const ncname = `[a-zA-Z_][\\-\\.0-9_a-zA-Z]*`;
const qnameCapture = `((?:${ncname}\\:)?${ncname})`;

const startTagOpen = new RegExp(`^<${qnameCapture}`);//它匹配到的分组是一个标签名<xxx> 匹配开始标签名
const endTag = new RegExp(`^<\\/${qnameCapture}[^>]*>`);//匹配的是</xxx> 最终匹配到结束标签名 分组1是标签名
const attribute = /^\s*([^\s"'<>\/=]+)(?:\s*(=)\s*(?:"([^"]*)"+|'([^']*)'+|([^\s"'=<>`]+)))?/;//匹配属性 a="xxxx" b  =  'xxx' c = xxx
//第一个分组是属性的key，value是分组3或分组4或者分组5
const startTagClose = /^\s*(\/?)>/;   //可以匹配<div>或者<br/>

export function parseHTML(html){// html最开始肯定是一个<
  //最终需要转化为一颗抽象的语法树

  const  ELEMENT_TYPE = 1;//元素类型1
  const TEXT_TYPE = 3;//文本类型3
  const stack = [];//存放标签的栈
  let currentParent = null;//指向栈中的最后一个
  let root = null;//根节点

  function createASTElement(tag,attrs){
    return {
      tag: tag,
      type: ELEMENT_TYPE,
      children: [],
      attrs,
      parent: null
    }
  }


  function start(tag,attrs){//给标签名和属性
    const node = createASTElement(tag,attrs);//创造ast结点
    if(!root){
      root = node;//如果树为空，则为根节点
    }
    if(currentParent){
      node.parent = currentParent;//当前结点的父节点是当前的父节点
      currentParent.children.push(node);//把它父亲结点的儿子指向它；

    }
    stack.push(node);//把当前的标签名压入栈中
    currentParent = node;
  } 
  function chars(text){//文本放在当前结点中
    text = text.replace(/\s/g,'');//如果空格超过两个以上就删除两个以上
    text &&currentParent.children.push({
      type: TEXT_TYPE,
      text,
      parent: currentParent
    })
  }
  function end(tag){
    stack.pop();//弹出最后一个
    currentParent = stack[stack.length - 1];
  }
  function advance(len){
    html = html.substring(len);
  }
  function parseStartTag(){
    const start = html.match(startTagOpen);//
    if(start){
      const match = {
        tagName: start[1],
        attrs: [],
        // start: index
      }
      advance(start[0].length);//匹配上了就进行截取
      // console.log(match,html);
      let attr,end;
      while(!(end = html.match(startTagClose)) &&(attr = html.match(attribute))){
        advance(attr[0].length);
        match.attrs.push({
          name: attr[1],
          value: attr[3] || attr[4] || attr[5] || true
        }) //true是为了弄disabled
      }
      if(end)advance(end[0].length);//结束的尖角号
      return match;
    }
    //如果不是开始标签的结束就一直匹配
    
    // console.log(html);
    return false;
  }
  while(html){
    //如果textEnd为0，说明是一个开始标签或者结束标签   如果textEnd>0说明就是文本的结束位置
    let textEnd = html.indexOf('<');//如果indexOf中的索引是0，则说明是个标签
    if(textEnd === 0){
      const startTagMatch = parseStartTag();//开始标签的匹配结果 
      if(startTagMatch){//解析到开始标签
        start(startTagMatch.tagName,startTagMatch.attrs);
        continue;
      }
      let endTagMatch = html.match(endTag);//匹配结束标签
      if(endTagMatch){
        advance(endTagMatch[0].length);
        end(endTagMatch[1]);
        // console.log(endTagMatch);
        continue;
      }
    }
    if(textEnd > 0){
      let text = html.substring(0,textEnd);//文本内容
      if(text){
        chars(text);//将文本内容传递给chars
        advance(text.length);
      }
    }
  }
  // console.log(root);
  return root;
}