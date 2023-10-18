const fs = require('fs')

fs.appendFile('./座右铭.txt', '\nhello world',err=>{
    if(err){
        console.log(err)
        return; 
    }
})
fs.writeFile('./座右铭.txt', '\rWTF!!',{flag:'a'},err=>{
    if(err){
        console.log(err)
        return;
    }
})