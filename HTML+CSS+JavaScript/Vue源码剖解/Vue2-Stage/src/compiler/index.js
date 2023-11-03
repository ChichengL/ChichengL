import { parseHTML } from "./parse";

function genProps(attrs){
  let str = '';
  for(let i=0;i<attrs.length;i++){
    let attr = attrs[i];
    if(attr.name === 'style'){
      //  color:red ==> {color:'red'}
      let obj = {};
      attr.value.split(';').forEach(item=>{//qs库
        let [key,value] = item.split(':');
        obj[key] = value;
      });
      attr.value = obj;
    }
    str += `${attr.name}:${JSON.stringify(attr.value)},` 
  }
  return `{${str.slice(0,-1)}}`; //去掉最后一个逗号
}

const defaultTagRE = /\{\{((?:.|\r?\n)+?)\}\}/g;//匹配双括号，内容是表达式的变量
function gen(node){
  if(node.type === 1){//说明是元素
    return codegen(node);
  }else{//文本两种情况
    let text = node.text;
    if(!defaultTagRE.test(text)){//纯文本
      return `_v(${JSON.stringify(text)})`;  
    }else{
      //_v(_s(name)+'hello'+_s(age))
      let tokens = [];
      let match;
      defaultTagRE.lastIndex = 0;//从文本开头执行匹配,每次exec后,lastIndex都会更新为下一次匹配开始的位置
      let lastIndex = 0;//最后匹配的位置
      while(match = defaultTagRE.exec(text)){
        //使用正则来捕获文本
        let index = match.index;//匹配的位置
        if(index > lastIndex){//比如 {{name}} hello {{age}},取得就是 hello 这段
          tokens.push(JSON.stringify(text.slice(lastIndex,index)));
        }
        tokens.push(`_s(${match[1].trim()})`)
        lastIndex = index + match[0].length;//更新最后匹配的位置
      }
      // 防止插入语法后面还存在一些文本
      if(lastIndex < text.length){
        tokens.push(JSON.stringify(text.slice(lastIndex)));
      }
      return `_v(${tokens.join('+')})`
    }
  }
}

function genChildren(children){
  return children.map(item=> gen(item));
}

function codegen(ast){
  let children = genChildren(ast.children);
  let code = (`_c('${ast.tag}',${ast.attrs.length > 0 ? genProps(ast.attrs) : 'null'}${ast.children.length > 0 ? `,${children}` : ',null'})`)
  return code;
}

export function compileToFunction(template){
  //1.将template转化为ast语法树
  let ast = parseHTML(template);
  // console.log(ast);
  // 2.生成render函数（render方法执行后返回的结果是虚拟DOM）
  //将ast树生成为类似于下面的字符串
  //  _c('div',{id:'app'},_c('div',{style:{color:'red'}},_v(_s(name)+'hello'),_c('span',undefine,_v(_s(age)))))
  // 
  let code = codegen(ast); 
  code = `with(this){return ${code}}`
  let render = new Function(code);//根据代码生成render函数
  return render;
}