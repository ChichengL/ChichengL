import { createElementVNode } from "./vdom/index"
import { createTextNodeVNode } from "./vdom/index"
import Watcher from "./observe/watcher";
import { patch } from "./vdom/patch";

export function initLifeCycle(Vue){
  Vue.prototype._updata = function(vnode){//将虚拟DOM转化为真实DOM
    const vm = this;
    const el = vm.$el;
    //这里vnode是虚拟节点,是真实节点
    const preVnode = vm._vnode;
    vm._vnode = vnode;//把组件第一次产生的虚拟节点保存到_vnode上
    if(preVnode){//之前渲染 
        vm.$el = patch(preVnode,vnode)
    }else{
        vm.$el = patch(el,vnode);//使用vnode,更新出真正的dom
    }
    //patch既有初始化的功能,又有更新的功能

  }
  Vue.prototype._c = function(){
    return createElementVNode(this,...arguments)
  }
  // _c('div',{},...children)
  Vue.prototype._v = function(){
    return createTextNodeVNode(this,...arguments)
  }
  // _v(text)
  Vue.prototype._s = function(value){
    if(typeof value !== 'object')return value;
    return JSON.stringify(value);
  }
  Vue.prototype._render = function(){
    const vm = this;
    // 让with中的this指向vm
    // console.log(vm.name,vm.age);
    return vm.$options.render.call(vm);//通过ast语法转义后生成的render方法
  }
}

export function callHook(vm,hook){
    const handlers = vm.$options[hook];
    console.log(handlers);
    if(handlers){
        handlers.forEach(handler=>{
            handler.call(vm);
        })
    }
}


export function mountComponent(vm,el){ //这里的el是通过querySelector处理过的
  vm.$el = el;
  //调用render方法产生虚拟DOM
  const updateComponent = ()=>{
    vm._updata(vm._render());
  }//vm.$options.render()渲染虚拟结点,vm._update()生成真实DOM
  // 根据虚拟DOM产生真实DOM
  // 3.插入到el元素中
  const watcher = new Watcher(vm,updateComponent,true);//这里的true标识着一个渲染过程
  // console.log(watcher);
}