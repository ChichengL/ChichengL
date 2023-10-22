
import babel from 'rollup-plugin-babel'
import resolve from '@rollup/plugin-node-resolve'
//rollup默认可以导出一个对象 作为打包的配置文件
export default{
  input:'./src/index.js',//入口
  output:{
    file:'./dist/vue.js',//出口
    format:'umd',//打包模式  常见有esm  es6模块  commonjs模块    iife自执行函数  umd统一模块规范(commonjs && amd)
    name:'Vue',// global.Vue
    sourcemap:true,//希望可以调试代码
  },
  plugins:[
    babel({
      exclude: 'node_modules/**' //排除node_modules所有的文件
    }),
    resolve()
  ],//插件
}