/**
 * 新建一个文件，写入内容，你好
 */

const fs = require('fs');

fs.writeFile('./座右铭.txt','三人行,必有我师焉',err=>{
    //如果失败err就是错误对象,写入成功null
    if(err){
        console.log('写入失败');
        return;
    }
    console.log('写入成功');
})