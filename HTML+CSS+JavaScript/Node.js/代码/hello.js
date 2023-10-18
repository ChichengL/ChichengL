const readline = require("readline")
const r1 = readline.createInterface({
    input: process.stdin,
    output: process.stdout
})
r1.on("line",function(s){
    let t = s.trim().split(' ')
    let a = []
    a[0] = "SWPUNB"
    a[1] = "LECSOFTWARELEAGUE!!!"
    
    for(let i = 2; i <= 80; i ++){
        a[i] = a[i-1]+a[i-2];
    }
    // console.log(a[Number(t[0])][Number(t[1])]);
    // console.log(a);
})
r1.on("close",function(){
    process.exit()
})