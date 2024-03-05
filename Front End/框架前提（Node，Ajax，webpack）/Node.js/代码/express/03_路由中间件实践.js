const express = require('express')
const fs = require('fs')
const path = require('path')
const app = express()

//声明中间件函数
function recordMiddleware(req,res,next){
    if(req.query.code === '521'){
        next()
    }else{
        res.send('非法访问')
    }
}

//使用中间件
app.use(recordMiddleware)

app.get('/setting',(req,res)=>{
    res.send('后台设置')
})

app.get('/admin',(req,res)=>{
    res.send('后台首页')
})


app.listen(3000,()=>{
    console.log('服务器启动成功')
})
