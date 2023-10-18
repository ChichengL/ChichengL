
Function.prototype.mycall = function (obj,...arguments) {
    obj.fn = this;
    obj.fn(...arguments);
    delete obj.fn;
    return this;
}
let obj = { name: '123' }
function test() {
    console.log(this.name);
}
test.mycall(obj)