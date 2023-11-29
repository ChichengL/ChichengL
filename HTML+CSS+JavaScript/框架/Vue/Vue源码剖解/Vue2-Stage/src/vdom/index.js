// h函数,_c函数都是调用这些

const isReservedTag = (tag) => {
    return [
        "a",
        "ul",
        "ol",
        "li",
        "div",
        "span",
        "p",
        "img",
        "input",
        "button",
        "textarea",
        "h1",
        "h2",
        "h3",
        "h4",
        "h5",
        "h6",
        "table",
        "tr",
        "td",
        "th",
        "tbody",
        "thead",
        "tfoot",
        "tr",
        "th",
        "td",
        "select",
        "option",
        "form",
    ].includes(tag);
};
export function createElementVNode(vm, tag, data, ...children) {
    if (data == null) {
        data = {};
    }
    let key = data.key || null;
    if (key) {
        delete data.key;
    }

    //判断是否为原生标签
    if (isReservedTag(tag)) {
        return VNode(vm, tag, key, data, children);
    } else {
        //创建组件的虚拟结点
        // 需要包含组件的构造函数
        let Ctor = vm.$options.components[tag];
        // Ctor可能是组件的定义，可能是一个Sub类，还有可能是组件的component选项
        return createComponentVnode(vm, tag, key, data, children, Ctor);
    }
}

function createComponentVnode(vm, tag, key, data, children, Ctor) {
    if (typeof Ctor === 'object') {
        Ctor = vm.$options._base.extend(Ctor);//将对象转化一下得到构造函数，_base声明于globalAPI上面的
    }
    data.hook = {
        init(vnode) {//稍后创造真实节点的时候，如果是组件则调用此init方法
            //保存组件的实例到虚拟节点
            let instance = vnode.componentInstance = new vnode.componentOptions.Ctor
            instance.$mount()
        }
    }
    return VNode(vm, tag, key, data, children, null, { Ctor })
}

// _v
export function createTextNodeVNode(vm, text) {
    return VNode(vm, undefined, undefined, undefined, undefined, text);
}
// 创建虚拟DOM,和ast一样吗?
// ast是做的语法上的转化,他描述的是语法本身(可以描述js css html)
// 虚拟DOM是描述的dom元素,可以增加一些自定义属性(描述dom)
function VNode(vm, tag, key, data, children, text, componentOptions) {
    return {
        vm,
        tag,
        key,
        data,
        children,
        text,
        componentOptions//组件的构造函数
    };
}

export function isSameVnode(vnode1, vnode2) {
    return vnode1.tag === vnode2.tag && vnode1.key === vnode2.key;
}
