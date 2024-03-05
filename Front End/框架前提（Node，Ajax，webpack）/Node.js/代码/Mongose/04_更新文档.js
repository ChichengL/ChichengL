const mongoose = require('mongoose')

// 连接mongodb服务
mongoose.connect('mongodb://127.0.0.1:27017/ChichengL')
//最后的users,是要操作的数据库名称

// 设置回调
mongoose.connection.once('open', ()=> {
    // 创建文档的结构对象,设置文档属性及其属性值的类型
    let BookSchema = new mongoose.Schema({
        name: String,
        price: Number,
        author:String
    })
    // 创建模型对象,是对文档操作的封装对象
    let BookModel = mongoose.model('Book', BookSchema)
    BookModel.updateOne({author:'zhangsan'},{price:88}).then((err,data)=>{
        if(err) {
            console.log(err)
            return;
        }
        console.log(data)
    })
    
})//连接成功的回调

mongoose.connection.on('error',()=>{
    console.log('数据库连接失败')
})//连接失败的回调

mongoose.connection.on('close',()=>{
    console.log('数据库连接关闭')
})//连接关闭的回调
//关闭连接数据库
