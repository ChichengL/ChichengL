const bodyParser = require('body-parser')
const express = require('express')

const app = express()

// 解析json格式的请求体中间件
const jsonParser = bodyParser.json()

// 解析queryString格式的请求体中间件
const urlencodedParser = bodyParser.urlencoded({extended:false})

app.get('/login',(req,res)=>{
    res.sendFile(__dirname + '/05_index.html')
})
 
app.post('/login',urlencodedParser,(req,res)=>{
    res.send('获取用户的数据')
    //添加了这个urlencodedParser,之后会往请求体上添加一个body属性
    console.log(req.body.name)
})

app.listen(3000,()=>{
    console.log('3000服务器启动成功')
})