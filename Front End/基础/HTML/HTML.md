> 总体分为
>
> <html>
>
> <head>
>     <title>这个是网页名字</title>
> </head>
>
> ​	<body>
>
> ​	</body>
>
> </html>



> <h4>标签</h4> 
>
> 分为  单标签和双标签
>
> 单标签例如  <br> 是一个 前行换行符
>
> 双标签最常见  比如 <div></div>  <span></span>  <a hrf="#"></a>…….
>
> > <h1>11</h1>  <h6>66</h6>这是标题标签  从1-6  依次减小
>
> 段落标签<p>ww</p>  自动成一段
>
> 注释 标签
>
> ```html
> <!--   注释内容-->
> ```
>
> <h4>链接标签</h4>  <a hrf="#">www</a>  这个就是让在a标签中间的文字附带上超链接  跳转到hrf指向的位置
>
> ```html
> <a hrf=“www.baidu.com” target=“_blank”>百度</a>
> target 是 生成目标页面的类型  比如新生成_blank  或者_self  在当前窗口打开页面(也就是会覆盖)
> <h4>空链接：</h4>
> 	<a id="1"></a>
> 	<a hrf="#2">返回底部</a>
>     <a href="#">空</a>
>     <h4>下载链接</h4>
>     <a href="img.7z">下载图片</a>
>     <h4>网页元素链接</h4>
>     <a href="http://www.baidu.com"><img src="img.jpg"/></a>
>     <a href="#1">comebaby</a>
>     <h4 id="2">已到最底部</h4>
> 
> ```
>
> 这里  id=“x”是定位标签也就是要到的位置    然后  hrf=“#x”  是让点击这个跳转到 id为 x的地方
>
> 
>
> <strong>加粗</strong>  <b>也是加粗</b>    <em>倾斜</em>  <i>也是倾斜</i>  <del>删除线</del> <s>也是删除线</s>   <ins>下划线</ins>  <u>也是下划线</u> 
>
> 图像标签   <img src=""/>  “”里面是路径 可以是绝对路径也可以是相对路径
>
> <img src="" alt=""  title=""  width=""  height=""  border=""/>
>
> src 是图像位置  alt  是图像显示不出来的时候用的“”里面的文字代替  title 是鼠标放在图片上出现的提示文字
>
> width 给图像设置宽度   height 给图像设置高度  border  给图像设置边框
>
> <h4>表格标签 </h4> 
>
> <table>
>     <tr><td>1</td> <td>2</td> <td>3</td></tr>
>     <tr><td>4</td> <td>5</td> <td>6</td></tr>
>     <tr><td>7</td> <td>8</td> <td>9</td></tr>
> </table>   这就是制作表格
>
> <tr></tr>  控制行   <td></td>  控制列
>
> **table align="center" border="2" cellpadding="20" cellspacing="0" width="300" heigt="100"**
>
> th可以让文字加粗并且居中<br>
>
>  align 让表格居左中右<br>
>
>  border 设置表格的边界<br>
>
>  cellpadding设置单元边缘与内容之间的空白(即文字)的距离<br>
>
>  cellspacing单元格之间的空白<br>
>
> 
>
> <h4>列表</h4>
>
> **无序列表ul**
>
> **ul  li**
>
> <ul>
>     <li>1</li>
>     <li>2</li>
> </ul>
>
> **有序列表ol**
>
> **ol  li**
>
> <ol>
>     <li>1</li>
>     <li>2</li>
> </ol>
>
> <h4>表单域</h4>
>
> ```html
> <form action="" method="" name="">
>     action是提交对象，method是提交方式，name是指由哪个表单提交的信息
>     input  用于收集用户信息
>     <label for="1">1</label><input type="属性值" id="1">
>     <input type="" name="" value="" maxlength="" id="">
>     type 后面跟的类型  text定义供文本输入的单行输入字段： password  定义密码字段会有密文显示  submit提交按钮  radio 单选框  checkbox多选框  button 提示框  reset重置所有按钮
>     name 属性规定 input 元素的名称。
> name 属性用于对提交到服务器后的表单数据进行标识，或者在客户端通过 JavaScript 引用表单数据。只有设置了 name 属性的表单元素才能在提交表单时传递它们的值。
>     value  提交类型 里面内容的默认值 
>     maxlength  限制的最大长度  
>     id="#"  让前面的label for="#"定位到这个
>     submit后用value属性可以改变提交框内的默认文字
>     单选按钮一定要有个name  否则无法实现单选！！！！
>     此外单选框和复选框可以有个checked  也就是打开这个页面的时候就会默认勾选出来的
>     
>     button  按钮按了之后会出现页面提示
>     
>    	select 下拉表单元素
>     <select>
>         <option selected>请选择</option>
>         <option>1</option>
>         <option>2</option>
>     </select>
>     
>     <textarea row="5" col="20"></textarea>
> ```
>
> <select>
>     <option selected>请选择</option>
>     <option>1</option>
>     <option>2</option>
> </select>
>
> <textarea row="5" col="20" ></textarea>
>
> 

