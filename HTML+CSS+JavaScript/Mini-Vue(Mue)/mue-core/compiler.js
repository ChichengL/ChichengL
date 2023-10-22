import Viewer from "./viewer.js";
// 模板编译者
class Compiler {
  constructor(mue) {
    this.mue = mue;
    this.el = mue.el;
    this.compile(this.el);
  }

  // 开始编译
  compile(el) {
    const childNodes = el.childNodes; // 真实DOM伪数组
    const childNodesList = Array.from(childNodes); // 转为真数组，进而可以用数组的api
    
    // 前序遍历整个DOM树
    childNodesList.forEach((node,) => {
      // 判断是什么类型的DOM, 扔给不同的处理方法
      if (node.nodeType === 1) { // 元素类型
        this.compileForElement(node);
      } else if (node.nodeType === 3) { // 文本类型
        this.compileForText(node);
      }
      // 如果还有子节点，递归获取下一层
      if (node.childNodes.length) {
        this.compile(node);
      }
    });
  }

    compileForElement(node){
        const reg = /\{(.+?)\}/ ///匹配单括号
        const allAttributes = Array.from(node.attributes)//将节点的属性处理为属性
        //遍历处理数组
        allAttributes.forEach(attribute=>{
            const text = attribute.value
            const matchRes = text.match(reg);//看看能不能匹配上
            if(matchRes){
                const dataKey = matchRes[1];    // 比如匹配的是"{msg}", matchRes[1]就是"msg"

                new Viewer(this.mue, dataKey, (newValue) => {
                    node.textContent = newValue;
                  });//每匹配到一个就创建他的监测者
                const newValue = this.mue.data[dataKey]
                node.value = text.replace(reg, newValue)
                // 实现双向绑定
                node.addEventListener('input', () => { 
                    this.mue.data[dataKey] = node.value;
                  });
              }
        })
    }
    //处理文本类型
    compileForText(node){
        const reg = /\{(.+?)\}/
        const text = node.textContent
        const matchRes = text.match(reg)
        if(matchRes){
            const dataKey = matchRes[1]
            const newText = this.mue.data[dataKey]
            node.textContent = text.replace(reg,newText)
            new Viewer(this.mue,dataKey,(newValue)=>{
                node.textContent = newValue
            })
        }
    }
}
export default Compiler