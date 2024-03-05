function getString(){
    return new Promise((resolve,reject)=>{
        setTimeout(()=>{
            resolve("Hello World");
        },2000);
    })
}


async function hello(){
    let string =await getString()
    console.log(string);
}

export default hello;