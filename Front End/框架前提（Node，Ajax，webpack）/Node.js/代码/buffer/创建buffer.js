let buf = Buffer.alloc(10);

let buf2 = Buffer.allocUnsafe(10, 1);
console.log(buf2);

let buf3 = Buffer.from([1, 2, 3]);

let buf4 = Buffer.from('tést');