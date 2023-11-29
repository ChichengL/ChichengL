const path = require('path') 
const HtmlWebpackPlugin = require('html-webpack-plugin')
module.exports = {
    entry:'./src/index.js',
    output:{
        filename:'main.js',//输出文件的文件名
        path:path.resolve(__dirname,'./dist'),//绝对路径
        clean:true,//清除之前的内容
        assetModuleFilename:'images/[contenthash][ext]'
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
    },

    module:{
        rules:[
            {
                test:/\.png$/,  //正则表达式
                type:'asset/resource',
                generator:{
                    filename:'images/[name].[contenthash][ext]'
                }
            },
            {
                test:/\.svg$/,
                type:'asset/inline'
            },
            {
                test:/\.txt$/,
                type:'asset/source'
            },
            {
                test:/\.jpg$/,
                type:'asset',
                parser:{//解释器设置打包大小超过多少就打包为一个资源，否则就是inline类型的
                    dataUrlCondition:{
                        maxSize:10*1024
                    }
                }
            }
        ]
    }
}