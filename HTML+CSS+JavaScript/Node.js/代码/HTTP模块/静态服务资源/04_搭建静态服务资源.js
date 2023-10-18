const http = require('http')
const fs = require('fs')
const path = require('path')
const mime = {
    'html': 'text/html',
    'css': 'text/css',
    'js': 'text/javascript',
    'json': 'application/json',
    'png': 'image/png',
    'jpg': 'image/jpg',
    'gif': 'image/gif',
    'ico': 'image/x-icon'
}
const server = http.createServer(function(request, response) {
    if(request.method !== 'GET'){
        response.statusCode = 405
        response.end('<h1>405 Method Not Allowed</h1>')
    }
    // 获取url的路径
    let {pathname} = new URL(request.url,'http://127.0.0.1');
    // 拼接文件路径
    let filePath = __dirname+'/page' + pathname;
    // 读取文件
    
    fs.readFile(filePath,(err,data)=>{
        if(err){
            response.setHeader('Content-Type','text/plain;charset=utf-8')
            switch(err.code){
                case 'ENOENT':
                    response.statusCode = 404;
                    response.end('<h1>404 Not Found</h1>');
                    break;
                case 'EPERM':
                    response.statusCode = 403;
                    response.end('<h1>403 Forbidden</h1>');
                    break;
                default:
                    response.statusCode = 500;
                    response.end('<h1>500 Internal Server Error</h1>');
                    break;  
            }
            return;
        }
        let ext = path.extname(filePath).slice(1)
        console.log(ext)
        let type = mime[ext]
        if(type){
            if(type=='html'){
                response.setHeader('Content-Type',type+';charset=utf-8')
            }else{
                response.setHeader('Content-Type',type)
            }
        }else{
            response.setHeader('Content-Type','application/octet-stream')
        }
        response.end(data)
    })
})

server.listen(9000,()=>{
    console.log('服务器启动成功')
})