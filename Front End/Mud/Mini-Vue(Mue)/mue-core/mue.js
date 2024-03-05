import Hijacker from "../mue-core/hijacker.js"
import Complier from "./compiler.js"


class Mue{
    constructor(options){
        this.el = document.querySelector(options.el)
        this.data = typeof options.data === 'function' ? options.data.call() : options.data
        new Hijacker(this,'data')
        new Complier(this)
    }
}

export default Mue