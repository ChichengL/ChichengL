const path = require('path')
const HtmlWebpackPlugin = require('html-webpack-plugin')
module.exports = {
    mode:'development',
    entry:'./app.js',
    output:{
        filename:'bundle.js',
        path:path.resolve(__dirname,'./dist'),
        clean:true
    },
    devServer:{
        static:path.resolve(__dirname,'./dist'),
        compress:true,//配置是否在服务端进行代码压缩
        port:3000,//设置端口号

        headers:{
            'X-Access-Token':"das134wd0as0xcas534edwq00d30wq1dqwd30qw1dqd0as1d6q5"
        },//添加 响应头
        proxy:{//解决跨域问题
            '/api':'http://localhost:9000' //当有请求路径是以api开头的就跳转到后面的值（localhost:9000）上面
        },
        //https:true,//让本地的http服务变成https服务，当然这样可能不安全（因为没有签名证书）


        // http2:true,//让本地服务变为http2，并且自带签名证书
        historyApiFallback:true, //如果是history模式且请求的路径不存在会返回根页面
    
        host:'0.0.0.0' //让局域网的伙伴一起访问
    },
    plugins:[
        new HtmlWebpackPlugin()  
    ]
} 