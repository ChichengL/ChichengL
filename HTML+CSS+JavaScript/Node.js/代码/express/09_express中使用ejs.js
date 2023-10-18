const express = require('express')
const path = require('path')
const app = express()

app.set('view engine', 'ejs')//设置模版引擎
//设置模版文件存放位置  模版文件:具有模版语法内容的文件
app.set('views',path.resolve(__dirname,'./views'))

app.get('/home',(req,res)=>{
    // res.render('模版的文件名','数据')
    let str = 'Hello World'
    res.render('home',{str})
})

app.listen(3000,()=>{

})