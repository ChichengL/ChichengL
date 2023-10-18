const db = require('./db/db')
const mongoose = require('mongoose')
db(()=>{
    let BookSchema = new mongoose.Schema({
        name: String,
        price: Number,
        author:String
    })
    // 创建模型对象,是对文档操作的封装对象
    let BookModel = mongoose.model('Book', BookSchema)
    BookModel.create({
        name:'啊对对对',
        price:99.99,
        author:'Syhing'
    }).then((err,data)=>{ 
        if(err){
            console.log(err)
            return;
        }
        console.log(data)
    })
},()=>{
    
})

 // 创建文档的结构对象,设置文档属性及其属性值的类型
 
