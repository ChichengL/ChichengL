function require(file){
    // 将相对路径转化为绝对路径
    let absolutePath = path.resolve(__dirname,file);
    // 缓存检测
    if(caches[absolutePath]){
        return caches[absolutePath]
    }
    // 读取文件代码 
    let code = fs.readFileSync(absolutePath).toString()
    let module = {}
    let exports = module.exports = {}
    (function (exports, require,module, __filename, __dirname){
        const test = {
            name:'text'
        }
        module.exports = test

        console.log(arguments.callee.toString())
    })(exports,require,module,__filename,__dirname)
    // 缓存结果
    caches[absolutePath] = module.exports
    return module.exports
}