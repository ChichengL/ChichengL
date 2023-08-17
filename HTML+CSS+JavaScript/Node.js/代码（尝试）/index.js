const serve = require('http').createServer((request,response)=>{
  console.log(request.url);
  response.end('Hello World');
});
const index = require('./index2.js');
console.log(index); 


serve.listen('8080',()=>{
  console.log('启动');
})