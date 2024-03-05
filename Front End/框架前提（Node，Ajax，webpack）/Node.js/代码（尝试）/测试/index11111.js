/* 引入express框架 */
const express = require('express');
const app = express();
 
/* 引入cors */
const cors = require('cors');
app.use(cors());
 
/* 引入body-parser */
const bodyParser = require('body-parser');
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));
 
/* 引入mysql */
const mysql = require('mysql');
const conn = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    password: '123456',
    database: 'test',
    multipleStatements: true
})
conn.connect();
 
/* 监听端口 */
app.listen(8080, () => {
    console.log('——————————服务已启动——————————');
})
 
app.get('/', (req, res) => {
    res.send('<p style="color:red">服务已启动</p>');
})
 
app.get('/api/getUserList', (req, res) => {
    const sqlStr = 'SELECT * FROM users'
    conn.query(sqlStr, (error, results) => {
        if (error) return res.json({ code: 10001, message: error})
        res.json({ code: 10000, message: results})
    })
})