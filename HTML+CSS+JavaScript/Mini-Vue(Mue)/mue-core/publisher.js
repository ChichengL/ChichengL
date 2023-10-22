class Publisher{
    constructor(data){
        this.viewers = new Set()
    }
    addViewer(viewer){
        this.viewers.push(viewer)
    }
    publish(){
        this.viewers.forEach(viewer => viewer.update(this))
    }
}

export default Publisher