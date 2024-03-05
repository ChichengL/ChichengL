const path = require('path') 
const HtmlWebpackPlugin = require('html-webpack-plugin')
module.exports = {
    entry:'./src/index.js',
    output:{
        filename:'bundle.js',//输出文件的文件名
        path:path.resolve(__dirname,'./dist'),//绝对路径
        clean:true//清除之前的内容
    },

    mode:'development',

    devtool:'inline-source-map',

    plugins:[
        new HtmlWebpackPlugin({
            template:'./index.html',
            filename:'app.html',
            inject:'body'//打包后的js代码插入位置
        })
    ],

    devServer:{
        static:'./dist',//指向的路径，作为server的根目录
    }
}