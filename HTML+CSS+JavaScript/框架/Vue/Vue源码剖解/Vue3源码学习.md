# Vue3源码学习

整体流程

![整体流程](Vue3%E6%BA%90%E7%A0%81%E5%AD%A6%E4%B9%A0.assets/138114565-3e0eecbb-7fd0-4203-bf36-5e5fd8003ce0.png)



![关键函数调用](Vue3%E6%BA%90%E7%A0%81%E5%AD%A6%E4%B9%A0.assets/68747470733a2f2f696d616765732d313235323630323835302e636f732e61702d6265696a696e672e6d7971636c6f75642e636f6d2f32303232303932373137303635382e706e67)





![img](Vue3%E6%BA%90%E7%A0%81%E5%AD%A6%E4%B9%A0.assets/138115157-1f4fb8a2-7e60-412d-96de-12e68eb0288c.png)



![img](Vue3%E6%BA%90%E7%A0%81%E5%AD%A6%E4%B9%A0.assets/138114969-9139e4af-b2df-41b2-a5d9-069d8b41903c.png)

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