console.log( localStorage.getItem('Array')===null)
console.log(localStorage.getItem('Array'))
let arr =localStorage.getItem('Array')!==null?JSON.parse(localStorage.getItem('Array')):[]
if(arr===null) arr=[]
//访问数据的id
let ID = localStorage.getItem('ID')

const getData = ()=>{
  const htmlStr = arr.map((item) =>{
    return `<li data-id=${item.id}>姓名为：${item.name}--------学号是：${item.id} <button class="btn_right del">删除</button><button class="btn_right details">查看详细</button></li>`
  }).join('')
  document.querySelector('.list').innerHTML = htmlStr
}

getData()


//新增对象
const addModalDOM = document.querySelector('.add-modal')
const addMoal = new bootstrap.Modal(addModalDOM)

document.querySelector('.add-btn').addEventListener('click',()=>{
  const form = document.querySelector('.add-form')
  const mydata = serialize(form,{hash:true,empty:true})
  let flag = true
  arr.map(item =>{
    if(item.id===mydata.id)
    {
      flag=false
    }
  })
  if(flag)arr.unshift(mydata)
  {
    // console.log(mydata)
    localStorage.setItem('Array',JSON.stringify(arr))
    getData()
    form.reset()
    addMoal.hide()
  }
  if(!flag){
    alert('警告，id已重复输入，请输入正确的id')
  }
})


//删除对象
  document.querySelector('.list').addEventListener('click',e =>{
    // console.log(e)
    if(e.target.classList.contains('del')){
      // console.log(e.target.parentNode.dataset.id)
      const id = e.target.parentNode.dataset.id
      arr = arr.filter((p)=>{
        return p.id!=id
      })
    }
    localStorage.setItem('Array',JSON.stringify(arr))
    getData()
  })

//添加查看
document.querySelector('.list').addEventListener('click',e=>{
  if(e.target.classList.contains('details')){
    ID = e.target.parentNode.dataset.id
    location.href='index2.html'
    localStorage.setItem('ID',ID)
  }
})

