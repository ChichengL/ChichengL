const express = require('express')
const fs = require('fs')
const path = require('path')
const app = express()
const homeRouter = require('./routes/homeRouter')
const adminRouter = require('./routes/adminRouter')
app.use(homeRouter)

app.use(adminRouter)

app.get('*',(req,res)=>{
    res.send('<h1>404 Not Found</h1>')
})

app.listen(3000,()=>{
    console.log('服务器启动成功')
})
