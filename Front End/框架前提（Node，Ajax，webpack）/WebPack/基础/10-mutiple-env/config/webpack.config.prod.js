const CssMinimizerPlugin = require('css-minimizer-webpack-plugin')
const TerserPlugin = require('terser-webpack-plugin')

module.exports = {
    output:{
        filename:'scripts/[name].[contenthash].js',//输出文件的文件名
        publicPath:'https://localhost:8080/'
    },

    mode:'production',
    optimization:{
        minimizer:[
            new CssMinimizerPlugin(),
            new TerserPlugin(),
        ],
    },
    performance:{
        hints:false
    }
}