//渲染
const creator='老张'
const getBooksList = ()=>{
  axios({
    url:'http://hmajax.itheima.net/api/books',
    params:{
      creator
    }
  }).then(result=>{
    // console.log(result)
    const books=result.data.data
    // console.log(books);
    const htmler = books.map((item,index)=>{
      return `
      <tr>
          <td>${index+1}</td>
          <td>${item.bookname}</td>
          <td>${item.author}</td>
          <td>${item.publisher}</td>
          <td data-id=${item.id}>
            <span class="del">删除</span>
            <span class="edit">编辑</span>
          </td>
        </tr>`
    }).join('')
    document.querySelector('.list').innerHTML = htmler
  })
}
getBooksList()


//新增
//1.创建对象
const addModalDOM = document.querySelector('.add-modal')
const addMoal = new bootstrap.Modal(addModalDOM)

//保存按钮，点击，隐藏
document.querySelector('.add-btn').addEventListener('click',()=>{

  const form = document.querySelector('.add-form')
  const mydata = serialize(form,{hash:true,empty:true})
  axios({
    url:'http://hmajax.itheima.net/api/books',
    method:'post',
    data:{
      ...mydata,//展开数据
      creator
    }
  }).then(result=>{
    getBooksList()
    //重置表单
    form.reset()
    //隐藏弹框
    addMoal.hide()
  })
})

//删除图书
document.querySelector('.list').addEventListener('click',e =>{
  if( e.target.classList.contains('del'))//确定点击的为删除按钮
  {
    const theId=e.target.parentNode.dataset.id
    // console.log(theId)
    axios({
      url:`http://hmajax.itheima.net/api/books/${theId}`,
      method:'DELETE'
    }).then(result=>{
      getBooksList()
    })
  }
})

//编辑图书

const editModalDom = document.querySelector('.edit-modal')
const editModal = new bootstrap.Modal(editModalDom)

document.querySelector('.list').addEventListener('click',e =>{
  if(e.target.classList.contains('edit')){
    //获取数据回显到表单中
    const theId = e.target.parentNode.dataset.id
    axios({
      url:`http://hmajax.itheima.net/api/books/${theId}`
    }).then(result=>{
      const bookObj = result.data.data
      // document.querySelector('.edit-form .bookname').value =bookObj.bookname
      // document.querySelector('.edit-form .author').value =bookObj.author
      // document.querySelector('.edit-form .publisher').value =bookObj.publisher

      const keys = Object.keys(bookObj)
      keys.forEach(key=>{
        document.querySelector(`.edit-form .${key}`).value=bookObj[key]
      })

    })

    editModal.show()
  }
})
//修改表单，点击，保存
document.querySelector('.edit-btn').addEventListener('click',()=>{
  const editForm = document.querySelector('.edit-form')
  const {id,bookname,author,publisher} = serialize(editForm,{hash:true,empty:true})
  axios({
    url:`http://hmajax.itheima.net/api/books/${id}`,
     method:'PUT',
     data:{
      bookname,
      author,
      publisher,
      creator
     }
  }).then(()=>{
    getBooksList()
  editModal.hide()

  })
})