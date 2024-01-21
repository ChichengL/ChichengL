# Vue3源码学习

整体流程

![整体流程](Vue3%E6%BA%90%E7%A0%81%E5%AD%A6%E4%B9%A0.assets/138114565-3e0eecbb-7fd0-4203-bf36-5e5fd8003ce0.png)



![关键函数调用](Vue3%E6%BA%90%E7%A0%81%E5%AD%A6%E4%B9%A0.assets/68747470733a2f2f696d616765732d313235323630323835302e636f732e61702d6265696a696e672e6d7971636c6f75642e636f6d2f32303232303932373137303635382e706e67)





![img](Vue3%E6%BA%90%E7%A0%81%E5%AD%A6%E4%B9%A0.assets/138115157-1f4fb8a2-7e60-412d-96de-12e68eb0288c.png)



![img](Vue3%E6%BA%90%E7%A0%81%E5%AD%A6%E4%B9%A0.assets/138114969-9139e4af-b2df-41b2-a5d9-069d8b41903c.png)

建议的阅读顺序

1. **响应式系统**：
    - 从 `@vue/reactivity` 模块开始，这是Vue3响应式设计的核心部分。理解如何使用ES6的Proxy实现数据劫持，以及如何通过`ref`、`reactive`、`readonly`等函数创建响应式对象。探究`effect`、`track`、`trigger`等函数如何收集和触发依赖。
2. **组件基础**：
    - 进一步阅读 `@vue/runtime-core` 模块，理解Vue组件的基本结构和生命周期。重点关注`Component`、`VNode`、`PublicInstance`等概念，以及`setup`、`render`、`props`、`emits`等组件属性的处理逻辑。
3. **渲染器适配**：
    - 然后阅读 `@vue/runtime-dom` 或 `@vue/server-renderer`，这取决于你关注客户端渲染还是服务器端渲染。了解Vue如何与DOM进行交互，包括如何创建和更新DOM节点，以及如何处理事件、插槽等。
4. **高级特性**：
    - 深入研究Vue3提供的高级API实现，如`@vue/runtime-core`中的`watch`、`watchEffect`、`computed`、`provide`、`inject`等函数的实现逻辑。
5. **模板编译**（可选）：
    - 如果对Vue的模板编译过程感兴趣，可以阅读 `@vue/compiler-dom` 和 `@vue/compiler-sfc` 模块，了解Vue单文件组件（SFC）的模板是如何被编译成渲染函数的。
6. **周边生态**（可选）：
    - Vue Router、Vuex等官方库的源码也是很好的学习材料，它们展示了如何将响应式系统与其他功能模块相结合，实现更复杂的业务逻辑。
7. **项目启动与构建**（可选）：
    - 最后，可以看看Vue CLI或Vite等项目脚手架的源码，了解项目初始化、构建、热更新等工程化方面的实现。



## Reactivity————响应式实现

响应式作为Vue的一大特点，其重要性可见一斑。

reactive是实现响应式的基础，后续的ref，shallowreactive，readonly都是建立在这个基础上的

本章的重心在，`reactive，ref`等（还有shallow和readonly），以及通过track和trigger进行依赖收集，以及计算属性。



#### reactive

首先是创建了四个Map，进行收集各个类型的reactive对象

```ts
export const reactiveMap = new WeakMap<Target, any>()
export const shallowReactiveMap = new WeakMap<Target, any>()
export const readonlyMap = new WeakMap<Target, any>()
export const shallowReadonlyMap = new WeakMap<Target, any>()
```

最关键的调用创建**createReactiveObject**

```ts
export function reactive(target: object) {
  // if trying to observe a readonly proxy, return the readonly version.
  if (isReadonly(target)) {
    return target
  }
  return createReactiveObject(
    target,
    false,
    mutableHandlers,
    mutableCollectionHandlers,
    reactiveMap,
  )
}

```

这里声明，相当于对这个对象进行创建响应式，且不是浅观察

`createReactiveObject`的声明

```ts
function createReactiveObject(
  target: Target,
  isReadonly: boolean,
  baseHandlers: ProxyHandler<any>,
  collectionHandlers: ProxyHandler<any>,
  proxyMap: WeakMap<Target, any>,
) {
  if (!isObject(target)) {
    return target
  }
  // target is already a Proxy, return it.
  // exception: calling readonly() on a reactive object
  if (
    target[ReactiveFlags.RAW] && //相当于表明是原始数据（__v_raw）
    !(isReadonly && target[ReactiveFlags.IS_REACTIVE])
  ) {
    return target
  }
  // target already has corresponding Proxy
  const existingProxy = proxyMap.get(target)//如果之前声明过，就直接返回
  if (existingProxy) {
    return existingProxy
  }
  // only specific value types can be observed.
  const targetType = getTargetType(target)
  if (targetType === TargetType.INVALID) {
    return target
  }
  const proxy = new Proxy(
    target,
    targetType === TargetType.COLLECTION ? collectionHandlers : baseHandlers,//看情况进行处理，如果是可收集类型，那么就使用collectionHandlers否则就正常处理
  )
  proxyMap.set(target, proxy)//将相对应的Map中存入值。
  return proxy
}

```





那么对于其他的，比如shallow，readonly类型就是

```ts
export function shallowReactive<T extends object>(
  target: T,
): ShallowReactive<T> {
  return createReactiveObject(
    target,
    false,
    shallowReactiveHandlers,
    shallowCollectionHandlers,
    shallowReactiveMap,
  )
}
export function readonly<T extends object>(
  target: T,
): DeepReadonly<UnwrapNestedRefs<T>> {
  return createReactiveObject(
    target,
    true,
    readonlyHandlers,
    readonlyCollectionHandlers,
    readonlyMap,
  )
}
```

从baseHandler声明处理各个类型的函数

```ts
import {
  mutableHandlers,
  readonlyHandlers,
  shallowReactiveHandlers,
  shallowReadonlyHandlers,
} from './baseHandlers'
```

然后就是对于是否是相对于类型的函数的实现

```ts
export function isReactive(value: unknown): boolean {
  if (isReadonly(value)) {
    return isReactive((value as Target)[ReactiveFlags.RAW])
  }
  return !!(value && (value as Target)[ReactiveFlags.IS_REACTIVE])
}
```

这句话相当于是，先看是否为只读对象，如果是，就进行查找原本的对象是否为Reactive类型；否则就是查找是否存在value且满足value上存在`__v_isReactive`



是在定义Target接口时定义的`ReactiveFlags.IS_REACTIVE`

```ts
export interface Target {
  [ReactiveFlags.SKIP]?: boolean
  [ReactiveFlags.IS_REACTIVE]?: boolean
  [ReactiveFlags.IS_READONLY]?: boolean
  [ReactiveFlags.IS_SHALLOW]?: boolean
  [ReactiveFlags.RAW]?: any
}
```

ReactiveFlags.RAW是any的原因，因为包裹的可能是对象可能是数组也可能是一些基本数据。





#### baseHandler



在 BaseReactiveHandler中，定义了get方法（是每一个Handler都有的）



get方法里面有很多杂乱的。

最核心的就是取数据时的拦截

也就是`track`方法

```ts
if (!isReadonly) {
      track(target, TrackOpTypes.GET, key)
}
```

其余的，在MutableReactiveHandler，定义的，比如set方法，

```typescript
set(
    target: object,
    key: string | symbol,
    value: unknown,
    receiver: object,
  ): boolean {
    let oldValue = (target as any)[key]
    if (!this._shallow) {
      const isOldValueReadonly = isReadonly(oldValue)
      if (!isShallow(value) && !isReadonly(value)) {
        oldValue = toRaw(oldValue)
        value = toRaw(value)
      }
      if (!isArray(target) && isRef(oldValue) && !isRef(value)) {
        if (isOldValueReadonly) {
          return false
        } else {
          oldValue.value = value
          return true
        }
      }
    } else {
      // in shallow mode, objects are set as-is regardless of reactive or not
    }

    const hadKey =
      isArray(target) && isIntegerKey(key)
        ? Number(key) < target.length
        : hasOwn(target, key)
    const result = Reflect.set(target, key, value, receiver)
    // don't trigger if target is something up in the prototype chain of original
    if (target === toRaw(receiver)) {
      if (!hadKey) {
        trigger(target, TriggerOpTypes.ADD, key, value)
      } else if (hasChanged(value, oldValue)) {
        trigger(target, TriggerOpTypes.SET, key, value, oldValue)
      }
    }
    return result
  }
```

使用了trigger方法，该属性的相关方法进行调用

track是在reactiveEffect文件中声明的。



#### reactiveEffect

track函数

```ts
export function track(target: object, type: TrackOpTypes, key: unknown) {
  if (shouldTrack && activeEffect) {
    let depsMap = targetMap.get(target)
    if (!depsMap) {
      targetMap.set(target, (depsMap = new Map()))
    }
    let dep = depsMap.get(key)
    if (!dep) {
      depsMap.set(key, (dep = createDep(() => depsMap!.delete(key))))
    }
    trackEffect(
      activeEffect,
      dep,
      __DEV__
        ? {
            target,
            type,
            key,
          }
        : void 0,
    )
  }
}
```

同样的味道，进行拦截，为每个管理值的“主播”，添加“粉丝”列表。

作用：

1. 函数接收三个参数：
    - `target`: 响应式对象，可能是经过Vue3代理过的对象，具有响应式能力。
    - `type`: 操作类型，取值为`TrackOpTypes`枚举，通常有`GET`（读取属性）。
    - `key`: 访问的属性名。
2. 首先判断全局变量`shouldTrack`是否为真且当前存在活跃的副作用函数`activeEffect`。若满足条件，则开始依赖收集流程。
3. 从全局的`targetMap`中获取`target`对应的依赖映射（depsMap）。如果尚未创建，就为`target`创建一个新的Map实例并存入`targetMap`。
4. 在depsMap中查找对应`key`的依赖项（dep）。如果没有找到，就创建一个新的`Dep`实例，并提供一个清理回调，当该依赖项不再被任何活跃副作用函数引用时，可以从depsMap中移除该key。
5. 调用`trackEffect`函数将当前活跃的副作用函数（`activeEffect`）与新创建或已存在的依赖项关联起来，这样当依赖项对应的属性发生变化时，就可以通过这个依赖项找到并触发所有的相关副作用函数。
6. 在开发环境下，还可以传入额外的调试信息，以便更好地追踪和理解依赖收集的过程。



还有trigger函数，也就是set后触发的函数。

```ts
export function trigger(
  target: object,
  type: TriggerOpTypes,
  key?: unknown,
  newValue?: unknown,
  oldValue?: unknown,
  oldTarget?: Map<unknown, unknown> | Set<unknown>,
) {
  const depsMap = targetMap.get(target)
  if (!depsMap) {
    // never been tracked
    return
  }

  let deps: (Dep | undefined)[] = []
  if (type === TriggerOpTypes.CLEAR) {
    // collection being cleared
    // trigger all effects for target
    deps = [...depsMap.values()]
  } else if (key === 'length' && isArray(target)) {
    const newLength = Number(newValue)
    depsMap.forEach((dep, key) => {
      if (key === 'length' || (!isSymbol(key) && key >= newLength)) {
        deps.push(dep)
      }
    })
  } else {
    // schedule runs for SET | ADD | DELETE
    if (key !== void 0) {
      deps.push(depsMap.get(key))
    }

    // also run for iteration key on ADD | DELETE | Map.SET
    switch (type) {
      case TriggerOpTypes.ADD:
        if (!isArray(target)) {
          deps.push(depsMap.get(ITERATE_KEY))
          if (isMap(target)) {
            deps.push(depsMap.get(MAP_KEY_ITERATE_KEY))
          }
        } else if (isIntegerKey(key)) {
          // new index added to array -> length changes
          deps.push(depsMap.get('length'))
        }
        break
      case TriggerOpTypes.DELETE:
        if (!isArray(target)) {
          deps.push(depsMap.get(ITERATE_KEY))
          if (isMap(target)) {
            deps.push(depsMap.get(MAP_KEY_ITERATE_KEY))
          }
        }
        break
      case TriggerOpTypes.SET:
        if (isMap(target)) {
          deps.push(depsMap.get(ITERATE_KEY))
        }
        break
    }
  }

  pauseScheduling()
  for (const dep of deps) {
    if (dep) {
      triggerEffects(
        dep,
        DirtyLevels.Dirty,
        __DEV__
          ? {
              target,
              type,
              key,
              newValue,
              oldValue,
              oldTarget,
            }
          : void 0,
      )
    }
  }
  resetScheduling()
}
```

这段函数主要干了

1. 函数`trigger`接收五个参数：
    - `target`: 响应式对象，可以是Array、Set、Map或其他对象。
    - `type`: 操作类型，取值为`TriggerOpTypes`枚举，表示对目标对象执行的操作，如`ADD`（添加元素）、`DELETE`（删除元素）、`SET`（设置属性值）、`CLEAR`（清空集合）等。
    - `key`：在操作特定属性时传入的键名。
    - `newValue`：新值，在属性被设置时传入。
    - `oldValue`：旧值，在属性被改变时传入。
    - `oldTarget`：对于特定操作可能需要的老的目标对象引用。
2. 函数首先尝试从全局的`targetMap`中获取当前`target`对应的依赖映射（depsMap），如果未找到，则说明该对象从未被跟踪过，直接返回。
3. 根据不同的`type`操作，收集所有相关的依赖（Dep实例）到deps数组中。例如：
    - 当`type`为`CLEAR`时，清除整个集合，触发所有对该目标对象的依赖。
    - 当操作涉及到数组长度变化时，会处理相关索引的依赖。
    - 对于Map、Set以及数组的增删改查操作，还会触发迭代器键（ITERATE_KEY）的相关依赖。
4. 使用`pauseScheduling`和`resetScheduling`暂停和恢复调度，以批量更新所有依赖。
5. 遍历收集到的所有依赖项，调用`triggerEffects`函数，触发这些依赖的副作用函数执行更新，同时传入一些用于调试的详细信息。



这两个函数离不开，trackEffect和triggerEffects函数也就是存在在effect中的

#### effect

```typescript
export function trackEffect(
  effect: ReactiveEffect,
  dep: Dep,
  debuggerEventExtraInfo?: DebuggerEventExtraInfo,
) {
  if (dep.get(effect) !== effect._trackId) {//验证副作用函数（effect）是否已经与当前的 Dep 关联，如果没有关联或关联的标识符（_trackId）不匹配，则将关联标识符设置到 Dep 中，并将 Dep 添加到副作用函数的依赖数组中。
    dep.set(effect, effect._trackId)
    const oldDep = effect.deps[effect._depsLength]
    if (oldDep !== dep) {
      if (oldDep) {
        cleanupDepEffect(oldDep, effect)
      }
      effect.deps[effect._depsLength++] = dep
    } else {
      effect._depsLength++
    }
    if (__DEV__) {
      effect.onTrack?.(extend({ effect }, debuggerEventExtraInfo!))
    }
  }
}

const queueEffectSchedulers: EffectScheduler[] = []

export function triggerEffects(
  dep: Dep,
  dirtyLevel: DirtyLevels,
  debuggerEventExtraInfo?: DebuggerEventExtraInfo,
) {
  pauseScheduling()
  for (const effect of dep.keys()) {
    if (
      effect._dirtyLevel < dirtyLevel &&//遍历 Dep 中的所有副作用函数，检查它们的“脏”级别是否低于给定的 dirtyLevel，以及是否已正确关联到 Dep。
      dep.get(effect) === effect._trackId
    ) {
      const lastDirtyLevel = effect._dirtyLevel//果满足条件，则更新副作用函数的“脏”级别，并检查是否需要安排重新执行（首次变脏的情况）。
      effect._dirtyLevel = dirtyLevel
      if (lastDirtyLevel === DirtyLevels.NotDirty) {
        effect._shouldSchedule = true
        if (__DEV__) {
          effect.onTrigger?.(extend({ effect }, debuggerEventExtraInfo))
        }
        effect.trigger()//调用副作用函数的 trigger 方法，实际执行副作用函数，从而更新视图或其他相关状态。
      }
    }
  }
  scheduleEffects(dep)//调用 scheduleEffects 函数对符合条件的副作用函数进行调度。
  resetScheduling()
}
```



这里，没有读过vue2源码的可能有点懵不知道依赖是如何收集的。主要是靠trackEffect和triggerEffects进行收集

`trackEffect` 主要负责收集依赖。当一个副作用函数（如组件的渲染函数或计算属性的getter）访问响应式对象的属性时，Vue3会通过`track`函数跟踪这个访问，`trackEffect`就是在这个过程中被调用的。

具体工作原理：

1. 当访问响应式对象属性时，Vue3通过`Reflect.get`等操作触发`track`函数。
2. `track`函数会调用`trackEffect`，将当前激活的副作用函数（保存在全局变量`activeEffect`中）与当前访问的属性关联起来。这个关联存储在响应式对象的依赖映射表（如`targetMap`）中，建立起“副作用函数 - 数据依赖”的映射关系。
3. 这样，当属性值发生变化时，Vue3就能知道哪些副作用函数需要重新执行。



`triggerEffects` 主要负责触发依赖的更新。当响应式对象的属性值发生变化时，Vue3会通过`trigger`函数触发依赖的更新。

具体工作原理：

1. 当响应式对象属性发生变化时，Vue3通过`Reflect.set`等操作触发`trigger`函数。
2. `trigger`函数会遍历与该属性关联的所有副作用函数（通过依赖映射表获取），并将它们收集到一个数组中。
3. 调用`triggerEffects`函数，遍历这些收集到的副作用函数，逐一触发它们的执行，从而引发视图或其他相关状态的更新。



#### ref

ref和reactive 的区别，ref能存入引用类型和基本类型，但是reactive只能存入引用类型。

ref将传入的值进行包裹，将原始值放在value属性上，对value属性进行劫持。



调用ref-->createRef——进行判断，如果本身就是ref直接返回，不是就进行创建新的ref对象(RefImpl)

```ts
function createRef(rawValue: unknown, shallow: boolean) {
  if (isRef(rawValue)) {
    return rawValue
  }
  return new RefImpl(rawValue, shallow)
}

class RefImpl<T> {
  private _value: T
  private _rawValue: T

  public dep?: Dep = undefined
  public readonly __v_isRef = true

  constructor(
    value: T,
    public readonly __v_isShallow: boolean,
  ) {
    this._rawValue = __v_isShallow ? value : toRaw(value)
    this._value = __v_isShallow ? value : toReactive(value)
  }

  get value() {
    trackRefValue(this)
    return this._value
  }

  set value(newVal) {
    const useDirectValue =
      this.__v_isShallow || isShallow(newVal) || isReadonly(newVal)
    newVal = useDirectValue ? newVal : toRaw(newVal)
    if (hasChanged(newVal, this._rawValue)) {
      this._rawValue = newVal
      this._value = useDirectValue ? newVal : toReactive(newVal)
      triggerRefValue(this, DirtyLevels.Dirty, newVal)
    }
  }
}
```

ref的value是会调用toReactive方法，如果是对象调用reactive方法，否则就是原始值

```ts
export const toReactive = <T extends unknown>(value: T): T =>
  isObject(value) ? reactive(value) : value

```

get进行拦截是使用trackRefValue实际上是调用了trackeffect方法（和reactive进行劫持一样的，`在reactiveEffect中`）

然后生成一个dep对象，进行`监视数据`（更准确的说是管理`依赖关系`的对象，类似于桥梁，将数据更新和视图变化联系起来），使用它来收集所有订阅了这个属性的观察者

1. 当一个响应式对象的属性被访问（读取）时，Vue 会调用 `track` 函数，此时如果存在活跃的副作用函数（`activeEffect`），则将这个副作用函数添加到该属性所对应的 `Dep` 对象的依赖列表中。
2. 当该属性的值发生改变时，Vue 会调用 `trigger` 函数，遍历并触发与该属性相关的所有 `Dep` 对象中的所有副作用函数，通知它们重新运行，以此实现视图的自动更新。

set进行拦截主要是调用的triggerEffect进行拦截

triggerEffect主要步骤：

1. 先调用`pauseScheduling`进行暂停调度器。
2. 遍历`dep`中的所有副作用函数（`effect`）：
    - 检查当前副作用函数的脏级别是否小于传入的`dirtyLevel`，如果是并且`dep`中存储的`trackId`与此副作用函数当前的`_trackId`一致，那么继续执行。
    - 更新副作用函数的脏级别为传入的`dirtyLevel`。
    - 如果之前该副作用函数的脏级别为`DirtyLevels.NotDirty`（即还未执行过），将其标记为应该被调度，并在开发环境时调用`onTrigger`钩子函数（如果有），同时附加上调试信息。
    - 调用副作用函数的`trigger`方法，实际执行副作用逻辑（通常是重新渲染组件）。
3. 调用`scheduleEffects(dep)`对符合条件的副作用函数进行调度，决定何时执行这些函数。
4. 最后调用`resetScheduling`恢复调度器的工作。

```ts
export function triggerEffects(
  dep: Dep,
  dirtyLevel: DirtyLevels,
  debuggerEventExtraInfo?: DebuggerEventExtraInfo,
) {
  pauseScheduling()
  for (const effect of dep.keys()) {
    if (
      effect._dirtyLevel < dirtyLevel &&
      dep.get(effect) === effect._trackId
    ) {
      const lastDirtyLevel = effect._dirtyLevel
      effect._dirtyLevel = dirtyLevel
      if (lastDirtyLevel === DirtyLevels.NotDirty) {
        effect._shouldSchedule = true
        if (__DEV__) {
          effect.onTrigger?.(extend({ effect }, debuggerEventExtraInfo))
        }
        effect.trigger()
      }
    }
  }
  scheduleEffects(dep)
  resetScheduling()
}
```

但是reactive进行拦截实现的更多。

reactive的set拦截在`baseHanlder`中的MutableReactiveHandler，里面进行了shallow和readonly的判断，然后比较新旧值，其不同才调用的trigger方法。

两者的不同之处：

**`trigger` 函数**：

- 定义：`trigger` 函数负责处理响应式对象（如对象、数组或 Map 等）在数据发生变化时的具体触发逻辑。
- 功能：当数据变化时，`trigger` 函数首先根据变化类型（如添加、删除、修改或清空等）和具体的键值信息，从响应式对象的依赖映射表（`depsMap`）中收集所有相关的依赖（`Dep` 对象）。
- 结果：收集完成后，`trigger` 函数会暂停调度器，然后逐个触发这些依赖（`Dep` 对象），并通过调用 `triggerEffects` 函数来执行对应的副作用函数（如组件的渲染函数等）。

**`triggerEffects` 函数**：

- 定义：`triggerEffects` 函数则是真正执行副作用函数的地方。
- 功能：接收一个 `Dep` 对象和一个脏级别作为参数。`Dep` 对象包含了一组关联的副作用函数，脏级别决定了哪些副作用函数应该被触发执行。
- 结果：遍历 `Dep` 对象中的所有副作用函数，根据它们的脏级别和调度状态，决定是否执行副作用函数。执行副作用函数会导致视图更新或其他相应的行为。







#### computed

1. **创建内部结构**：
    - 在 `computed.ts` 内部，Vue3 会通过 `computedRef` 或类似的工厂函数创建一个特殊的引用（Ref），这个引用具有追踪依赖的能力。
    - 这个引用背后维护了一个 `getter` 函数和一个可选的 `setter` 函数，以及对依赖关系的跟踪。
2. **依赖追踪**：
    - 当首次读取计算属性时，它会执行 `getter` 函数，并使用响应式系统去追踪在其内部访问的所有其他响应式状态。
    - 这些依赖项会被记录在一个依赖集合（Dep）中，与当前计算属性相关联。
3. **缓存与懒计算**：
    - 计算属性的结果会被缓存起来，只有当它的依赖项发生改变时，才会重新计算。
    - 如果任何依赖的状态改变，Vue3 会通过响应式系统的 `trigger` 函数，找到依赖了该改变状态的所有计算属性，并通过 `triggerEffects` 触发它们的更新。
4. **更新视图**：
    - 当计算属性值发生变化时，由于它是响应式的，因此会自动触发依赖它的视图更新或者其他订阅者。
5. **访问计算属性**：
    - 在模板或者 JavaScript 中，可以直接像访问普通 Ref 一样访问计算属性，Vue3 的响应式系统会确保在正确的时间点获取最新且正确的计算结果。 	

在使用计算属性的时候，是将一个函数或者一个配置对象作为参数传入`computed`

也就是调用了computed这个函数

```ts
export function computed<T>(
  getter: ComputedGetter<T>,
  debugOptions?: DebuggerOptions,
): ComputedRef<T>
export function computed<T>(
  options: WritableComputedOptions<T>,
  debugOptions?: DebuggerOptions,
): WritableComputedRef<T>
export function computed<T>(
  getterOrOptions: ComputedGetter<T> | WritableComputedOptions<T>,
  debugOptions?: DebuggerOptions,
  isSSR = false,
) {
  let getter: ComputedGetter<T>
  let setter: ComputedSetter<T>

  const onlyGetter = isFunction(getterOrOptions)
  if (onlyGetter) {
    getter = getterOrOptions
    setter = __DEV__
      ? () => {
          console.warn('Write operation failed: computed value is readonly')
        }
      : NOOP
  } else {
    getter = getterOrOptions.get
    setter = getterOrOptions.set
  }

  const cRef = new ComputedRefImpl(getter, setter, onlyGetter || !setter, isSSR)

  if (__DEV__ && debugOptions && !isSSR) {
    cRef.effect.onTrack = debugOptions.onTrack
    cRef.effect.onTrigger = debugOptions.onTrigger
  }

  return cRef as any
}

```

第一个重载就是只包含一个 getter 函数：

当仅传入一个 getter 函数时，表明这是一个只读计算属性。getter 函数用于计算值，而 setter 被默认设置为一个空操作（noop），并在开发环境下打印警告信息，提示用户尝试修改只读计算属性。

第二个是只包含options的函数

当传入一个选项对象时，此对象应该包含 `get` 和 `set` 属性，分别对应计算属性的 getter 和 setter 函数。这样创建的是一个可读写的计算属性。

传入之后，判断是否是函数还是对象，然后分别给`getter和setter`

然后根据这些创建一个 ComputedRefImpl

```ts
export class ComputedRefImpl<T> {
  public dep?: Dep = undefined

  private _value!: T
  public readonly effect: ReactiveEffect<T>

  public readonly __v_isRef = true
  public readonly [ReactiveFlags.IS_READONLY]: boolean = false

  public _cacheable: boolean

  constructor(
    getter: ComputedGetter<T>,
    private readonly _setter: ComputedSetter<T>,
    isReadonly: boolean,
    isSSR: boolean,
  ) {
    this.effect = new ReactiveEffect(
      () => getter(this._value),
      () => triggerRefValue(this, DirtyLevels.MaybeDirty),
      () => this.dep && scheduleEffects(this.dep),
    )
    this.effect.computed = this
    this.effect.active = this._cacheable = !isSSR
    this[ReactiveFlags.IS_READONLY] = isReadonly
  }

  get value() {
    // the computed ref may get wrapped by other proxies e.g. readonly() #3376
    const self = toRaw(this)
    if (!self._cacheable || self.effect.dirty) {
      if (hasChanged(self._value, (self._value = self.effect.run()!))) {
        triggerRefValue(self, DirtyLevels.Dirty)
      }
    }
    trackRefValue(self)
    if (self.effect._dirtyLevel >= DirtyLevels.MaybeDirty) {
      triggerRefValue(self, DirtyLevels.MaybeDirty)
    }
    return self._value
  }

  set value(newValue: T) {
    this._setter(newValue)
  }

  // #region polyfill _dirty for backward compatibility third party code for Vue <= 3.3.x
  get _dirty() {
    return this.effect.dirty
  }

  set _dirty(v) {
    this.effect.dirty = v
  }
  // #endregion
}
```



这个对象是会生成一个effect，其作用是：计算属性的依赖收集、更新调度、结果缓存以及自定义副作用逻辑。

1. **依赖收集**： 当计算属性的 `getter` 函数被调用时，与之关联的 `effect` 会跟踪并收集所有访问到的响应式依赖。这意味着它会记录下哪些响应式状态（如 `ref`、`reactive` 对象属性）被计算属性所依赖。
2. **调度更新**： 当计算属性的依赖项发生变化时，响应式系统会触发这些依赖项的更新。对应的 `effect` 会检测到依赖变化，进而重新执行 `getter` 函数以计算新的值，并根据新值更新相关联的视图或其它依赖于计算属性的组件状态。
3. **懒计算与缓存**： 通过 `effect`，Vue3 能够实现计算属性的懒计算和结果缓存机制。只有当计算属性的依赖发生变化时，才会重新执行 `getter` 函数并更新结果，否则会直接返回缓存的值，从而提高性能。
4. **自定义副作用行为**： 开发者可以在创建 `effect` 时传递自定义的副作用函数和其他选项，允许更灵活地控制副作用函数的执行时机和行为，比如在跟踪依赖时附加额外的调试信息、或者在触发时执行额外的逻辑。



effect是`ReactiveEffect`（也就是处理`响应式副作用`的类）

ReactiveEffect传入的东西，第一个是取值调用的函数，第二个是设置值调用的函数，第三个是调度器，第四个是作用域（可选）

```ts
export class ReactiveEffect<T = any> {
  active = true
  deps: Dep[] = []

  /**
   * Can be attached after creation
   * @internal
   */
  computed?: ComputedRefImpl<T>
  /**
   * @internal
   */
  allowRecurse?: boolean

  onStop?: () => void
  // dev only
  onTrack?: (event: DebuggerEvent) => void
  // dev only
  onTrigger?: (event: DebuggerEvent) => void

  /**
   * @internal
   */
  _dirtyLevel = DirtyLevels.Dirty
  /**
   * @internal
   */
  _trackId = 0
  /**
   * @internal
   */
  _runnings = 0
  /**
   * @internal
   */
  _shouldSchedule = false
  /**
   * @internal
   */
  _depsLength = 0

  constructor(
    public fn: () => T,
    public trigger: () => void,
    public scheduler?: EffectScheduler,
    scope?: EffectScope,
  ) {
    recordEffectScope(this, scope)
  }

  public get dirty() {
    if (this._dirtyLevel === DirtyLevels.MaybeDirty) {
      pauseTracking()
      for (let i = 0; i < this._depsLength; i++) {
        const dep = this.deps[i]
        if (dep.computed) {
          triggerComputed(dep.computed)
          if (this._dirtyLevel >= DirtyLevels.Dirty) {
            break
          }
        }
      }
      if (this._dirtyLevel < DirtyLevels.Dirty) {
        this._dirtyLevel = DirtyLevels.NotDirty
      }
      resetTracking()
    }
    return this._dirtyLevel >= DirtyLevels.Dirty
  }

  public set dirty(v) {
    this._dirtyLevel = v ? DirtyLevels.Dirty : DirtyLevels.NotDirty
  }

  run() {
    this._dirtyLevel = DirtyLevels.NotDirty
    if (!this.active) {
      return this.fn()
    }
    let lastShouldTrack = shouldTrack
    let lastEffect = activeEffect
    try {
      shouldTrack = true
      activeEffect = this
      this._runnings++
      preCleanupEffect(this)
      return this.fn()
    } finally {
      postCleanupEffect(this)
      this._runnings--
      activeEffect = lastEffect
      shouldTrack = lastShouldTrack
    }
  }

  stop() {
    if (this.active) {
      preCleanupEffect(this)
      postCleanupEffect(this)
      this.onStop?.()
      this.active = false
    }
  }
}
```



`public get dirty` 方法：

- 返回一个布尔值，表示当前 `ReactiveEffect` 是否为“脏”。在获取过程中，如果当前的“脏”级别是 `DirtyLevels.MaybeDirty`，则会进一步检查其依赖的计算属性（`deps` 数组中的 `computed` 对象）是否也“脏”，并递归地触发它们以确定最终的“脏”状态。最终返回当前 `ReactiveEffect` 是否需要重新执行。

`public set dirty(v)` 方法：

- 设置 `ReactiveEffect` 的“脏”状态。如果参数 `v` 为 `true`，则设置其为需要重新执行（`DirtyLevels.Dirty`）；否则设置为不需要重新执行（`DirtyLevels.NotDirty`）。



其中还有run方法是在computed取值时调用。



<img src="Vue3%E6%BA%90%E7%A0%81%E5%AD%A6%E4%B9%A0.assets/image-20240120200533859.png" alt="image-20240120200533859" style="zoom:67%;" />

- 当取value值时触发`get value`方法
    - 首先，它会检查当前计算属性实例（`this`）是否可缓存（`_cacheable`）以及与其关联的副作用函数（`effect`）是否脏（需要重新计算）。如果需要重新计算，则执行副作用函数（`effect.run()`）并更新`_value`。
    - 使用`hasChanged`函数检查新计算的值与原有值是否不同，如果不同，则触发计算属性的值变更事件（`triggerRefValue`）并设置为脏（`DirtyLevels.Dirty`）。
    - 之后，无论是否需要重新计算，都会调用`trackRefValue`来追踪计算属性的依赖，这是Vue3响应式系统依赖收集的关键步骤。
    - 最后，如果副作用函数的脏级别至少为`MaybeDirty`，也会触发计算属性的值变更事件，但设置为`MaybeDirty`级别。
- 当更新值时
    - 这是计算属性的`value`属性的setter方法，对于可写计算属性（WritableComputed），当试图设置计算属性的值时会调用。
    - 它通过调用预设的`_setter`函数来设置计算属性的值，`_setter`是在创建计算属性时传入的setter函数。
- 剩下两个是为了向后兼容版本低于3.3的



Tips：这里涉及到依赖收集

>对于普通的例如
>
>​	reactive是采用的   reactiveEffect文件下的track和trigger函数进行收集依赖。
>
>​	track调用了trackEffect方法；trigger调用的triggerEffects方法
>
>​	Ref是采用的trackRefValue调用了 trackEffect方法，triggerRefValue调用了triggerEffects方法

而对于计算属性

>其get value内部调用的triggerRefValue()，set调用的_setter（也就是创建时传入的set函数）。

希望不要被绕晕







## runtime-core

这章不仅涉及到组件的基础和生命周期，此外还涉及到一些高级api的实现



### 组件基础和生命周期



#### component.ts

主要是实现了 Vue3 组件的核心功能，涵盖了组件的整个生命周期，确保组件能够在响应式数据变化时正确地创建、更新和销毁，以及在此过程中调用相应的生命周期钩子函数。

组件的创建

uid是组件的编号，每一个组件的编号不同

```typescript
export function createComponentInstance(
  vnode: VNode,
  parent: ComponentInternalInstance | null,
  suspense: SuspenseBoundary | null,
) {
  const type = vnode.type as ConcreteComponent
  // inherit parent app context - or - if root, adopt from root vnode
  const appContext =
    (parent ? parent.appContext : vnode.appContext) || emptyAppContext

  const instance: ComponentInternalInstance = {
    uid: uid++,
    vnode,
    type,
    parent,
    appContext,
    root: null!, // to be immediately set
    next: null,
    subTree: null!, // will be set synchronously right after creation
    effect: null!,
    update: null!, // will be set synchronously right after creation
    scope: new EffectScope(true /* detached */),
    render: null,
    proxy: null,
    exposed: null,
    exposeProxy: null,
    withProxy: null,
    provides: parent ? parent.provides : Object.create(appContext.provides),
    accessCache: null!,
    renderCache: [],

    // local resolved assets
    components: null,
    directives: null,

    // resolved props and emits options
    propsOptions: normalizePropsOptions(type, appContext),
    emitsOptions: normalizeEmitsOptions(type, appContext),

    // emit
    emit: null!, // to be set immediately
    emitted: null,

    // props default value
    propsDefaults: EMPTY_OBJ,

    // inheritAttrs
    inheritAttrs: type.inheritAttrs,

    // state
    ctx: EMPTY_OBJ,
    data: EMPTY_OBJ,
    props: EMPTY_OBJ,
    attrs: EMPTY_OBJ,
    slots: EMPTY_OBJ,
    refs: EMPTY_OBJ,
    setupState: EMPTY_OBJ,
    setupContext: null,

    attrsProxy: null,
    slotsProxy: null,

    // suspense related
    suspense,
    suspenseId: suspense ? suspense.pendingId : 0,
    asyncDep: null,
    asyncResolved: false,

    // lifecycle hooks
    // not using enums here because it results in computed properties
    isMounted: false,
    isUnmounted: false,
    isDeactivated: false,
    bc: null,
    c: null,
    bm: null,
    m: null,
    bu: null,
    u: null,
    um: null,
    bum: null,
    da: null,
    a: null,
    rtg: null,
    rtc: null,
    ec: null,
    sp: null,
  }
  if (__DEV__) {
    instance.ctx = createDevRenderContext(instance)
  } else {
    instance.ctx = { _: instance }
  }
  instance.root = parent ? parent.root : instance
  instance.emit = emit.bind(null, instance)

  // apply custom element special handling
  if (vnode.ce) {
    vnode.ce(instance)
  }

  return instance
}
```

包含组件的各个信息，包括，父组件，子组件，数据，插槽等等



定义了组件之后，就是组件的初始化。

也就是调用的`setupComponent`函数

```typescript
export function setupComponent(
  instance: ComponentInternalInstance,
  isSSR = false,
) {
  isSSR && setInSSRSetupState(isSSR)

  const { props, children } = instance.vnode
  const isStateful = isStatefulComponent(instance)
  initProps(instance, props, isStateful, isSSR)
  initSlots(instance, children)

  const setupResult = isStateful
    ? setupStatefulComponent(instance, isSSR)
    : undefined

  isSSR && setInSSRSetupState(false)
  return setupResult
}
```

这里初始化了props（属性，定义在componentProps.ts）和slot（插槽，定义在componentSlots.ts）

initProps主要干了：

1. **初始化props和attrs对象**：
    - 创建空的`props`和`attrs`对象，用于存储组件实例的props和非prop属性（HTML attributes）。
2. **设置attrs的元信息**：
    - 使用`def`函数设置`attrs`对象的元信息，表明它是一个内部Vue对象。
3. **初始化props默认值**：
    - 设置`instance.propsDefaults`为一个空对象，用于存储组件props的默认值。
4. **填充props和attrs**：
    - 调用`setFullProps`函数，根据传入的原始props(`rawProps`)填充`props`和`attrs`对象。
5. **确保声明的props存在**：
    - 遍历组件声明的props选项，若某个声明的props未在`props`对象中找到，则将其值设为`undefined`。
6. **验证props**：
    - 在开发环境下，调用`validateProps`函数验证props的有效性，确保props的类型和格式符合预期。
7. **根据组件类型设置props和attrs**：
    - 根据组件是否是状态化组件（`isStateful`）：
        - 如果是状态化组件并且不是服务器端渲染（SSR），将props对象转换为浅响应式对象并赋值给组件实例的`props`属性。
        - 如果是状态化组件并且是SSR，直接将props赋值给组件实例的`props`属性。
        - 如果是非状态化组件（函数式组件）：
            - 如果组件没有声明props，那么props和attrs指向同一个对象。
            - 如果组件声明了props，则将填充后的props对象赋值给组件实例的`props`属性。
8. **设置attrs**：
    - 不论组件类型如何，都将填充后的attrs对象赋值给组件实例的`attrs`属性。





initSlots主要干了：

1. **判断是否存在slots**：
    - 首先检查组件实例的vnode（虚拟节点）的形状标志（shapeFlag）是否包含`ShapeFlags.SLOTS_CHILDREN`，表示子组件接受插槽内容。
2. **处理已编译插槽**：
    - 如果存在已编译的插槽（即type属性存在），则提取插槽类型，并将原始的（非代理的）插槽内容赋值给组件实例的`slots`属性，同时设置`_`属性为插槽类型，但设置为不可枚举。
3. **标准化对象插槽**：
    - 如果插槽内容是对象形式的原始插槽，调用`normalizeObjectSlots`函数，将原始插槽对象规范化，并填充到组件实例的`slots`属性中。
4. **处理默认插槽和命名插槽**：
    - 如果不存在已编译的插槽，或者插槽内容不是对象形式，则为组件实例分配一个空的`slots`对象。如果`children`参数不为空，则调用`normalizeVNodeSlots`函数，将常规的VNode子节点（包括默认插槽和命名插槽）转换为适合内部使用的格式。
5. **设置元信息**：
    - 最后，不论何种情况，都会在组件实例的`slots`属性上设置元信息，标记为内部对象。

这里，isStateful是用来判断当前组件是否“有状态”，即拥有setup的组件（即通过options创建的）

setupStatefulComponent函数

```typescript
function setupStatefulComponent(
  instance: ComponentInternalInstance,
  isSSR: boolean,
) {
  const Component = instance.type as ComponentOptions

  if (__DEV__) {
    if (Component.name) {
      validateComponentName(Component.name, instance.appContext.config)
    }
    if (Component.components) {
      const names = Object.keys(Component.components)
      for (let i = 0; i < names.length; i++) {
        validateComponentName(names[i], instance.appContext.config)
      }
    }
    if (Component.directives) {
      const names = Object.keys(Component.directives)
      for (let i = 0; i < names.length; i++) {
        validateDirectiveName(names[i])
      }
    }
    if (Component.compilerOptions && isRuntimeOnly()) {
      warn(
        `"compilerOptions" is only supported when using a build of Vue that ` +
          `includes the runtime compiler. Since you are using a runtime-only ` +
          `build, the options should be passed via your build tool config instead.`,
      )
    }
  }
  // 0. create render proxy property access cache
  instance.accessCache = Object.create(null)
  // 1. create public instance / render proxy
  // also mark it raw so it's never observed
  instance.proxy = markRaw(new Proxy(instance.ctx, PublicInstanceProxyHandlers))
  if (__DEV__) {
    exposePropsOnRenderContext(instance)
  }
  // 2. call setup()
  const { setup } = Component
  if (setup) {
    const setupContext = (instance.setupContext =
      setup.length > 1 ? createSetupContext(instance) : null)

    const reset = setCurrentInstance(instance)
    pauseTracking()
    const setupResult = callWithErrorHandling(
      setup,
      instance,
      ErrorCodes.SETUP_FUNCTION,
      [
        __DEV__ ? shallowReadonly(instance.props) : instance.props,
        setupContext,
      ],
    )
    resetTracking()
    reset()

    if (isPromise(setupResult)) {
      setupResult.then(unsetCurrentInstance, unsetCurrentInstance)
      if (isSSR) {
        // return the promise so server-renderer can wait on it
        return setupResult
          .then((resolvedResult: unknown) => {
            handleSetupResult(instance, resolvedResult, isSSR)
          })
          .catch(e => {
            handleError(e, instance, ErrorCodes.SETUP_FUNCTION)
          })
      } else if (__FEATURE_SUSPENSE__) {
        // async setup returned Promise.
        // bail here and wait for re-entry.
        instance.asyncDep = setupResult
        
      } else if (__DEV__) {
        warn(
          `setup() returned a Promise, but the version of Vue you are using ` +
            `does not support it yet.`,
        )
      }
    } else {
      handleSetupResult(instance, setupResult, isSSR)
    }
  } else {
    finishComponentSetup(instance, isSSR)
  }
}
```



1. 获取组件实例的类型（ComponentOptions），并对开发环境下的组件名称、组件内的组件和指令名称进行验证，确保它们符合规范。
2. 初始化组件实例的`accessCache`属性，这是一个用于存储属性访问缓存的对象。
3. 创建组件实例的代理（proxy）对象，该对象公开了一些公共方法和属性，同时被标记为`markRaw`，意味着不会被Vue的响应式系统追踪。
4. 在开发环境下，将props暴露到渲染上下文中以供IDE工具提示和调试。
5. 获取组件的`setup`函数，如果有`setup`函数，则执行以下步骤：
    - 创建`setupContext`对象，用于在`setup`函数中访问props和emit等上下文信息。
    - 使用`setCurrentInstance`设置当前组件实例，并暂停依赖收集（pauseTracking）。
    - 执行`setup`函数，捕获错误并传递props和setupContext作为参数。
    - 重置依赖收集（resetTracking）并还原当前组件实例（resetCurrentInstance）。
6. 判断`setup`函数的返回值是否为Promise：
    - 如果是Promise，根据环境（SSR与否及是否支持Suspense）处理异步结果。如果是SSR，等待Promise解决后继续处理；如果是客户端渲染且支持Suspense，将Promise保存到asyncDep属性中，等待Suspense边界；否则抛出警告。
    - 如果不是Promise，直接处理同步的结果（调用`handleSetupResult`函数）。
7. 如果组件没有`setup`函数，则调用`finishComponentSetup`函数完成组件的剩余初始化工作。



```ts
export function createSetupContext(
  instance: ComponentInternalInstance,
): SetupContext {
  const expose: SetupContext['expose'] = exposed => {
    instance.exposed = exposed || {}
  }
    return {
      get attrs() {
        return getAttrsProxy(instance)
      },
      slots: instance.slots,
      emit: instance.emit,
      expose,
    }
}
```

创建上下文对象，包含了插槽，触发，还有向外暴露的对象，以及非prop属性的代理对象

该函数就是创建了一个上下文对象（删除了一部分东西）

```ts
export function finishComponentSetup(
  instance: ComponentInternalInstance,
  isSSR: boolean,
  skipOptions?: boolean,
) {
  const Component = instance.type as ComponentOptions

  // template / render function normalization
  // could be already set when returned from setup()
  if (!instance.render) {
    // only do on-the-fly compile if not in SSR - SSR on-the-fly compilation
    // is done by server-renderer
    if (!isSSR && compile && !Component.render) {
      const template =
        (__COMPAT__ &&
          instance.vnode.props &&
          instance.vnode.props['inline-template']) ||
        Component.template ||
        resolveMergedOptions(instance).template
      if (template) {
        if (__DEV__) {
          startMeasure(instance, `compile`)
        }
        const { isCustomElement, compilerOptions } = instance.appContext.config
        const { delimiters, compilerOptions: componentCompilerOptions } =
          Component
        const finalCompilerOptions: CompilerOptions = extend(
          extend(
            {
              isCustomElement,
              delimiters,
            },
            compilerOptions,
          ),
          componentCompilerOptions,
        )
        
        Component.render = compile(template, finalCompilerOptions)
        if (__DEV__) {
          endMeasure(instance, `compile`)
        }
      }
    }

    instance.render = (Component.render || NOOP) as InternalRenderFunction

    // for runtime-compiled render functions using `with` blocks, the render
    // proxy used needs a different `has` handler which is more performant and
    // also only allows a whitelist of globals to fallthrough.
    if (installWithProxy) {
      installWithProxy(instance)
    }
  }

  // support for 2.x options
  if (__FEATURE_OPTIONS_API__ && !(__COMPAT__ && skipOptions)) {
    const reset = setCurrentInstance(instance)
    pauseTracking()
    try {
      applyOptions(instance)
    } finally {
      resetTracking()
      reset()
    }
  }

  // warn missing template/render
  // the runtime compilation of template in SSR is done by server-render
  
}

```

组件的props，slots，attrs等初始化之后就是，要进行模版编译了。

模版编译需要看是否存在render函数，如果不存在

- 确保组件实例`render`有有效的

    函数。如果没有，函数会尝试从以下途径获取并编译模板：

    - 组件实例的`vnode`属性中的`inline-template`属性。
    - 组件选项（ComponentOptions）中的`template`属性。
    - 组件全局合并选项中的`template`。

- 编译发生在非SSR情况下，因为在SSR环境下编译工作由服务器渲染器完成。

- 编译时会合并全局和组件级别的编译选项，并在开发环境下记录编译时间。





```ts
export let currentInstance: ComponentInternalInstance | null = null

export const setCurrentInstance = (instance: ComponentInternalInstance) => {
  const prev = currentInstance
  internalSetCurrentInstance(instance)
  instance.scope.on()
  return () => {
    instance.scope.off()
    internalSetCurrentInstance(prev)
  }
}
export const getCurrentInstance: () => ComponentInternalInstance | null = () =>
  currentInstance || currentRenderingInstance

type CompileFunction = (
  template: string | object,
  options?: CompilerOptions,
) => InternalRenderFunction

let compile: CompileFunction | undefined
let installWithProxy: (i: ComponentInternalInstance) => void
export function registerRuntimeCompiler(_compile: any) {
  compile = _compile
  installWithProxy = i => {
    if (i.render!._rc) {
      i.withProxy = new Proxy(i.ctx, RuntimeCompiledPublicInstanceProxyHandlers)
    }
  }
}
```



这一堆是辅助处理组件实例的当前上下文和编译相关的

1. **currentInstance**:
    - 定义一个全局变量 `currentInstance`，它用于存储当前正在执行 `setup` 函数或其它内部操作的组件实例。这个变量在Vue3的内部逻辑中非常重要，因为它提供了在执行过程中的组件上下文信息。
2. **setCurrentInstance**:
    - 定义一个函数 `setCurrentInstance`，用于设置当前组件实例，并返回一个清理函数。当进入一个组件的 `setup` 函数或其他内部处理时，调用这个函数将当前组件实例设置为 `currentInstance`。清理函数在离开当前组件上下文时调用，恢复之前的 `currentInstance` 值，并解除组件实例的副作用监听。
3. **getCurrentInstance**:
    - 提供一个 `getCurrentInstance` 函数，它返回当前的 `ComponentInternalInstance` 或 `null`。在编写Composition API时，可以通过这个函数获取当前组件实例，进而访问其属性、方法以及上下文信息。
4. **CompileFunction**:
    - 定义一个类型 `CompileFunction`，描述一个用于编译模板字符串或对象为内部渲染函数的函数签名。
5. **compile** 和 **installWithProxy**:
    - `compile` 变量用于存储模板编译函数，`installWithProxy` 用于安装一个代理，使得在使用 `with` 块的运行时编译渲染函数中能更高效地访问全局变量。初始时它们都被设置为 `undefined`。
6. **registerRuntimeCompiler**:
    - 定义一个 `registerRuntimeCompiler` 函数，它接收一个编译函数 `_compile` 参数，并将其赋值给全局变量 `compile`。同时，该函数还初始化了 `installWithProxy` 函数，用于在运行时编译的组件实例上安装代理。当组件实例的渲染函数已经经过运行时编译时，这个函数会为该组件实例创建一个代理，使得在模板渲染时能正确处理 `with` 块等特性。



组件相关的文件

#### ComponentEmits.ts

```ts
export function emit(
  instance: ComponentInternalInstance,
  event: string,
  ...rawArgs: any[]
) {
  if (instance.isUnmounted) return
  const props = instance.vnode.props || EMPTY_OBJ

  
  let args = rawArgs
  const isModelListener = event.startsWith('update:')

  // for v-model update:xxx events, apply modifiers on args
  const modelArg = isModelListener && event.slice(7)
  if (modelArg && modelArg in props) {
    const modifiersKey = `${
      modelArg === 'modelValue' ? 'model' : modelArg
    }Modifiers`
    const { number, trim } = props[modifiersKey] || EMPTY_OBJ
    if (trim) {
      args = rawArgs.map(a => (isString(a) ? a.trim() : a))
    }
    if (number) {
      args = rawArgs.map(looseToNumber)
    }
  }


  let handlerName
  let handler =
    props[(handlerName = toHandlerKey(event))] ||
    // also try camelCase event handler (#2249)
    props[(handlerName = toHandlerKey(camelize(event)))]
  // for v-model update:xxx events, also trigger kebab-case equivalent
  // for props passed via kebab-case
  if (!handler && isModelListener) {
    handler = props[(handlerName = toHandlerKey(hyphenate(event)))]
  }

  if (handler) {
    callWithAsyncErrorHandling(
      handler,
      instance,
      ErrorCodes.COMPONENT_EVENT_HANDLER,
      args,
    )
  }

  const onceHandler = props[handlerName + `Once`]
  if (onceHandler) {
    if (!instance.emitted) {
      instance.emitted = {}
    } else if (instance.emitted[handlerName]) {
      return
    }
    instance.emitted[handlerName] = true
    callWithAsyncErrorHandling(
      onceHandler,
      instance,
      ErrorCodes.COMPONENT_EVENT_HANDLER,
      args,
    )
  }

  if (__COMPAT__) {
    compatModelEmit(instance, event, args)
    return compatInstanceEmit(instance, event, args)
  }
}
```

1. 检查组件实例是否已经卸载（`isUnmounted`），如果已卸载则直接返回，不触发任何事件。
2. 获取组件实例的VNode（虚拟节点）上的props对象。
3. 处理`v-model`相关事件：
    - 检查事件名是否以`update:`开头，若是，则认为这是一个`v-model`更新事件（如`update:modelValue`）。
    - 对应的model属性（如`modelValue`）在props中查找是否有修饰符（如`number`和`trim`），如有则按需对传递的参数进行转换（数字转换或去除首尾空白字符）。
4. 查找事件对应的处理器（handler）：
    - 根据原始事件名和驼峰式事件名（如`change`和`onChange`）在props对象中查找事件处理器。
5. 调用事件处理器（handler）：
    - 如果找到了事件处理器，则使用`callWithAsyncErrorHandling`包装调用，以处理可能发生的错误，并提供错误处理的上下文。
    - 如果事件处理器中有一次性执行的版本（`onceHandler`），则在首次触发时调用，并将触发状态存储在组件实例的`emitted`对象中，避免重复触发。

emit 是基于 props 里面的 onXXX 的函数来进行匹配的





#### ComponentProps

这里面最主要的就是初始化props

```ts
export function initProps(
  instance: ComponentInternalInstance,
  rawProps: Data | null,
  isStateful: number, // result of bitwise flag comparison
  isSSR = false,
) {
  const props: Data = {}
  const attrs: Data = {}
  def(attrs, InternalObjectKey, 1)

  instance.propsDefaults = Object.create(null)

  setFullProps(instance, rawProps, props, attrs)

  // ensure all declared prop keys are present
  for (const key in instance.propsOptions[0]) {
    if (!(key in props)) {
      props[key] = undefined
    }
  }

  // validation
  if (__DEV__) {
    validateProps(rawProps || {}, props, instance)
  }

  if (isStateful) {
    // stateful
    instance.props = isSSR ? props : shallowReactive(props)
  } else {
    if (!instance.type.props) {
      // functional w/ optional props, props === attrs
      instance.props = attrs
    } else {
      // functional w/ declared props
      instance.props = props
    }
  }
  instance.attrs = attrs
}
```

 这里处理了两个东西`attrs`和`props`，并且初始化了props的默认值。

然后调用setFullProps，以rawProps为蓝本，填充props和attrs

ensure all declared prop keys are present

然后根据isStateful给props进行赋值，如果不是有状态的组件，且未声明props就将props设置为attrs，因为此时两者相同。

props，是父组件向子组件传递的数据。

attrs，是所有传递给组件但并未在props中声明的HTML属性（也叫做非props属性）





#### ComponentSlots.ts

```ts
export const initSlots = (
  instance: ComponentInternalInstance,
  children: VNodeNormalizedChildren,
) => {
  if (instance.vnode.shapeFlag & ShapeFlags.SLOTS_CHILDREN) {
    const type = (children as RawSlots)._
    if (type) {
      // users can get the shallow readonly version of the slots object through `this.$slots`,
      // we should avoid the proxy object polluting the slots of the internal instance
      instance.slots = toRaw(children as InternalSlots)
      // make compiler marker non-enumerable
      def(children as InternalSlots, '_', type)
    } else {
      normalizeObjectSlots(
        children as RawSlots,
        (instance.slots = {}),
        instance,
      )
    }
  } else {
    instance.slots = {}
    if (children) {
      normalizeVNodeSlots(instance, children)
    }
  }
  def(instance.slots, InternalObjectKey, 1)
}
```

其作用：

1. **检测插槽类型**：
    - 首先检查组件实例的vnode（虚拟节点）的形状标志（shapeFlag）是否设置了`ShapeFlags.SLOTS_CHILDREN`，这意味着组件有子节点作为插槽内容。
2. **处理已编译插槽**：
    - 如果存在已编译的插槽（通过检查`(children as RawSlots)._`是否存在及其类型），则将原始插槽内容转换为非响应式对象赋值给组件实例的`slots`属性，并且设置`_`属性为插槽类型，同时确保该属性不可枚举。
3. **处理未编译插槽**：
    - 如果插槽未编译，或者类型不匹配，则调用`normalizeObjectSlots`函数将原始插槽内容规范化，并填充到组件实例的`slots`属性中。
4. **初始化默认插槽**：
    - 如果组件没有带`ShapeFlags.SLOTS_CHILDREN`标识的插槽，初始化一个空的`slots`对象，然后调用`normalizeVNodeSlots`函数处理默认插槽内容。



```ts
const normalizeObjectSlots = (
  rawSlots: RawSlots,
  slots: InternalSlots,
  instance: ComponentInternalInstance,
) => {
  const ctx = rawSlots._ctx
  for (const key in rawSlots) {
    if (isInternalKey(key)) continue
    const value = rawSlots[key]
    if (isFunction(value)) {
      slots[key] = normalizeSlot(key, value, ctx)
    } else if (value != null) {
      if (
        __DEV__ &&
        !(
          __COMPAT__ &&
          isCompatEnabled(DeprecationTypes.RENDER_FUNCTION, instance)
        )
      ) {
        warn(
          `Non-function value encountered for slot "${key}". ` +
            `Prefer function slots for better performance.`,
        )
      }
      const normalized = normalizeSlotValue(value)
      slots[key] = () => normalized
    }
  }
}
```

1. 获取原始插槽对象的上下文（`ctx`），这个上下文通常包含组件实例的相关信息，如组件的props、methods等。
2. 遍历原始插槽对象的所有属性（这里指代各个插槽名称）。
3. 对于每个插槽名称（`key`），首先检查是否是内部保留的关键字（通过`isInternalKey`函数判断），如果是则跳过此次循环。
4. 如果插槽值（`value`）是一个函数，则调用`normalizeSlot`函数对其进行规范化处理，并将结果存入新的`slots`对象中。
5. 如果插槽值不是函数，但其值不为`null`，则在开发环境下进行性能提示（如果启用了兼容性检查，且当前不支持旧版渲染函数），提醒开发者最好使用函数形式的插槽以获得更好的性能。
6. 对于非函数的插槽值，调用`normalizeSlotValue`函数将其规范化为一个返回值恒定的函数，并将此函数存入新的`slots`对象中。

将原始插槽对象按照vue的标准进行转化，以便组件内部能够正确识别



```ts
const normalizeSlot = (
  key: string,
  rawSlot: Function,
  ctx: ComponentInternalInstance | null | undefined,
): Slot => {
  if ((rawSlot as any)._n) {
    // already normalized - #5353
    return rawSlot as Slot
  }
  const normalized = withCtx((...args: any[]) => {
    return normalizeSlotValue(rawSlot(...args))
  }, ctx) as Slot
  // NOT a compiled slot
  ;(normalized as ContextualRenderFn)._c = false
  return normalized
}
const normalizeSlotValue = (value: unknown): VNode[] =>
  isArray(value)
    ? value.map(normalizeVNode)
    : [normalizeVNode(value as VNodeChild)]


```

nomalizeSlotValue是将，值变为VNode数组进行返回

normalized._c = false表示这不是一个编译过的插槽函数，然后返回这个新函数



#### ComponentPublicInstance.ts

```ts
export const publicPropertiesMap: PublicPropertiesMap =
  // Move PURE marker to new line to workaround compiler discarding it
  // due to type annotation
  /*#__PURE__*/ extend(Object.create(null), {
    $: i => i,
    $el: i => i.vnode.el,
    $data: i => i.data,
    $props: i => (__DEV__ ? shallowReadonly(i.props) : i.props),
    $attrs: i => (__DEV__ ? shallowReadonly(i.attrs) : i.attrs),
    $slots: i => (__DEV__ ? shallowReadonly(i.slots) : i.slots),
    $refs: i => (__DEV__ ? shallowReadonly(i.refs) : i.refs),
    $parent: i => getPublicInstance(i.parent),
    $root: i => getPublicInstance(i.root),
    $emit: i => i.emit,
    $options: i => (__FEATURE_OPTIONS_API__ ? resolveMergedOptions(i) : i.type),
    $forceUpdate: i =>
      i.f ||
      (i.f = () => {
        i.effect.dirty = true
        queueJob(i.update)
      }),
    $nextTick: i => i.n || (i.n = nextTick.bind(i.proxy!)),
    $watch: i => (__FEATURE_OPTIONS_API__ ? instanceWatch.bind(i) : NOOP),
  } as PublicPropertiesMap)
```

这里是定义组件实例的各种属性和方法



```ts
export const PublicInstanceProxyHandlers: ProxyHandler<any> = {
  get({ _: instance }: ComponentRenderContext, key: string) {
    const { ctx, setupState, data, props, accessCache, type, appContext } =
      instance

    // for internal formatters to know that this is a Vue instance


    // data / props / ctx
    // This getter gets called for every property access on the render context
    // during render and is a major hotspot. The most expensive part of this
    // is the multiple hasOwn() calls. It's much faster to do a simple property
    // access on a plain object, so we use an accessCache object (with null
    // prototype) to memoize what access type a key corresponds to.
    let normalizedProps
    if (key[0] !== '$') {
      const n = accessCache![key]
      if (n !== undefined) {
        switch (n) {
          case AccessTypes.SETUP:
            return setupState[key]
          case AccessTypes.DATA:
            return data[key]
          case AccessTypes.CONTEXT:
            return ctx[key]
          case AccessTypes.PROPS:
            return props![key]
          // default: just fallthrough
        }
      } else if (hasSetupBinding(setupState, key)) {
        accessCache![key] = AccessTypes.SETUP
        return setupState[key]
      } else if (data !== EMPTY_OBJ && hasOwn(data, key)) {
        accessCache![key] = AccessTypes.DATA
        return data[key]
      } else if (
        // only cache other properties when instance has declared (thus stable)
        // props
        (normalizedProps = instance.propsOptions[0]) &&
        hasOwn(normalizedProps, key)
      ) {
        accessCache![key] = AccessTypes.PROPS
        return props![key]
      } else if (ctx !== EMPTY_OBJ && hasOwn(ctx, key)) {
        accessCache![key] = AccessTypes.CONTEXT
        return ctx[key]
      } else if (!__FEATURE_OPTIONS_API__ || shouldCacheAccess) {
        accessCache![key] = AccessTypes.OTHER
      }
    }

    const publicGetter = publicPropertiesMap[key]
    let cssModule, globalProperties
    // public $xxx properties
    if (publicGetter) {
      if (key === '$attrs') {
        track(instance, TrackOpTypes.GET, key)
        __DEV__ && markAttrsAccessed()
      } else if (__DEV__ && key === '$slots') {
        track(instance, TrackOpTypes.GET, key)
      }
      return publicGetter(instance)
    } else if (
      // css module (injected by vue-loader)
      (cssModule = type.__cssModules) &&
      (cssModule = cssModule[key])
    ) {
      return cssModule
    } else if (ctx !== EMPTY_OBJ && hasOwn(ctx, key)) {
      // user may set custom properties to `this` that start with `$`
      accessCache![key] = AccessTypes.CONTEXT
      return ctx[key]
    } else if (
      // global properties
      ((globalProperties = appContext.config.globalProperties),
      hasOwn(globalProperties, key))
    ) {
      if (__COMPAT__) {
        const desc = Object.getOwnPropertyDescriptor(globalProperties, key)!
        if (desc.get) {
          return desc.get.call(instance.proxy)
        } else {
          const val = globalProperties[key]
          return isFunction(val)
            ? Object.assign(val.bind(instance.proxy), val)
            : val
        }
      } else {
        return globalProperties[key]
      }
    } else if (
      __DEV__ &&
      currentRenderingInstance &&
      (!isString(key) ||
        // #1091 avoid internal isRef/isVNode checks on component instance leading
        // to infinite warning loop
        key.indexOf('__v') !== 0)
    ) {
      if (data !== EMPTY_OBJ && isReservedPrefix(key[0]) && hasOwn(data, key)) {
        warn(
          `Property ${JSON.stringify(
            key,
          )} must be accessed via $data because it starts with a reserved ` +
            `character ("$" or "_") and is not proxied on the render context.`,
        )
      } else if (instance === currentRenderingInstance) {
        warn(
          `Property ${JSON.stringify(key)} was accessed during render ` +
            `but is not defined on instance.`,
        )
      }
    }
  },

  set(
    { _: instance }: ComponentRenderContext,
    key: string,
    value: any,
  ): boolean {
    const { data, setupState, ctx } = instance
    if (hasSetupBinding(setupState, key)) {
      setupState[key] = value
      return true
    } else if (
      __DEV__ &&
      setupState.__isScriptSetup &&
      hasOwn(setupState, key)
    ) {
      warn(`Cannot mutate <script setup> binding "${key}" from Options API.`)
      return false
    } else if (data !== EMPTY_OBJ && hasOwn(data, key)) {
      data[key] = value
      return true
    } else if (hasOwn(instance.props, key)) {
      __DEV__ && warn(`Attempting to mutate prop "${key}". Props are readonly.`)
      return false
    }
    if (key[0] === '$' && key.slice(1) in instance) {
      __DEV__ &&
        warn(
          `Attempting to mutate public property "${key}". ` +
            `Properties starting with $ are reserved and readonly.`,
        )
      return false
    } else {
      if (__DEV__ && key in instance.appContext.config.globalProperties) {
        Object.defineProperty(ctx, key, {
          enumerable: true,
          configurable: true,
          value,
        })
      } else {
        ctx[key] = value
      }
    }
    return true
  },

  
    return Reflect.defineProperty(target, key, descriptor)
  },
}
```

需要让用户可以直接在 render 函数内直接使用 this 来触发 proxy。

它用于创建Vue组件实例的公开代理对象。这个代理对象可以让开发者在模板或`setup`函数之外访问组件实例的部分内部状态，如props、data、context、setupState等。

- `get`：当访问代理对象的属性时调用，用于根据访问的键值返回对应的属性值。它首先会尝试从不同的来源（setupState、data、props、context、globalProperties等）查找属性值，并利用缓存（accessCache）提高查找效率。
- `set`：当尝试修改代理对象的属性值时调用，用于设置对应属性的新值。它同样会检查属性来源，并根据规则决定是否允许修改。



#### ComponentRenderUtils.ts

```ts
export function shouldUpdateComponent(
  prevVNode: VNode,
  nextVNode: VNode,
  optimized?: boolean,
): boolean {
  const { props: prevProps, children: prevChildren, component } = prevVNode
  const { props: nextProps, children: nextChildren, patchFlag } = nextVNode
  const emits = component!.emitsOptions

  // Parent component's render function was hot-updated. Since this may have
  // caused the child component's slots content to have changed, we need to
  // force the child to update as well.
  if (__DEV__ && (prevChildren || nextChildren) && isHmrUpdating) {
    return true
  }

  // force child update for runtime directive or transition on component vnode.
  if (nextVNode.dirs || nextVNode.transition) {
    return true
  }

  if (optimized && patchFlag >= 0) {
    if (patchFlag & PatchFlags.DYNAMIC_SLOTS) {
      // slot content that references values that might have changed,
      // e.g. in a v-for
      return true
    }
    if (patchFlag & PatchFlags.FULL_PROPS) {
      if (!prevProps) {
        return !!nextProps
      }
      // presence of this flag indicates props are always non-null
      return hasPropsChanged(prevProps, nextProps!, emits)
    } else if (patchFlag & PatchFlags.PROPS) {
      const dynamicProps = nextVNode.dynamicProps!
      for (let i = 0; i < dynamicProps.length; i++) {
        const key = dynamicProps[i]
        if (
          nextProps![key] !== prevProps![key] &&
          !isEmitListener(emits, key)
        ) {
          return true
        }
      }
    }
  } else {
    // this path is only taken by manually written render functions
    // so presence of any children leads to a forced update
    if (prevChildren || nextChildren) {
      if (!nextChildren || !(nextChildren as any).$stable) {
        return true
      }
    }
    if (prevProps === nextProps) {
      return false
    }
    if (!prevProps) {
      return !!nextProps
    }
    if (!nextProps) {
      return true
    }
    return hasPropsChanged(prevProps, nextProps, emits)
  }

  return false
}
function hasPropsChanged(
  prevProps: Data,
  nextProps: Data,
  emitsOptions: ComponentInternalInstance['emitsOptions'],
): boolean {
  const nextKeys = Object.keys(nextProps)
  if (nextKeys.length !== Object.keys(prevProps).length) {
    return true
  }
  for (let i = 0; i < nextKeys.length; i++) {
    const key = nextKeys[i]
    if (
      nextProps[key] !== prevProps[key] &&
      !isEmitListener(emitsOptions, key)
    ) {
      return true
    }
  }
  return false
}

```

用于判断一个组件是否需要更新的逻辑

1. 父组件热更新：如果当前环境是开发环境并且父组件正在进行热更新（HMR），则强制子组件更新。
2. 当前虚拟节点上有运行时指令或过渡效果：如果有运行时指令或过渡效果，则不论其他因素，都需要更新组件。
3. 优化后的patchFlag（补丁标记）：根据patchFlag判断是否需要更新。例如，如果标记表示动态插槽内容发生变化，或者props发生改变，即使进行了优化也需要更新。
4. 手动编写的render函数：对于手动编写的render函数，只要有子节点变化或者props不同，就需要更新。
5. `比较props的变化`：在非优化路径下，逐一对比props的变化，同时考虑到组件的`emitsOptions`（组件声明的emit事件），只有当props实际发生变化，并且该变化的prop不是emit事件监听器所关注的，才判定需要更新组件。

hasPropsChanged是对props更加细致的比较

`shouldUpdateComponent`函数在Vue3的虚拟DOM diff过程中被调用，具体调用时机是在组件树的更新阶段。当Vue确定需要更新视图时，它会遍历组件树并对每个组件生成新的虚拟节点（VNode）。对于每一个旧虚拟节点（`prevVNode`）和新虚拟节点（`nextVNode`）对，Vue会调用`shouldUpdateComponent`函数来判断是否有必要对该组件进行更新。





#### VNode

实现虚拟结点：vnode

创建节点：

```ts
export const createVNode = (
  __DEV__ ? createVNodeWithArgsTransform : _createVNode
) as typeof _createVNode

function _createVNode(
  type: VNodeTypes | ClassComponent | typeof NULL_DYNAMIC_COMPONENT,
  props: (Data & VNodeProps) | null = null,
  children: unknown = null,
  patchFlag: number = 0,
  dynamicProps: string[] | null = null,
  isBlockNode = false,
): VNode {
  if (!type || type === NULL_DYNAMIC_COMPONENT) {
    if (__DEV__ && !type) {
      warn(`Invalid vnode type when creating vnode: ${type}.`)
    }
    type = Comment
  }

  if (isVNode(type)) {
    // createVNode receiving an existing vnode. This happens in cases like
    // <component :is="vnode"/>
    // #2078 make sure to merge refs during the clone instead of overwriting it
    const cloned = cloneVNode(type, props, true /* mergeRef: true */)
    if (children) {
      normalizeChildren(cloned, children)
    }
    if (isBlockTreeEnabled > 0 && !isBlockNode && currentBlock) {
      if (cloned.shapeFlag & ShapeFlags.COMPONENT) {
        currentBlock[currentBlock.indexOf(type)] = cloned
      } else {
        currentBlock.push(cloned)
      }
    }
    cloned.patchFlag |= PatchFlags.BAIL
    return cloned
  }

  // class component normalization.
  if (isClassComponent(type)) {
    type = type.__vccOpts
  }

  // 2.x async/functional component compat
  if (__COMPAT__) {
    type = convertLegacyComponent(type, currentRenderingInstance)
  }

  // class & style normalization.
  if (props) {
    // for reactive or proxy objects, we need to clone it to enable mutation.
    props = guardReactiveProps(props)!
    let { class: klass, style } = props
    if (klass && !isString(klass)) {
      props.class = normalizeClass(klass)
    }
    if (isObject(style)) {
      // reactive state objects need to be cloned since they are likely to be
      // mutated
      if (isProxy(style) && !isArray(style)) {
        style = extend({}, style)
      }
      props.style = normalizeStyle(style)
    }
  }

  // encode the vnode type information into a bitmap
  const shapeFlag = isString(type)
    ? ShapeFlags.ELEMENT
    : __FEATURE_SUSPENSE__ && isSuspense(type)
      ? ShapeFlags.SUSPENSE
      : isTeleport(type)
        ? ShapeFlags.TELEPORT
        : isObject(type)
          ? ShapeFlags.STATEFUL_COMPONENT
          : isFunction(type)
            ? ShapeFlags.FUNCTIONAL_COMPONENT
            : 0

  if (__DEV__ && shapeFlag & ShapeFlags.STATEFUL_COMPONENT && isProxy(type)) {
    type = toRaw(type)
    warn(
      `Vue received a Component that was made a reactive object. This can ` +
        `lead to unnecessary performance overhead and should be avoided by ` +
        `marking the component with \`markRaw\` or using \`shallowRef\` ` +
        `instead of \`ref\`.`,
      `\nComponent that was made reactive: `,
      type,
    )
  }

  return createBaseVNode(
    type,
    props,
    children,
    patchFlag,
    dynamicProps,
    shapeFlag,
    isBlockNode,
    true,
  )
}
```

这个函数主要是检验属性和类型是否合格

1. 如果传入的类型本身就是VNode，则克隆并合并相关属性及子节点；
2. 处理类组件的相关配置；
3. 对于类(class)和样式(style)属性，进行规范化处理，确保它们可以正确地应用到DOM；
4. 根据类型计算VNode的形状标识(shapeFlag)，这决定了VNode代表的是普通元素、组件、 suspense、 teleport等不同类型的节点；
5. 最后，通过调用`createBaseVNode`进一步创建基础VNode对象，并传递所有必要的参数。



```ts
function createBaseVNode(
  type: VNodeTypes | ClassComponent | typeof NULL_DYNAMIC_COMPONENT,
  props: (Data & VNodeProps) | null = null,
  children: unknown = null,
  patchFlag = 0,
  dynamicProps: string[] | null = null,
  shapeFlag = type === Fragment ? 0 : ShapeFlags.ELEMENT,
  isBlockNode = false,
  needFullChildrenNormalization = false,
) {
  const vnode = {
    __v_isVNode: true,
    __v_skip: true,
    type,
    props,
    key: props && normalizeKey(props),
    ref: props && normalizeRef(props),
    scopeId: currentScopeId,
    slotScopeIds: null,
    children,
    component: null,
    suspense: null,
    ssContent: null,
    ssFallback: null,
    dirs: null,
    transition: null,
    el: null,
    anchor: null,
    target: null,
    targetAnchor: null,
    staticCount: 0,
    shapeFlag,
    patchFlag,
    dynamicProps,
    dynamicChildren: null,
    appContext: null,
    ctx: currentRenderingInstance,
  } as VNode

  if (needFullChildrenNormalization) {
    normalizeChildren(vnode, children)
    // normalize suspense children
    if (__FEATURE_SUSPENSE__ && shapeFlag & ShapeFlags.SUSPENSE) {
      ;(type as typeof SuspenseImpl).normalize(vnode)
    }
  } else if (children) {
    // compiled element vnode - if children is passed, only possible types are
    // string or Array.
    vnode.shapeFlag |= isString(children)
      ? ShapeFlags.TEXT_CHILDREN
      : ShapeFlags.ARRAY_CHILDREN
  }

  // validate key
  if (__DEV__ && vnode.key !== vnode.key) {
    warn(`VNode created with invalid key (NaN). VNode type:`, vnode.type)
  }

  // track vnode for block tree
  if (
    isBlockTreeEnabled > 0 &&
    // avoid a block node from tracking itself
    !isBlockNode &&
    // has current parent block
    currentBlock &&
    // presence of a patch flag indicates this node needs patching on updates.
    // component nodes also should always be patched, because even if the
    // component doesn't need to update, it needs to persist the instance on to
    // the next vnode so that it can be properly unmounted later.
    (vnode.patchFlag > 0 || shapeFlag & ShapeFlags.COMPONENT) &&
    // the EVENTS flag is only for hydration and if it is the only flag, the
    // vnode should not be considered dynamic due to handler caching.
    vnode.patchFlag !== PatchFlags.NEED_HYDRATION
  ) {
    currentBlock.push(vnode)
  }

  if (__COMPAT__) {
    convertLegacyVModelProps(vnode)
    defineLegacyVNodeProperties(vnode)
  }

  return vnode
}
```

这里最终是返回了一个vnode对象，以便生成ast语法树

1. 构造VNode对象的基本结构，设置各种属性，如类型（type）、属性（props）、子节点（children）、patchFlag（用于优化更新过程的标记位）、动态属性（dynamicProps）、形状标识（shapeFlag，区分元素、组件、fragment等不同类型节点）、是否为块级节点（isBlockNode）等。
2. 正常化children属性，如果需要的话。这一步会对子节点进行处理，确保它们符合预期的格式。
3. 根据children的类型，设置VNode的形状标识（shapeFlag）以区别文本节点还是数组子节点。
4. 验证key属性的有效性。
5. 如果开启了block tree追踪，并且当前存在一个父block，且VNode需要进行patch更新（根据patchFlag和shapeFlag判断），则将当前VNode加入到block中。

```ts
export const Text = Symbol.for('v-txt')//全局注册symbol
export const Comment = Symbol.for('v-cmt')
export const Static = Symbol.for('v-stc')
export const Fragment = Symbol.for('v-fgt') as any as {
  __isFragment: true
  new (): {
    $props: VNodeProps
  }
}

export function createTextVNode(text: string = ' ', flag: number = 0): VNode {
  return createVNode(Text, null, text, flag)
}
export function createStaticVNode(
  content: string,
  numberOfNodes: number,
): VNode {
  // A static vnode can contain multiple stringified elements, and the number
  // of elements is necessary for hydration.
  const vnode = createVNode(Static, null, content)
  vnode.staticCount = numberOfNodes
  return vnode
}
export function createCommentVNode(
  text: string = '',
  // when used as the v-else branch, the comment node must be created as a
  // block to ensure correct updates.
  asBlock: boolean = false,
): VNode {
  return asBlock
    ? (openBlock(), createBlock(Comment, null, text))
    : createVNode(Comment, null, text)
}


export function normalizeVNode(child: VNodeChild): VNode {
  if (child == null || typeof child === 'boolean') {
    // empty placeholder
    return createVNode(Comment)
  } else if (isArray(child)) {
    // fragment
    return createVNode(
      Fragment,
      null,
      // #3666, avoid reference pollution when reusing vnode
      child.slice(),
    )
  } else if (typeof child === 'object') {
    // already vnode, this should be the most common since compiled templates
    // always produce all-vnode children arrays
    return cloneIfMounted(child)
  } else {
    // strings and numbers
    return createVNode(Text, null, String(child))
  }
}
```

这里分别创建文本节点，静态节点，注释节点，还有标准化vnode，让child支持更多格式



#### scheduler.ts

这一章的执行情况，有点懵，主要是与异步任务有关

由名字可知，这是与调度器相关的。

`nextTick`重点

声明，isFlushPending,queue（任务队列）

```ts
let isFlushPending = false
const queue: SchedulerJob[] = []
const resolvedPromise = /*#__PURE__*/ Promise.resolve() as Promise<any>
let activePostFlushCbs: SchedulerJob[] | null = null
let currentFlushPromise: Promise<void> | null = null

```

```ts
export function nextTick<T = void, R = void>(
  this: T,
  fn?: (this: T) => R,
): Promise<Awaited<R>> {
  const p = currentFlushPromise || resolvedPromise
  return fn ? p.then(this ? fn.bind(this) : fn) : p
}
```





```ts
export function queueJob(job: SchedulerJob) {
  // the dedupe search uses the startIndex argument of Array.includes()
  // by default the search index includes the current job that is being run
  // so it cannot recursively trigger itself again.
  // if the job is a watch() callback, the search will start with a +1 index to
  // allow it recursively trigger itself - it is the user's responsibility to
  // ensure it doesn't end up in an infinite loop.
  if (
    !queue.length ||
    !queue.includes(
      job,
      isFlushing && job.allowRecurse ? flushIndex + 1 : flushIndex,
    )
  ) {
    if (job.id == null) {
      queue.push(job)
    } else {
      queue.splice(findInsertionIndex(job.id), 0, job)
    }
    queueFlush()
  }
}
```

queueJob常见触发时机：

1. 当响应式数据发生变化时，Vue会调用`trigger`函数，进而调用`queueJob`将更新视图的任务放入队列中，等待微任务阶段执行。
2. 用户在组件内使用`watch` API 监听数据变化时，当监听的响应式数据发生变化，对应的回调函数会被包装成一个任务并通过`queueJob`函数加入到任务队列中。
3. 用户调用`setTimeout`、`Promise.then`等异步API时，Vue会把在其内部进行视图更新的操作封装成任务并调用`queueJob`。

总结下来，queueJob在需要异步更新的地方被调度使用

比如在这些地方。

<img src="Vue3%E6%BA%90%E7%A0%81%E5%AD%A6%E4%B9%A0.assets/image-20240121191631142.png" alt="image-20240121191631142" style="zoom: 80%;" />

- 作用：将一个异步任务（`SchedulerJob`）添加到调度队列中。Vue中的异步任务可以是组件的渲染、watcher回调、effect（副作用）等。
- 关系：通过调用此函数将任务放入队列，等待下一轮事件循环中被调度执行。



queueFlush

```ts
function queueFlush() {
  if (!isFlushing && !isFlushPending) {
    isFlushPending = true
    currentFlushPromise = resolvedPromise.then(flushJobs)
  }
}
```

如果同时触发两个组件的更新，这里就会触发两次then，但是没有这个必要。

1. 首先，函数检查两个状态变量`isFlushing`和`isFlushPending`。`isFlushing`表示是否正在执行任务队列中的工作，`isFlushPending`表示是否已安排在下一个异步时机执行任务队列。
2. 如果当前既不在执行任务队列（`!isFlushing`），也没有安排在将来执行（`!isFlushPending`），那么就将`isFlushPending`设为`true`，表示当前已安排了任务队列的执行。
3. 然后，它调用`resolvedPromise.then(flushJobs)`。这里的`resolvedPromise`是一个已经解决的Promise对象，调用其`then`方法可以在下一次微任务轮询时执行`flushJobs`函数。`flushJobs`函数负责从任务队列中取出并执行所有待处理的任务。



- 作用：检查当前是否已有异步更新在进行或已安排进行。如果没有，则标记异步更新已安排，并调用`resolvedPromise.then(flushJobs)`，使得在下一个微任务中执行`flushJobs`函数，开始处理队列中的任务。
- 关系：`queueJob`在添加任务后通常会调用`queueFlush`来触发任务的执行。



```ts
export function queuePostFlushCb(cb: SchedulerJobs) {
  if (!isArray(cb)) {
    if (
      !activePostFlushCbs ||
      !activePostFlushCbs.includes(
        cb,
        cb.allowRecurse ? postFlushIndex + 1 : postFlushIndex,
      )
    ) {
      pendingPostFlushCbs.push(cb)
    }
  } else {
    // if cb is an array, it is a component lifecycle hook which can only be
    // triggered by a job, which is already deduped in the main queue, so
    // we can skip duplicate check here to improve perf
    pendingPostFlushCbs.push(...cb)
  }
  queueFlush()
}

```

1. 检查传入的回调函数`cb`是否为数组。如果不是数组，则将其视为单个回调函数处理。
    - 如果`activePostFlushCbs`（当前活跃的post-flush回调队列）为空，或者`cb`不在活跃队列中（通过`includes`方法判断，考虑是否允许递归触发以及当前索引`postFlushIndex`），则将`cb`推入`pendingPostFlushCbs`（等待执行的post-flush回调队列）中。
    - 如果`cb`是一个数组，则认为它是由组件生命周期钩子组成的，这些钩子已经在主任务队列中去重，所以这里可以略过重复检查，直接将整个数组推入`pendingPostFlushCbs`。
2. 不论是否添加了新的回调函数，都会调用`queueFlush()`函数。这是因为，即使添加的是post-flush回调，也需要触发一次异步更新流程以确保所有同步任务完成后再执行这些回调。

安排执行那些需要在DOM更新后执行的回调函数。



- 作用：将一个post-flush回调函数（`SchedulerJob`）添加到post-flush回调队列中。这些回调会在DOM更新之后执行，通常用于处理DOM交互、资源清理等操作。
- 关系：同样在添加回调后调用`queueFlush`来确保回调在合适的时机执行。



```ts
function flushJobs(seen?: CountMap) {
  isFlushPending = false
  isFlushing = true
  if (__DEV__) {
    seen = seen || new Map()
  }

  // Sort queue before flush.
  // This ensures that:
  // 1. Components are updated from parent to child. (because parent is always
  //    created before the child so its render effect will have smaller
  //    priority number)
  // 2. If a component is unmounted during a parent component's update,
  //    its update can be skipped.
  queue.sort(comparator)

  // conditional usage of checkRecursiveUpdate must be determined out of
  // try ... catch block since Rollup by default de-optimizes treeshaking
  // inside try-catch. This can leave all warning code unshaked. Although
  // they would get eventually shaken by a minifier like terser, some minifiers
  // would fail to do that (e.g. https://github.com/evanw/esbuild/issues/1610)
  const check = __DEV__
    ? (job: SchedulerJob) => checkRecursiveUpdates(seen!, job)
    : NOOP

  try {
    for (flushIndex = 0; flushIndex < queue.length; flushIndex++) {
      const job = queue[flushIndex]
      if (job && job.active !== false) {
        if (__DEV__ && check(job)) {
          continue
        }
        callWithErrorHandling(job, null, ErrorCodes.SCHEDULER)
      }
    }
  } finally {
    flushIndex = 0
    queue.length = 0

    flushPostFlushCbs(seen)

    isFlushing = false
    currentFlushPromise = null
    // some postFlushCb queued jobs!
    // keep flushing until it drains.
    if (queue.length || pendingPostFlushCbs.length) {
      flushJobs(seen)
    }
  }
}
```

1. 设置调度状态：首先将`isFlushPending`设置为`false`，表示当前没有待刷新的任务；将`isFlushing`设置为`true`，表示已经开始执行刷新任务。
2. 排序任务队列：根据任务优先级对任务队列`queue`进行排序，确保父组件的更新优先于子组件，这样能保证组件树从父到子有序更新，并且在更新过程中如果某个子组件被卸载，则可以跳过其更新。
3. 遍历任务队列：尝试执行队列中的每个任务。在开发环境中，会检查每个任务是否可能导致递归更新（`checkRecursiveUpdates`），如果是，则跳过本次更新以防止无限循环。
4. 执行任务：调用`callWithErrorHandling`函数来执行每个有效的任务（`active !== false`），并将可能出现的错误报告给全局错误处理程序。
5. 清理状态：遍历完成后，重置`flushIndex`为0，清空`queue`长度，执行所有post-flush回调函数`flushPostFlushCbs`。
6. 结束调度：将`isFlushing`设置回`false`，清空当前的flush promise，并检查是否有剩余的post-flush回调任务或新的任务进入队列。若有，则继续调用`flushJobs`函数以执行剩余任务，直到队列全部清空。

这里先执行的flushPostFlushcbs，然后再继续执行flushjobs



- 作用：执行调度队列中的所有任务。首先对任务队列进行排序，然后依次调用每个任务，同时在开发环境下检查是否有递归更新的情况，避免无限循环。在执行完所有任务后，还会处理post-flush回调队列。
- 关系：由`queueFlush`安排在微任务阶段调用，是任务执行的具体逻辑所在。



在flushPostFlushCbs中

```ts
export function flushPostFlushCbs(seen?: CountMap) {
  if (pendingPostFlushCbs.length) {
    const deduped = [...new Set(pendingPostFlushCbs)].sort(
      (a, b) => getId(a) - getId(b),
    )
    pendingPostFlushCbs.length = 0

    // #1947 already has active queue, nested flushPostFlushCbs call
    if (activePostFlushCbs) {
      activePostFlushCbs.push(...deduped)
      return
    }

    activePostFlushCbs = deduped
    if (__DEV__) {
      seen = seen || new Map()
    }

    for (
      postFlushIndex = 0;
      postFlushIndex < activePostFlushCbs.length;
      postFlushIndex++
    ) {
      if (
        __DEV__ &&
        checkRecursiveUpdates(seen!, activePostFlushCbs[postFlushIndex])
      ) {
        continue
      }
      activePostFlushCbs[postFlushIndex]()
    }
    activePostFlushCbs = null
    postFlushIndex = 0
  }
}
```

1. 首先检查是否存在待处理的post-flush回调（`pendingPostFlushCbs.length`），若存在则进行下一步操作。
2. 将待处理的回调数组去重，并按回调的唯一标识（通过`getId`函数获取）进行排序。
3. 清空原始的`pendingPostFlushCbs`队列。
4. 判断是否有当前活跃的post-flush回调队列（`activePostFlushCbs`）。如果有，则将去重后的回调追加到活跃队列中，然后结束本次函数调用。
5. 若当前无活跃的post-flush回调队列，则将去重后的回调设置为新的活跃队列。
6. 在开发环境中，会创建一个新的`seen`映射表用于记录递归更新检查。
7. 遍历新的活跃post-flush回调队列，执行每个回调。在开发环境下，会先检查回调是否会导致递归更新（`checkRecursiveUpdates`），如果会，则跳过本次执行。
8. 执行完所有回调后，清空活跃的post-flush回调队列（`activePostFlushCbs = null`）以及回调索引（`postFlushIndex = 0`）。



- 作用：执行post-flush回调队列中的所有任务。与`flushJobs`类似，也会进行去重、排序等操作，并在执行每个回调时检查是否有递归更新，然后执行回调函数。
- 关系：在`flushJobs`函数的末尾调用，确保在DOM更新后执行这些回调任务



这五者的关系

`queueJob`和`queuePostFlushCb`负责将任务添加到相应队列，`queueFlush`负责触发任务的执行，而`flushJobs`和`flushPostFlushCbs`则分别处理常规的异步任务队列和post-flush回调队列。（比如DOM更新）

渲染有关

