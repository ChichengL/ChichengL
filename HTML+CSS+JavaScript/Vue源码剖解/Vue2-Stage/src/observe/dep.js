let id = 0;
class Dep{
  constructor(){
    this.id = id++;//属性的dep需要收集watcher
    this.subs = [];//存放着当前属性对应的watcher有哪些
  }
  depend(){
    //为了避免一个模板中使用两个数据导致重复收集,除了dep->watcher还希望watcher->dep
    // this.subs.push(Dep.target);//收集watcher这样写会重复
    Dep.target.addDep(this);//收集dep,先让watcher收集到dep,再让dep存储watcher
    // 一个组件中由多个属性组成(那么对应一个watcher监视多个dep)
  }
  addSub(watcher){
    this.subs.push(watcher);
  }
  notify(){
    this.subs.forEach(watcher => watcher.update());//让视图去更新
  }
}

Dep.target = null;

let stack = [];
export function pushTarget(watcher){
  stack.push(watcher);
  Dep.target = watcher;
  // 渲染时会将watcher入栈，渲染完就出栈
}

export function popTarget(){
  stack.pop();
  Dep.target = stack[stack.length - 1];
}

export default Dep;