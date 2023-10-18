const http = require('http');

const server = http.createServer(function(request, response) {
    let {method} = request
    let {pathname} = new URL(request.url,'http://127.0.0.1');
    // console.log(method,pathname)
    response.setHeader('Content-Type','text/html;charset=utf-8')

    if(method=='GET' && pathname == '/login'){
        response.end('登录页面')
    }else if(method=='GET' && pathname == '/reg'){
        response.end('注册页面')
    }else{
        response.end('practise');
    }
})

server.listen(9000,()=>{
    console.log('服务器启动成功')
})