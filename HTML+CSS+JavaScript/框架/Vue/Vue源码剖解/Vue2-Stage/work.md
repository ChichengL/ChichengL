

- Vue.component 作用就是收集全局的定义   id和对应的definition  Vue.options.components[组件名] = 定义||包装成构造函数（定义）
- Vue.extend 返回一个子类，而且会在子类上记录自己的选项（为什么Vue组件中的data不能是一个对象？）


```
function extend(选项) {
    function Sub(){
        this._init()//子组件的初始化
    }
    Sub.options = 选项
    return Sub
}

let Sub = Vue.extend({data:数据源})

new Sub()   mergeOptions(Sub.options)
new Sub()   mergeOptions(Sub.options)

//当new了两个的时候，如果传入的都是同一个对象，那么会达到“共享数据”，或者称之为相互污染，但是如果data是函数形式，那么就是闭包进行保存的,就是全新的数据源
```

- 创建子类的构造函数的时候，会将全局的租金啊和自己身上定义的组件进行合并(组件的合并会先查找自己再查找全局)
- 组件的渲染，开始渲染组件会编译组件的模版变成render函数 ，render函数返回虚拟DOM，然后渲染成真实DOM，渲染真实DOM的时候，会根据组件的data数据源，生成
- createElementVNode  会根据tag类型来区分是否是组件，如果是组件，那么会调用createComponent，createComponent会调用子类的_init方法，增加componentsOptions选项{Ctor}，稍后创在组件的真实节点，我们只需要使用new Ctor()