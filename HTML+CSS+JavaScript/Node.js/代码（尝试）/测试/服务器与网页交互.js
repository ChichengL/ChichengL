const url = require('url');

const serve = require('http').createServer((request,response)=>{
  const queryObj = url.parse(request.url,true).query
  const [name,age,sex] = [queryObj.name,queryObj.age,queryObj.sex]
  console.log('服务器得到了请求'+name+age+sex)
})

serve.listen(3000,'127.0.0.1')