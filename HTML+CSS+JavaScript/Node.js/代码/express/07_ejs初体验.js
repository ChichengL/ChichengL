const ejs = require('ejs')

let china = '中国'
let str = '我爱'

console.log(ejs.render(str+china))
console.log(ejs.render('我爱 <%= china %>',{china:china}))