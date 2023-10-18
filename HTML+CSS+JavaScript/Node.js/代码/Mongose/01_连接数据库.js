const mongoose = require('mongoose')

// 连接mongodb服务
mongoose.connect('mongodb://127.0.0.1:27017/ChichengL')
//最后的users,是要操作的数据库名称

// 设置回调
mongoose.connection.on('open', ()=> {
    console.log('数据库连接成功')
})//连接成功的回调

mongoose.connection.on('error',()=>{
    console.log('数据库连接失败')
})//连接失败的回调

mongoose.connection.on('close',()=>{
    console.log('数据库连接关闭')
})//连接关闭的回调
//关闭连接数据库
setTimeout(()=>{
    mongoose.disconnect()
},2000)