// 导入默认的合并策略函数
import { defaultStrat } from './utils'

// 定义strats对象
export const strats = Object.create(null)

// 定义一些特殊的选项名
const hooks = [
  'beforeCreate',
  'created',
  'beforeMount',
  'mounted',
  'beforeUpdate',
  'updated',
  'beforeDestroy',
  'destroyed',
  'activated',
  'deactivated',
  'errorCaptured',
  'serverPrefetch'
]

// 定义一些需要合并为数组的选项名
const ASSET_TYPES = [
  'component',
  'directive',
  'filter'
]

// 定义一些需要递归合并的选项名
const LIFECYCLE_HOOKS = [
  'beforeCreate',
  'created',
  'beforeMount',
  'mounted',
  'beforeUpdate',
  'updated',
  'beforeDestroy',
  'destroyed',
  'activated',
  'deactivated',
  'errorCaptured'
]

// 遍历特殊的选项名
hooks.forEach(hook => {
  // 给strats对象添加以特殊选项名为键的合并策略函数
  strats[hook] = mergeHook
})

// 遍历需要合并为数组的选项名
ASSET_TYPES.forEach(type => {
  // 给strats对象添加以需要合并为数组的选项名为键的合并策略函数
  strats[type + 's'] = mergeAssets
})

// 遍历需要递归合并的选项名
LIFECYCLE_HOOKS.forEach(hook => {
  // 给strats对象添加以需要递归合并的选项名为键的合并策略函数
  strats[hook] = mergeHook
})

// 定义data选项的合并策略函数
strats.data = function (
  parentVal,
  childVal,
){
  // 如果没有子选项，则返回父选项
  if (!childVal) {
    return parentVal
  }
  
  // 如果有子选项，则检查它是否是一个函数，如果不是，则报错
  if (typeof childVal !== 'function') {
    
    return parentVal
  }
  
  // 如果有子选项，并且它是一个函数，则返回一个新的函数，该函数会调用父选项和子选项，并将它们返回的对象进行深度合并，然后返回合并后的对象
  return function mergedDataFn () {
    return mergeData(
      typeof parentVal === 'function' ? parentVal.call(this, this) : parentVal,
      childVal.call(this, this)
    )
  }
}

// 定义props、methods、inject、computed选项的合并策略函数
strats.props =
strats.methods =
strats.inject =
strats.computed = function (
  parentVal,
  childVal,
){
  
   // 如果没有子选项，则返回父选项
   if (!childVal) {
    return parentVal
   }
   
   // 如果有子选项，则检查父选项是否存在，如果不存在，则创建一个空对象作为父选项
   const ret = Object.create(null)
   if (!parentVal) {
    return childVal
   }
   
   // 将父选项和子选项都拷贝到ret对象上，如果有重复的键，则以子选项为准
   extend(ret, parentVal)
   extend(ret, childVal)
   
   // 返回ret对象
   return ret
}

// 定义provide选项的合并策略函数
strats.provide = mergeDataOrFn

// 定义watch选项的合并策略函数
strats.watch = function (
  parentVal,
  childVal,
) {
  
  // 如果没有子选项，则返回父选项
  if (!childVal) return parentVal
  
  // 如果没有父选项，则返回子选项
  if (!parentVal) return childVal
  
  // 创建一个ret对象，用于存储合并后的结果
  const ret = {}
  
  // 将父选项拷贝到ret对象上
  extend(ret, parentVal)
  
  // 遍历子选项的键值
  for (const key in childVal) {
    // 获取子选项的值
    let child = childVal[key]
    // 获取父选项的值
    const parent = parentVal[key]
    
    // 如果父选项有该键值，则将父选项和子选项的值都转换为数组，并合并为一个数组，然后赋给ret对象的该键值
    if (parent && !Array.isArray(parent)) {
      parent = [parent]
    }
    ret[key] = parent
      ? parent.concat(child)
      : Array.isArray(child) ? child : [child]
  }
  
  // 返回ret对象
  return ret
}

function mergeHook (
    parentVal,
    childVal
  ) {
    // 如果有子选项，则返回一个函数，该函数会将父选项和子选项都转换为数组，并合并为一个数组，然后返回该数组
    if (childVal) {
      if (parentVal) {
        return parentVal.concat(childVal)
      } else {
        return Array.isArray(childVal)
          ? childVal
          : [childVal]
      }
    } else {
      // 如果没有子选项，则返回父选项
      return parentVal
    }
  }
  function mergeAssets (
    parentVal,
    childVal,
  ) {
    // 创建一个ret对象，用于存储合并后的结果，它的原型指向父选项
    const ret = Object.create(parentVal || null)
    
    // 如果有子选项，则将子选项拷贝到ret对象上，如果有重复的键，则以子选项为准
    if (childVal) {
      extend(ret, childVal)
    }
    
    // 返回ret对象
    return ret
  }
  // 定义mergeDataOrFn函数
export function mergeDataOrFn (
    parentVal,
    childVal,
    vm
  ) {
    // 如果有vm实例，则说明是当前实例，即通过new Vue()创建的实例
    if (!vm) {
      // 如果没有子选项，则返回父选项
      if (!childVal) {
        return parentVal
      }
      // 如果没有父选项，则返回子选项
      if (!parentVal) {
        return childVal
      }
      // 如果有父选项和子选项，则返回一个新的函数，该函数会调用父选项和子选项，并将它们返回的对象进行深度合并，然后返回合并后的对象
      return function mergedDataFn () {
        return mergeData(
          typeof childVal === 'function' ? childVal.call(vm, vm) : childVal,
          typeof parentVal === 'function' ? parentVal.call(vm, vm) : parentVal
        )
      }
    } else {
      // 如果没有vm实例，则说明是组件实例，即通过Vue.extend()创建的子类
      // 返回一个新的函数，该函数会调用mergeDataOrFn(parentVal, childVal)，并传入vm实例，然后返回其结果
      return function mergedInstanceDataFn () {
        return mergeDataOrFn(parentVal, childVal, vm)
      }
    }
  }
  