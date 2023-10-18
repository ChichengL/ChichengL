const express = require('express')
const fs = require('fs')
const path = require('path')
const app = express()

app.use(express.static(__dirname + '/public'))

app.get('/',(req,res)=>{
    res.send('顶真首页')
})

app.get('/admin',(req,res)=>{
    res.send('后台首页')
})


app.listen(3000,()=>{
    console.log('服务器启动成功')
})
