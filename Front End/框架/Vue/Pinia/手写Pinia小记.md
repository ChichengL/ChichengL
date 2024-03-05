# Vuex和Pinia的区别



- Pinia的特点是采用ts进行编写的，类型提示友好，体积小。
- 去除mutations， 保存了state，getters，actions（包含了同步和异步）
- Pinia支持compositionAPI，同时兼顾OptionsApi
- Vuex中需要使用module定义模块，出现嵌套的树形结构，以此vuex中出现命名空间的概念。取值也非常
- Vuex中允许程序有一个store
- Pinia可以采用多个store，store之间可以互相调用（扁平化），不用担心命名冲突问题



```vue
new Vuex.Store({
	state:{a:1},
	module:{
	a:{
	state:{}
}
}
})
```



## Pinia的基本结构及CompositionApi格式

本次手写的pinia主要包含两个函数`createPinia`和`defineStore`

这里介绍一下createPinia的作用

- 创建一个pinia实例，然后将其挂载到当前实例上。
    - 因为Pinia支持Vue2和Vue3因此，有两种方法进行挂载到相应的实例上，然后最后返回一个Pinia实例

`createStore.ts`

```ts
import type { App } from "vue";
import { ref } from "vue";
import { PiniaSymbol } from "./rootState";
export function createPinia() {
  const state = ref({}); ///映射状态

  const pinia = {
    install(app: App) {
      //希望所有组件都访问，this.$pinia
      app.config.globalProperties.$pinia = pinia;
      //   使用provide和inject来访问pinia
      app.provide(PiniaSymbol, pinia);
    },
    state,
    _s: new Map(), //每个store id对应这一个store
  };
  return pinia;
}

```



_s是私有属性，主要功能是映射 id->store的关系，以便后面取出各种store

state作为全局状态树的一个起点或者最顶层的状态对象，作为映射状态的

对于各个仓库中`state的数据都是响应式`的，都借用了vue的`ref`方法

`store.ts`

```ts
import { computed, getCurrentInstance, inject, reactive, toRefs } from "vue";
import { PiniaSymbol } from "./rootState";

function createOptionStore(id: any, options: any, pinia: any) {
  const { state, actions, getters = {} } = options;

  function setup(store) {
    //用户提供的状态
    pinia.state.value[id] = state ? state() : {};
    const localState = toRefs(pinia.state.value[id]); //解构出去依旧是响应式

    const setupStore = Object.assign(
      localState,
      actions, //用户提供的动作
      Object.keys(getters).reduce((computeds, getterKey) => {
        computeds[getterKey] = computed(() => {
          return getters[getterKey].call(store);
        });
        return computeds;
      }, {})
    );
    return setupStore;
  }

  createSetupStore(id, setup, pinia); //options API需要将这个Api转化为
}
//setupStore 中用户提供了完整的setup方法，直接执行即可
function createSetupStore(id: any, setup: any, pinia: any) {
  const store = reactive({}); //创建响应式对象
  function wrapAction(action: Function) {
    return function () {
      //保证this对象
      return action.call(store, ...arguments);
    };
  }

  const setupStore = setup(store); //拿到的setupStore 可能没有处理过this指向
  for (let key in setupStore) {
    const value = setupStore[key];
    if (typeof value === "function") {
      setupStore[key] = wrapAction(value); //将函数的this永远指向store
    }
  }
  Object.assign(store, setupStore);
  console.log(store);
  pinia._s.set(id, store);
  return store;
}

export function defineStore(idOrOptions: string | any, setup: any) {
  let id: any;
  let options: any;

  if (typeof idOrOptions === "string") {
    id = idOrOptions;
    options = setup;
  } else {
    options = idOrOptions;
    id = idOrOptions.id;
  }
  function useStore() {
    const currentInstance = getCurrentInstance();
    const pinia: any = currentInstance && inject(PiniaSymbol);
    // return store
    //useStore只能在组件中使用
    if (!pinia._s.has(id)) {
      //第一次使用
      //创建选项store，还可能是setupStore
      if (typeof setup === "function") {
        createSetupStore(id, setup, pinia);
      } else {
        createOptionStore(id, options, pinia);
      }
    }
    const store = pinia._s.get(id);
    return store;
  }
  return useStore;
}

```

都知道defineStore返回的是一个对象，因此在`useStore`函数最后返回的是`store`对象。

因为defineStore支持vue2和vue3因此有两种风格，OptionsAPI和CompositionAPI

对于OptionsAPI

可能出现

```ts
export const useCounterStore = defineStore("counter", {
  state: () => {
    return {
      count: 0,
    };
  },
  getters: {
    double() {
      return this.count * 2;
    },
  },
  actions: {
    increment(payload:number) {
      this.count += payload;
    },
  },
});
```

这种情况，或者是

```ts
export const useCounterStore = defineStore( {
    id:"counter",
  state: () => {
    return {
      count: 0,
    };
  },
  getters: {
    double() {
      return this.count * 2;
    },
  },
  actions: {
    increment(payload:number) {
      this.count += payload;
    },
  },
});
```

对于这种选项式处理，调用的是`createOptionStore` 方法

createOptionStore方法接收三个参数，当前仓库的名字，配置对象，以及pinia实例

createOptionsStore最终返回的是一个对象

- 通过调用 `options.state()` 初始化并将其值赋给全局 pinia 状态树中对应 id 的位置。
- 然后通过toRefs方法，转化为响应式对象，相当于将state再包裹一层防止解构丢失响应式
- 然后通过setup函数将其内容转化为函数（最终这个函数要返回一个对象），以便后续CompositionAPI的统一处理

```tsx
export const useCounterStore = defineStore("counter", () => {
  const count = ref(0);
  const todoStore = useTodoStore();

  const double = computed(() => {
    return count.value * 2;
  });
  const increment = (payload: number) => {
    console.log(todoStore);
    count.value += payload;
  };
  return {
    count,
    double,
    increment,
  };
});
```



在`createSetupStore`方法中对state中的属性进行处理

- 首先创建一个响应式对象进行存储值
- 随后调用setup方法，拿到一个对象，其中包含state，getter，actions
- 然后遍历该对象，如果得到的值是function，那么就将其使用高阶函数处理，以防止解构后丢失this指针

- 执行传入的 setup 函数获取处理后的 store 结构，并将其中的函数包装以确保正确的上下文。
- 对于各种操作（actions）调用直接进行调用，然后放在当前仓库上

Object.assign将actions对象上的方法放在localState上，以便可以实现`xxxStore.yyy()`进行调用方法

getters本身就是计算属性，调用getters上的方法，然后将其用计算属性包裹得到

```js
Object.keys(getters).reduce((computeds, getterKey) => {
        computeds[getterKey] = computed(() => {
          return getters[getterKey].call(store);
        });
        return computeds;
      }, {})
```

这一步相当于是，创建一个新对象，然后执行getters上的方法，得到的数据通过computed包裹，后放在新对象上

然后通过Object.assign，将这些属性拷贝到localState上

最终得到的是一个`setupStore`

最后放在pinia._s上