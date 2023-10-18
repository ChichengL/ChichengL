const express = require('express')
const fs = require('fs')
const path = require('path')
const app = express()

//声明中间件函数
function recordMiddleware(req,res,next){
    let {url,ip} = req
    // console.log(url,ip)
    fs.appendFileSync(path.resolve(__dirname,'./access.log'), `${url}  ${ip}\r\n `)
    next() 
}

//使用中间件
app.use(recordMiddleware)

app.get('/home',(req,res)=>{
    res.send('前台首页')
})

app.get('/admin',(req,res)=>{
    res.send('后台首页')
})
app.get('*',(req,res)=>{
    res.send('<h1>404 Not Found</h1>')
})

app.listen(3000,()=>{
    console.log('服务器启动成功')
})
