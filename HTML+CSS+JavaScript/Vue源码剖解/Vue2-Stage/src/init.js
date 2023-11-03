import { initState } from "./state";
import { compileToFunction } from "./compiler/index";
import { mountComponent } from "./lifecycle";
import { mergeOptions } from "./utils";
export function initMixin(Vue){//给Vue 增加init方法
  Vue.prototype._init = function(options){//用于初始化操作
    //vue vm.$options 就是获取用户的配置 
    const vm = this; //
    vm.$options = mergeOptions(this.constructor.options,options);//把用户配置赋值给vm.,挂载到vm身上 使用$标识表示这是vue里面的
    // callHook(vm,'beforeCreate');
    //初始化状态
    initState(vm);
    // callHook(vm,'created');
    //判断是否由el属性
    if(options.el){
      vm.$mount(options.el);//挂载 
    }
  }
  Vue.prototype.$mount = function(el){
    const vm = this;
    el = document.querySelector(el);
    let op = vm.$options;
    if(!op.render){//如果没有render函数
      let template;//没有render看是否写了template。没有写template采用外部的template
      if(!op.template && el){//没有模版但是有el
         template = el.outerHTML;
      }else{
          template = op.template;//如果有el则采用模版
      }
      // console.log(template);
      if(template){//存在模版就对模版进行编译
        const render = compileToFunction(template);
        op.render = render;//把编译后的render函数赋值给render
      }
    }
    // console.log(op.render);
    mountComponent(vm,el);//组件挂载

    //script标签引用的vue.global.js这个编译过程是在浏览器进行的，runtime是不包含模版编译的，整个编译是打包的时候通过loader来转义.vue文件的
    //用runtime的时候不能使用template模版的
  }
}
