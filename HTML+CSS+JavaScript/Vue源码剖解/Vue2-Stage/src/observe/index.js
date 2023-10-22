import { newArrayProto } from "./array";
import Dep from "./dep";
class Observer {
    constructor(data) {

        // 给每个对象做收集功能 
        this.dep = new Dep();

        //数组单独处理
        data.__ob__ = this;//这里可以给data添加一个__ob__属性，这个属性指向Observer实例，这样就可以通过__ob__属性访问Observer实例了
        Object.defineProperty(data, '__ob__', {
            value: this,
            enumerable: false//将ob变为不可枚举否则会陷入死循环，因为进入data后枚举到其__ob__属性（实际回到了本身），那么就会出现问题
        })
        // 同时给数据加了标识，数据上有ob那么对象被代理过，但是也需要其变成不可枚举属性
        if (Array.isArray(data)) {
            //这里我们可以重写数组中的七个编译方法，可以修改数组本身的。除此之外还有数组内的引用方法也应该劫持，比如一个对象作为数组的内容
            //同时保留其他的方法，因此需要在array.js里面重写
            data.__proto__ = newArrayProto;
            this.observeArray(data);//观测数组
        } else {
            this.walk(data);
        }
    }
    walk(data) {
        Object.keys(data).forEach(key => defineReactive(data, key, data[key]))
    }
    observeArray(data) {
        data.forEach(item => observe(item))
    }
    //剩下的和之前一样
}

function dependArray(val) {
    for (let i = 0; i < val.length; i++) {
        let current = val[i];
        // console.log(current);
        if (Array.isArray(current)) {//如果还是数组
            dependArray(current);
            current.__ob__.dep.depend();//收集数组中数组依赖
        }
    }
}

export function defineReactive(data, key, val) {//形成闭包，值不会消失
    //如果数据是对象那么再次递归处理进行劫持
    let childOb = observe(val);//对所有的对象都进行属性劫持,childOb.dep 用来收集依赖
    let dep = new Dep();//每一个属性都有dep
    Object.defineProperty(data, key, {
        get() {//取值会执行get
            if (Dep.target) {
                dep.depend();//让这个属性的收集器记住当前的watcher
                if (childOb) {//比如对象,数组类
                    childOb.dep.depend();//让数组或者对象本身进行依赖收集
                    if (Array.isArray(val)) {
                        dependArray(val);
                    }
                }
            }
            return val;
        },
        set(newVal) {
            if (newVal !== val) {
                val = newVal;
                dep.notify();//通知更新
            }
        }
    })
}
export function observe(data) {
    if (typeof data !== 'object' || data === null) return;//只对对象劫持
    //如果一个对象被劫持了，那么就不需要再被劫持了（判断一个对象是否被劫持过，可以添加一个实例，用实例进行判定）

    if (data.__ob__ instanceof Observer) {//说明被代理过，直接返回它的实例对象
        return data.__ob__;
    }
    return new Observer(data);
}