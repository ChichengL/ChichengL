// h函数,_c函数都是调用这些
export function createElementVNode(vm, tag, data, ...children) {
    if (data == null) {
        data = {};
    }
    let key = data.key || null;
    if (key) {
        delete data.key;
    }
    return VNode(vm, tag, key, data, children)
}

// _v
export function createTextNodeVNode(vm, text) {
    return VNode(vm, undefined, undefined, undefined, undefined, text)
}
// 创建虚拟DOM,和ast一样吗?
// ast是做的语法上的转化,他描述的是语法本身(可以描述js css html)
// 虚拟DOM是描述的dom元素,可以增加一些自定义属性(描述dom)
function VNode(vm, tag, key, data, children, text) {
    return {
        vm, tag, key, data, children, text
    }
}

export function isSameVnode(vnode1,vnode2){
    return vnode1.tag===vnode2.tag&&vnode1.key===vnode2.key
}