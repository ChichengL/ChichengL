const { log } = require('console');
const http = require('http');

const server = http.createServer((req, res) => {
    res.end('Hello Server')//设置响应体的
    console.log(req.url)
    console.log(req.method);
})

// 3：监听端口，响应服务
server.listen(9000,()=>{
    console.log('服务器启动成功')
})