import Publisher from "./publisher.js"

class Viewer{
    constructor(mue,dataKey,updateHandler){
        this.mue = mue;//实例
        this.dataKey = dataKey;//数据
        this.updateHandler = updateHandler;//更新视图的方法
        Publisher.target = this//反向通知
        this.oldValue = mue.data[dataKey]//检测到需要替换模板的东西后，就进行取值
        Publisher.target = null
    }
    update(){
        const newValue = this.mue.data[this.dataKey]
        if(this.oldValue === newValue){
            return;
        }
        this.updateHandler(newValue)
    }

}

export default Viewer