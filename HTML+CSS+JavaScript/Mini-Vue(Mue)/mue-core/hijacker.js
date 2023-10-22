import Publisher from './publisher.js'
class Hijacker{
    constructor(data){
        this.hijack(data)
        //劫持数据
    }
    hijack(object,key){
        const publisher = new Publisher()
        let value = object[key]
        if(!value){
            return;
        }else if(typeof value ==='object'){
            Object.keys(value).forEach(key=>{
                this.hijack(value,key)//递归进行劫持
            })
        }else{
            const that = this
            Object.defineProperty(object,value,{
                get(){
                    if(Publisher.target){
                        publisher.addViewer(Publisher.target)//取值触发get，使得观测者被加入到发布者的列表里
                    }
                    return value
                },
                set(newValue){
                    if(value === newValue){
                        return
                    }
                    value = newValue
                    that.hijack(newValue)//如果更改的属性仍然是树形，那么继续递归进行劫持
                    publisher.publish()
                }
            })
        }
    }
}


export default Hijacker