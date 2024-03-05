const path = require('path') 
const HtmlWebpackPlugin = require('html-webpack-plugin')
const MiniCssExtractPlugin = require('mini-css-extract-plugin')
const toml = require('toml')
const yaml = require('yaml')
const json5 = require('json5')

module.exports = {
    output:{
        filename:'scripts/[name].js',//输出文件的文件名
    },

    mode:'development',

    devtool:'inline-source-map',

    devServer:{
        static:'./dist',//指向的路径，作为server的根目录
    },
}