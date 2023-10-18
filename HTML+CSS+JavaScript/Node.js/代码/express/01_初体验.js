// 导入express
const express = require('express')

// 创建应用对象
const app = express()

// 创建路由
app.get('/home',(req,res)=>{
    res.end('hello express')
})
// 如果请求方法是get,并且请求的路径是home,那么就会发送响应报文
app.listen(3000,()=>{
    console.log('server is running')
})