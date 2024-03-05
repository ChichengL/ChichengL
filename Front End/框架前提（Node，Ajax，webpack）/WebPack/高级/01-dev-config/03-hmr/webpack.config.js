const HtmlWebpackPlugin = require('html-webpack-plugin');

module.exports = {
    mode:'development',

    entry:'./app.js',
    module:{
        rules:[
            {
                test:/\.css$/,
                use:['style-loader','css-loader']
            }
        ]
    },
    plugins:[
        new HtmlWebpackPlugin({
            template:'./index.html'
        })
    ],
    devServer:{
        hot:true,
    }
}