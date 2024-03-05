const { merge } = require('webpack-merge');

const common = require('./webpack.config.common');
const production = require('./webpack.config.prod')
const development = require('./webpack.config.dev')

module.exports = (env)=>{
    switch (true){
        case env.development:
            return merge(common, development);
        case env.production:
            return merge(common, production);

        default:
            return new Error("No match configuration was found")
    }
}