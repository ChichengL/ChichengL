const ejs = require('ejs')

const xiyou = ['唐僧','孙悟空','猪八戒','沙僧']

const fs = require('fs')

let str = fs.readFileSync('./08_index.html').toString();
console.log(ejs.render(str,{xiyou:xiyou}))