const express = require('express')
//创建路由对象
const router = express.Router()

// 创建路由规则

router.get('/home',(req,res)=>{
    res.send('前台首页')
})

router.get('/search',(req,res)=>{
    res.send('搜索首页')
})

module.exports = router