const { log } = require('console');
const http = require('http');
const url = require('url');
const server = http.createServer((request, response) => {
    // let res = url.parse(request.url);
    // // console.log(res);
    // //路径
    // let pathname = res.pathname;

    // //查询字符串
    // let query = res.query;

    let url = new URL(request.url,'http://127.0.0.1')
    console.log(url.pathname);
    console.log(url.searchParams.get('password'));
    response.end('hello world');
})

// 3：监听端口，响应服务
server.listen(9000,()=>{
    console.log('服务器启动成功')
})