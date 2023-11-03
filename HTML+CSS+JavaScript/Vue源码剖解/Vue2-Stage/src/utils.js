const strats = {}
const LIFECYCLE = [
    'beforeCreate',
    'created',
]
LIFECYCLE.forEach(hook =>{
    strats[hook] = function (parentVal, childVal) {
        if(childVal){
            if(parentVal){
                return parentVal.concat(childVal)//如果儿子有父亲有，则让父亲儿子拼接在一起
            }else{
                return [childVal]//儿子有父亲没有，则将儿子包装为数组
            }
        }else{
            return parentVal//如果儿子没有父亲有直接返回父亲
        }
    }
})

strats.components = function(parentVal,childVal){
    const res = Object.create(parentVal || null)
    if(childVal){
        for(let key in childVal){
            res[key] = childVal[key] //返回的是构造的对象可以拿到父亲原型上的属性，并且将儿子都拷贝到自己身上
        }
    }
    return res
}

export function mergeOptions(ops = {}, mixin) {
    // 创建一个空对象作为合并后的结果
    const options = {};
    // 定义一个合并策略对象，存放不同属性名对应的合并策略函数
    const strats = {};
    // 定义一个默认的合并策略函数，如果没有找到对应的策略函数，就使用它
    const defaultStrat = function (parentVal, childVal) {
      // 如果子选项有值，就使用子选项的值，否则就使用父选项的值
      return childVal === undefined ? parentVal : childVal;
    };
    // 定义一个合并字段的函数，用于遍历属性并调用合并策略函数
    function mergeField(key) {
      // 根据属性名查找合并策略对象，如果没有找到，就使用默认的合并策略函数
      const strat = strats.hasOwnProperty(key) ? strats[key] : defaultStrat;
      // 调用合并策略函数，传入父选项和子选项的属性值，以及当前的属性名
      options[key] = strat(ops[key], mixin[key], key);
    }
    // 遍历父选项的所有属性，并调用合并字段的函数
    for (let key in ops) {
      mergeField(key);
    }
    // 遍历子选项的所有属性，并调用合并字段的函数
    for (let key in mixin) {
      // 如果父选项没有该属性，才需要调用合并字段的函数
      if (!Object.hasOwn(ops, key)) {
        mergeField(key);
      }
    }
    // 返回合并后的结果对象
    return options;
  }