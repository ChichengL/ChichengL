const { log } = require('console');
const http = require('http');

const server = http.createServer((req, res) => {
    let body = '';
    req.on('data',chunk=>{
        body+=chunk;//chunk本身是一个buffer，会自动转会成字符串
    })
    req.on('end',()=>{
        console.log(body)
        res.end('Hello HTTP')
    })
})

// 3：监听端口，响应服务
server.listen(9000,()=>{
    console.log('服务器启动成功')
})