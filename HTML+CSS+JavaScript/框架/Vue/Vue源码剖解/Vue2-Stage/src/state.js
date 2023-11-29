import { observe } from "./observe/index";
import Watcher,{nextTick} from "./observe/watcher";
import Dep from "./observe/dep";
export function initState(vm) {
    const opts = vm.$options;//获取所有的选项
    if (opts.data) {//如果有data选项那么初始化data
        initData(vm);
    }
    if (opts.computed) {
        initComputed(vm);
    }
    if (opts.watch) {
        initWatch(vm);
    }
}

function initWatch(vm) {
    let watch = vm.$options.watch;
    for (let key in watch) {//字符串,数组,函数
        const handler = watch[key];

        if (Array.isArray(handler)) {
            for (let i = 0; i < handler.length; i++) {
                createWatcher(vm, key, handler[i]);
            }
        } else {
            createWatcher(vm, key, handler);
        }
    }
}

function createWatcher(vm, key, handler) {//字符串,数组,函数(还有可能是对象)
    if (typeof handler === 'string') {
        handler = vm[handler];
    }
    return vm.$watch(key, handler);
}


// function proxy(vm,target,key){
//   Object.defineProperty(vm,key,{
//     get(){
//       return vm[target][key];
//     },
//     set(newVal){
//       vm[target][key] = newVal;
//     }
//   })
// }


function proxy(vm, target) {
    Object.keys(vm[target]).forEach(key => {
        Object.defineProperty(vm, key, {
            get() {
                return vm[target][key];
            },
            set(newVal) {
                vm[target][key] = newVal;
            }
        })
    })
}

function initData(vm) {
    let data = vm.$options.data;//data可能是函数，可能是对象
    // debugger;
    data = typeof data === 'function' ? data.call(vm) : data;//call进行执行函数  data是用户的属性
    vm._data = data;//将data挂载到vm._data
    //对数据进行劫持，Vue2使用defineProperty
    observe(data);

    // 将vm._data用vm代理即可直接使用vm访问到,比如vm.xxx实际上是访问到的 vm._data.xxx
    // for(let key in data){
    //   proxy(vm,'_data',key);
    // }
    proxy(vm, '_data');
}

function initComputed(vm) {
    const computed = vm.$options.computed;
    const watchers = vm._computedWatchers = {};//将计算属性watcher保存到vm上
    //循环对象
    for (let key in computed) {
        let userDef = computed[key];
        //userDef 可能是对象可能是函数
        //需要监控计算属性中get的变化,传入值,监视的实例,方法,配置项
        let fn = typeof userDef === 'function' ? userDef : userDef.get;
        watchers[key] = new Watcher(vm, fn, { lazy: true });
        defineComputed(vm, key, userDef);
    }
}
function defineComputed(target, key, userDef) {
    //   const getter = typeof userDef === 'function' ? userDef :userDef.get;
    const setter = userDef.set || (() => { });
    Object.defineProperty(target, key, {
        get: createComputedGetter(key),//希望当重复取值时不会调用getter
        set: setter
    })
}

function createComputedGetter(key) {
    //我们需要检测是否执行这个getter
    return function () {
        const watcher = this._computedWatchers[key];//获取到对应属性的watcher
        if (watcher.dirty) {
            //如果是脏的就去执行用户传入的函数
            watcher.evalaute();//求值后 dirty变为false,下次取值,就不求值了
        }
        if (Dep.target) {//计算属性出栈后还有渲染 watcher,应该也让计算属性中的watcher去收集上一层watcher
            watcher.depend();
        }
        return watcher.value;//这样就不用每次取值都是get来取,可以从缓存中来取
    }
}


export function initStateMixin(Vue) {
    Vue.prototype.$nextTick = nextTick;
    Vue.prototype.$watch = function (exprOrFn, cb) {//还有deep:true,immediate等
        // firstname
        // ()=>{}
        new Watcher(this, exprOrFn, { user: true }, cb);
    }
}