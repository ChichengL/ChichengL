let buf_1 = Buffer.from([101, 102, 103, 104, 105])
console.log(buf_1.toString())

let buf_2 = Buffer.from('hello')
// console.log(buf_2[0].toString(2));
buf_2[0] = 361;
console.log(buf_2[0].toString(2));