const path = require('path') 
const HtmlWebpackPlugin = require('html-webpack-plugin')
const MiniCssExtractPlugin = require('mini-css-extract-plugin')
const CssMinimizerPlugin = require('css-minimizer-webpack-plugin')
const toml = require('toml')
const yaml = require('yaml')
const json5 = require('json5')

module.exports = {
    entry:{
        // index:{
        //     import:'./src/index.js',
        //     dependOn:'shared'
        // },
        // another:{
        //     import:'./src/another-modules.js',
        //     dependOn:'shared'
        // },
        // shared:'lodash'
        index:'./src/index.js',
        another:'./src/another-modules.js',
    },
    output:{
        filename:'[name].bundle.js',//输出文件的文件名
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
        }),
        new MiniCssExtractPlugin({
            filename:'styles/[contenthash].css'
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
            },
            {
                test:/\.(css|less)$/,
                use:[MiniCssExtractPlugin.loader,'css-loader','less-loader']
            },
            {
                test:/\.(woff|woff2|eot|ttf|otf)$/,
                type:'asset/resource'
            },
            {
                test:/\.(csv|tsv)$/,
                use:['csv-loader']
            },
            {
                test:/\.xml$/,
                use:['xml-loader']
            },
            {
                test:/\.toml$/,
                type:'json',
                parser:{
                    parse:toml.parse,
                }
            },
            {
                test:/\.yaml$/,
                type:'json',
                parser:{
                    parse:yaml.parse,
                }
            },
            {
                test:/\.json5$/,
                type:'json',
                parser:{
                    parse:json5.parse,
                }
            },
            {
                test:/\.js$/,
                exclude:/node_modules/,//排除node_modules中的js代码
                use:{
                    loader:'babel-loader',//加载loader
                    options:{
                        presets:['@babel/preset-env']//加载预设
                    }
                }
            }
        ]
    },
    optimization:{
        minimizer:[
            new CssMinimizerPlugin(),
        ],
        splitChunks:{
            chunks:'all'
        }
    }
}