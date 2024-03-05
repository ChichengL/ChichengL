const path = require('path') 
const HtmlWebpackPlugin = require('html-webpack-plugin')
const MiniCssExtractPlugin = require('mini-css-extract-plugin')
const CssMinimizerPlugin = require('css-minimizer-webpack-plugin')
const TerserPlugin = require('terser-webpack-plugin')
const toml = require('toml')
const yaml = require('yaml')
const json5 = require('json5')

module.exports = {
    entry:{
        index:'./src/index.js',
        another:'./src/another-modules.js',
    },
    output:{
        path:path.resolve(__dirname,'../dist'),//绝对路径
        clean:true,//清除之前的内容
        assetModuleFilename:'images/[contenthash][ext]',
    },
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
        splitChunks:{
            cacheGroups:{
                vendor:{
                    test:/[\\/]node_modules[\\/]/, //因为可能其前面存在一些斜线（路径）
                    name:'vendor',
                    chunks:'all'
                }
            }
        }
    }
}