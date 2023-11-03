
import { observe } from './observe/index'
import {mergeOptions} from './utils'

export function initGlobalAPI(Vue) {
  // config
  const configDef = {}
  configDef.get = () => config
  Object.defineProperty(Vue, 'config', configDef)

  // exposed util methods.
  // NOTE: these are not considered part of the public API - avoid relying on
  // them unless you are aware of the risk.


  // 2.6 explicit observable API
  Vue.observable = function(obj){
    observe(obj)
    return obj
  }

  Vue.options = Object.create(null)
  

  // this is used to identify the "base" constructor to extend all plain-object
  // components with in Weex's multi-instance scenarios.
  Vue.options = {
    _base:Vue,
  }
  Vue.mixin = function(mixin) {
    this.options = mergeOptions(this.options, mixin)
    return this
  }
  Vue.extend = function(options) {
    //实现根据用户的参数返回一个构造函数
    function Sub(options = {}){
      //调用Vue的构造函数
      this._init(options)
    }
    Sub.prototype = Object.create(this.prototype)//Sub.protoytype.__proto__ = Vue.protoType
    Sub.prototype.constructor = Sub
    //将用户传递的参数和全局的Vue.options来合并
    Sub.options = mergeOptions(Vue.options, options);
    return Sub
  }
  Vue.options.components = {}//全局的指令  Vue.options.directives
  Vue.components = function(id, definition){
    //如果是函数直接返回，不是函数就进行包装
    definition = typeof definition === 'function' ? definition : Vue.extend(definition)
    Vue.options.components[id] = definition
  }

}
