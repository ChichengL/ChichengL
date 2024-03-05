const fs = require('fs');

// fs.readFile('./1.txt',(err,data)=>{
//     if(err){
//         console.log(err);
//         return;
//     }
//     console.log(data.toString());
// })

let data = fs.readFileSync('./1.txt');
console.log(data.toString());