// const { error, log } = require('console')
const fs = require('fs')

try {
  const data = fs.readFileSync('./数据.txt', 'utf-8')
// console.log(__dirname)
console.log('data:' , data)
} catch (error) {
  console.log('err:' , error);
}

const data2 = {name:'小夫',age:72}

fs.writeFileSync('数据.txt',JSON.stringify(data2),'utf-8')

try {
  const data = fs.readFileSync('./数据.txt', 'utf-8')
// console.log(__dirname)
console.log('data:' , data)
} catch (error) {
  console.log('err:' , error);
}