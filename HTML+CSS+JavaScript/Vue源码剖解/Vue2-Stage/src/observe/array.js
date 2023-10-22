//重写数组的部分方法

 let oldArrayProto = Array.prototype;//获取数组的原型
export let newArrayProto = Object.create(oldArrayProto);//将原有的原型加在新数组原型上

//找到所有的变异方法

let methods =[
  'push','pop','shift','unshift','splice','sort','reverse'
]
methods.forEach((method)=>{
  //arr.push(1,2,3)
  newArrayProto[method] = function(...args){
    //调用原来的方法修改数组，函数的劫持，切片编程
   const result =  oldArrayProto[method].call(this, ...args);

    // console.log('method',method);

    //对新增的数据再次进行劫持
    let inserted;
    let ob = this.__ob__;
    switch(method){
      case 'push':
      case 'unshift':
        inserted = args;
        break;
      case 'splice'://arr.splice(0,1,{a:1})//第一个是删除的位置，第二个是个数
        inserted = args.slice(2);
        break;
      default:
        break;
    }

    if(inserted){
      //对新增内容再次进行观测,这是新的数组，可以使用observeArray进行观测，那么可以将Observer的实例对象，放在data的某一个值上
      ob.observeArray(inserted);
    }
    ob.dep.notify();
   return result;
  }
})

