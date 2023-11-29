import Publisher from "./publisher.js";
// 数据劫持者
// 数据劫持者
class Hijacker {
    constructor(object,data) {
      this.hijack(object,data);
    }
  
    // Object.defineProperties劫持数据需要拿到 该数据节点 及 其父级对象
    hijack(object, key) {
      // 创建发布者
      const publisher = new Publisher();
      let value = object[key];
      console.log(object,value)
      if (!value) {
         return;
      } else if (typeof value === 'object') { // 当前节点是树，递归;
        // 定义一个空对象，用来存储要定义或修改的属性和描述符
        let props = {};
        // 遍历当前节点的所有属性
        Object.keys(value).forEach((key) => {
          // 递归调用hijack方法，返回一个描述符对象
          props[key] = this.hijack(value, key);
        });
        // 使用Object.defineProperties进行数据劫持
        Object.defineProperties(value, props);
      } else { // 当前节点是叶子节点；object则是其父级节点
        // 上文提到的知识点：JS的this指向
        const that = this;  
        // 返回一个描述符对象
        return {
          // 记住这个get, 这个很重要
          get() {  // 实现反向通知的核心步骤，具体怎么回事在实现Viewer时进一步说明
            if (Publisher.target) { 
              publisher.addViewer(Publisher.target);
            }
            return value;
          },
          
          set(newValue) {
            if (value === newValue) { // 防止死循环: 更新->触发publish->更新->...
              return
            }
            value = newValue;
            if(typeof newValue === 'object'){
                Object.keys(newValue).forEach(key=>{
                    Object.defineProperty(newValue,key,that.hijack(newValue,key))
                })
            } // 提防一首新的数据是树形结构，递归一下
            publisher.publish();
          }
        };
  
      }
    }
  }
  
  export default Hijacker
  