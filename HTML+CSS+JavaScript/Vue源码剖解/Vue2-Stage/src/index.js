//将所有的方法耦合在一起
import { initMixin } from './init'
import { initLifeCycle } from './lifecycle';
import { initStateMixin } from './state';
function Vue(options) {//options就是用户的选项
    this._init(options);//初始化操作
}

initMixin(Vue);//扩展了init方法 
initLifeCycle(Vue);//扩展了生命周期方法

initStateMixin(Vue);//实现了nextTick和$watch

// 为了测试使用

export default Vue