const serve = require('http').createServer((request,response)=>{
  console.log(request);
  
  response.writeHead(200, {'Content-Type': 'text/plain; charset=UTF-8'})
  response.end('Hello World');
});

serve.listen('8080',()=>{
  console.log('网站启动');
})

