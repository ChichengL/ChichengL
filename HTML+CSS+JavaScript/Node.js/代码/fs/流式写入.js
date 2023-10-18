const fs = require('fs');

// 创建写入流对象
const ws = fs.createWriteStream('./1.txt');

ws.write('hello');
ws.write(' world');
ws.close();