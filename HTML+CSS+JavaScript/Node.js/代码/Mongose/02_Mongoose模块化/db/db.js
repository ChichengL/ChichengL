module.exports = function(success,error){
    const mongoose = require('mongoose')

    // 连接mongodb服务
    mongoose.connect('mongodb://127.0.0.1:27017/ChichengL')
    //最后的users,是要操作的数据库名称
    mongoose.connection.once('open', ()=> {
        success()
    })//连接成功的回调
    // 设置回调
    mongoose.connection.on('error',()=>{
        error()
    })//连接失败的回调

    mongoose.connection.on('close',()=>{
        console.log('数据库连接关闭')
    })//连接关闭的回调
    //关闭连接数据库

}