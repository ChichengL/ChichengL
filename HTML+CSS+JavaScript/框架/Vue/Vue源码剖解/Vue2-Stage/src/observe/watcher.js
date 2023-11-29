import Dep, { popTarget, pushTarget } from "./dep";

let id = 0;

// 1)当我们创建渲染watcher的时候我们会把当前的渲染watcher放在Dep.target上
// 2)调用_render()会取值走到get上


class Watcher {//不同组件有不同的watcher
    constructor(vm, exprOrFn, options, cb) {

        this.cb = cb;//对于watch
        if (typeof exprOrFn === 'string') {
            this.getter = function(){return vm[exprOrFn]}//将字符串变为函数
        } else {
            this.getter = exprOrFn;//getter意味调用这个函数可以发生取值操作
        }

        this.id = id++;
        this.renderWatcher = options;
        this.deps = [];//收集依赖
        this.depsId = new Set();//收集依赖的id
        this.vm = vm;//防止在计算属性取得getter时,调用的this不是对应的this

        this.lazy = options.lazy;
        this.dirty = this.lazy;//缓存值
        this.oldValue = this.lazy ? undefined : this.get();// 
        //value是旧值
    }

    evalaute() {
        this.value = this.get();//获取到用户函数的返回值,并且还要标识为脏
        this.dirty = false;
    }
    get() {
        pushTarget(this);//静态属性只有一份
        let val = this.getter.call(this.vm);//会去vm上取值,当渲染时就会有取值操作触发getter,然后在getter里面操作
        popTarget();//渲染完成就清空,只是在模板中收集的时候才会做依赖收集
        return val;
    }
    addDep(dep) {//一个组件对应多个属性,重复的属性无需记录
        let id = dep.id;
        if (!this.depsId.has(id)) {
            this.deps.push(dep);
            this.depsId.add(id);
            dep.addSub(this);
        }
    }
    depend() {
        let i = this.deps.length;
        while (i--) {
            this.deps[i].depend();//让计算属性watcher也收集渲染watcher
        }
    }
    update() {
        if (this.lazy) {//如果是计算属性,依赖属性变化了,就标识是脏值
            this.dirty = true;
        } else {
            queueWatcher(this);//暂存watcher
            this.run();//重新更新
        }
    }
    run() {
        let newValue = this.get();
        if(this.user){
            this.cb.call(this.vm,newValue,this.oldValue);
        }
    }
}



let queue = [];//因为可能更新同一属性多次，那么需要去重，只保留最后一个
let has = {};//使用对象去重，或者set去重
let pending = false;//进行防抖操作，无论调用多少次，只执行一次

function flushSchedulerQueue() {
    let flushQueue = queue.slice(0);//拷贝一下queue
    flushQueue.forEach(q => q.run());//在刷新过程中可能存在新的watcher，重新被放回在队列中
    queue = [];
    has = {};
    pending = false;
}

function queueWatcher(watcher) {
    let id = watcher.id;//取出每个监视器的唯一标识id
    if (has[id] == null) {
        queue.push(watcher);
        has[id] = true;
        //可能有多个组件不管update多少次，最终只执行一次刷新操作
        if (!pending) {
            nextTick(flushSchedulerQueue, 0)//刷新调度队列
            pending = true;
        }
    }
}

let callbacks = [];
let waiting = false;
function flushCallbacks() {
    waiting = false;
    let cbs = callbacks.slice(0);
    callbacks = [];
    cbs.forEach(cb => cb());
}

let timerFunc;
if (Promise) {
    timerFunc = (flushCallbacks) => {
        Promise.resolve().then(flushCallbacks)
    }
} else if (MutationObserver) {
    let observer = new MutationObserver(flushCallbacks);//这里传入的回调是异步执行的
    let textNode = document.createTextNode(1);
    observer.observe(textNode, {
        characterData: true
    });//让observer监控文本,如果数据变化,那么就执行cb任务
    timerFunc = () => {
        textNode.textContent = 2;
    }
} else if (setImmediate) {
    timerFunc = () => {
        setImmediate(flushCallbacks);
    }
} else {
    timerFunc = () => {
        setTimeout(flushCallbacks, 0);
    }
}

//nextTick中没有直接使用某个api,而是采用优雅降级的方式
// 内部采用promise(ie不兼容)降级为MutationObserver(h5的api) 可以再降级为ie专享setImmediate   降级为 setTimeout 
export function nextTick(cb) {//先内部还是先用户
    callbacks.push(cb);//维护nextTick中的callback方法,同步操作
    if (!waiting) {
        // debugger;
        timerFunc();
        waiting = true;
    }
}

//需要给每个属性添加一个dep,目的是收集watcher
// n个dep对应一个视图(一个watcher)
// 一个属性对应多个组件,一个dep对应多个watcher    所以两者关系是多对多

export default Watcher;