# 搭建一个服务器(尝试)

index

```js
const serve = require('http').createServer((request,response)=>{//回调函数
  console.log(request.url);
  response.end('Hello World');
});
const index = require('./index2.js');//得到暴露数据
console.log(index); 
serve.listen('8080',()=>{
  console.log('启动');
})
```

index2

```js
module.exports = {
  a:1,
};
```



简介：

**Node.js之 REPL**

Node.js REPL(Read Eval Print Loop:交互式解释器) 表示一个电脑的环境，类似 Window 系统的终端或 Unix/Linux shell，我们可以在终端中输入命令，并接收系统的响应。

REPL 的交互式的编程环境可以实时的验证你所编写的代码，非常适合于验证 Node.js 和 JavaScript 的相关 API。

Node 自带了交互式解释器，可以执行以下任务：

读取 - 读取用户输入，解析输入了Javascript 数据结构并存储在内存中。

执行 - 执行输入的数据结构

打印 - 输出结果

循环 - 循环操作以上步骤直到用户两次按下 ctrl-c 按钮退出。

Node 的交互式解释器可以很好的调试 Javascript 代码。



可以输入以下命令来启动 Node 的终端：

node