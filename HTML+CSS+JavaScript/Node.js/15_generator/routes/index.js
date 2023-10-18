var express = require('express');
var router = express.Router();
const {formidable} = require('formidable');
/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

// 显示网页的
router.get('/portrait', function(req,res){
    res.render('portrait');
})
// 处理文件上传
router.post('/portrait', function(req,res){
    // 创建表单对象
    const form = formidable({
        multiples:true,
        // 设置上传文件的保存目录
        uploadDir:__dirname + '/../public/images',
        // 保持文件后缀
        keepExtensions:true
    });
    // 解析请求报文
    // fields是一般字段（文件之外的,例如text,radio,checkbox,select），files是文件
    form.parse(req,(err,fields,files)=>{
        if(err){
            next(err);
            return;
        }
        // 服务器需要 
        res.json({fields,files});
    });
});


module.exports = router;
