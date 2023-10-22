import { isSameVnode } from ".";

export function createElm(vnode) {
    let { tag, data, children, text } = vnode;
    if (typeof tag === 'string') {//标签
        vnode.el = document.createElement(tag);// 这里将真实节点和虚拟节点对应起来，后续如果修改属性了
        patchProps(vnode.el, {}, data);// 处理data
        children.forEach(child => {
            vnode.el.appendChild(createElm(child));
        });
    } else {//就是创建文本
        vnode.el = document.createTextNode(text);
    }
    return vnode.el;
}

export function patchProps(el, oldProps = {}, props = {}) {
    //可能老的属性有而新的属性没有的情况需要去除老的
    let oldStyle = oldProps.style || {};
    let newStyle = props.style || {};
    for (let key in oldStyle) {//老的样式中有而新的样式中没有，则删除
        if (!newStyle[key]) {
            el.style[key] = '';
        }
    }

    for (let key in oldProps) {
        if (!props[key]) {
            el.removeAttribute(key);//老的属性中有而新的没有，则删除属性
        }
    }


    for (let key in props) { //styly{color:'red'}       使用新的覆盖老的
        if (key === 'style') {
            for (let styleName in props.style) {
                el.style[styleName] = props.style[styleName];
            }
        } else {
            el.setAttribute(key, props[key]);//这里将属性都设置到真实dom上
        }
    }
}

export function patch(oldVNode, vnode) {
    //初渲染和后面的diff渲染一样的
    const isRealElement = oldVNode.nodeType;//nodeType是js原生属性,如果是元素节点的那么值就是1
    if (isRealElement) {
        const elm = oldVNode;//这里oldVNode是真实dom
        const parentElm = elm.parentNode;//拿到真实元素

        let newElm = createElm(vnode);
        parentElm.insertBefore(newElm, elm);//将新节点插入到老节点后面
        parentElm.removeChild(elm);//删除老节点
        return newElm;
    } else {
        // diff算法
        //1.两个节点不是同一个节点      直接删除老的
        // 2.两个节点是同一个节点(判断节点的tag和节点的key)比较两个节点的属性是否由差异（复用老节点，将差异的属性更新）
        // 节点比较完毕就需要比较两人的儿子
        patchVnode(oldVNode, vnode);
    }
}

function patchVnode(oldVNode, vnode) {
    if (!isSameVnode(oldVNode, vnode)) {
        //使用老节点的父亲进行替换
        let el = createElm(vnode)
        oldVNode.el.parentNode.replaceChild(el, oldVNode.el)
        return el;
    }
    //文本情况,期望对文本内容进行比较
    let el = vnode.el = oldVNode.el //复用老节点的元素
    if (!oldVNode.tag) {//是文本
        if (oldVNode.text !== vnode.text) {
            el.textContent = vnode.text;//用新的文本覆盖掉老的
        }
    }
    //是标签        需要比对标签的属性
    patchProps(el, oldVNode.data, vnode.data);

    //比较儿子节点      比较一方有儿子，一方没有儿子        两方都有儿子

    let oldChildren = oldVNode.children;
    let newChildren = vnode.children;

    if (oldChildren.length > 0 && newChildren.length > 0) {
        //完整的diff算法（需要比较两个人的儿子）
        updateChildren(el, oldChildren, newChildren);
    } else if (newChildren.length > 0) {//没有老的儿子直接插入
        mountChildren(el, newChildren);
    } else if (oldChildren.length > 0) {//新的没有，老的有，需要删除
        el.innerHTML = '';//也可以循环删除
    }

    return el;
}

function mountChildren(el, newChildren) {
    for (let i = 0; i < newChildren.length; i++) {
        let child = newChildren[i];
        el.appendChild(createElm(child));
    }
}
function updateChildren(el, oldChildren, newChildren) {
    //比较两个儿子的时候，为了增高性能会有优化手段
    let oldStartIndex = 0;//老儿子开始的位置
    let newStartIndex = 0;//新儿子开始的位置
    let oldEndIndex = oldChildren.length - 1;//老儿子结束的位置
    let newEndIndex = newChildren.length - 1;//新儿子结束的位置
    let oldStartVnode = oldChildren[oldStartIndex];
    let oldEndVnode = oldChildren[oldEndIndex];
    let newStartVnode = newChildren[newStartIndex];
    let newEndVnode = newChildren[newEndIndex];


    function makeIndexByKey() {
        let map = {};
        children.forEach((child, index) => {
            map[child.key] = index;
        })
        return map;
    }
    let map = makeIndexByKey(oldChildren);


    while (oldStartIndex <= oldEndIndex && newStartIndex <= newEndIndex) {
        if (!oldStartVnode) {
            oldStartVnode = oldChildren[++oldStartIndex];
        } else if (!oldEndVnode) {
            oldEndVnode = oldChildren[--oldEndIndex];
        }
        //有一方大于尾指针就停止
        else if (isSameVnode(oldStartVnode, newStartVnode)) {
            patchVnode(oldStartVnode, newStartVnode)// 如果是相同节点，则递归比较子节点
            oldStartVnode = oldChildren[++oldStartIndex];
            newStartVnode = newChildren[++newStartIndex];
        }
        else if (isSameVnode(oldEndVnode, newEndVnode)) {//比较尾节点
            patchVnode(oldStartVnode, newStartVnode)// 如果是相同节点，则递归比较子节点
            oldEndVnode = oldChildren[--oldEndIndex];
            newEndVnode = newChildren[--newEndIndex];
        }

        // 交叉比较 abcd -> dabc
        // 头尾比对和尾头比对,同时处理的倒序的情况
        else if (isSameVnode(oldEndVnode, newStartVnode)) {
            patchVnode(oldEndVnode, newStartVnode);
            el.insertBefore(oldEndVnode.el, oldStartVnode.el)//将老的后面的节点插入到开头节点的前面

            oldEndVnode = oldChildren[--oldEndIndex];
            newStartVnode = newChildren[++newStartIndex];

        }
        else if (isSameVnode(oldStartVnode, newEndVnode)) {
            patchVnode(oldStartVnode, newEndVnode);
            el.insertBefore(oldStartVnode.el, oldEndVnode.el.nextSibling)//将老头节点放在尾节点之后
            oldStartVnode = oldChildren[++oldStartIndex];
            newEndVnode = newChildren[--newEndIndex];
        }
        // 在给动态列表添加key时,尽可能避免使用索引,无论你怎么改变索引都是从0开始非常容易错乱
        else {
            // 乱序比对
            let moveIndex = map[newStartVnode.key];//如果拿到则说明是要移动的索引
            if (moveIndex !== undefined) {
                let moveVnode = oldChildren[moveIndex];//找到对应的虚拟节点 ,复用
                el.insertBefore(moveVnode.el, oldStartVnode.el);
                oldChildren[moveIndex] = undefined//标识这个节点清空了
                patch(moveVnode, newStartVnode);
            } else {//找不到的情况
                el.insertBefore(createElm(newStartVnode), oldStartVnode.el);
            }
        }

    }
    if (newStartIndex <= newEndIndex) {//多余的塞进去
        for (let i = newStartIndex; i <= newEndIndex; i++) {
            let childEl = createElm(newChildren[i]);
            // 可能像后追加,可能向前追加
            // el.appendChild(childEl)
            let anchor = newChildren[newEndIndex + 1] ? newChildren[newEndIndex + 1].el : null; //获取下一个元素
            el.insertBefore(childEl, anchor);//当anchor为null的时候,就会认为是appendChild
        }
    }
    if (oldStartIndex <= oldEndIndex) {
        for (let i = oldStartIndex; i <= oldEndIndex; i++) {
            if(oldChildren[i]){
                el.removeChild(oldChildren[i].el);
            }
        }
    }
}