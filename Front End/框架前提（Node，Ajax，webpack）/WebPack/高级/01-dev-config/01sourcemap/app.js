class A{
    constructor(){
        this.a = 1;
    }
    sayHello(){
        console.log(this.a)
    }
}

const a = new A()
a.sayHello()