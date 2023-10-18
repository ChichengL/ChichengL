const { log } = require('console');
const fs = require('fs');

const rs = fs.createReadStream('./座右铭.txt');

//chunk 块
rs.on('data',(chunk)=>{
    console.log(chunk.toString());
})

rs.on('end',()=>{
    console.log('读取完毕');
})

rs.on('error',(err)=>{
    console.log(err);
})

rs.on('close',()=>{
    console.log('文件关闭');
})

rs.on('open',()=>{
    console.log('文件打开');
})
