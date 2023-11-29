<template>
<!-- 组件的结构   -->
  <div>
    <h2>学生姓名{{ studentName }}</h2>
    <h2>学生年龄{{ age }}</h2>
    <button @click="showName">点我提示学校名</button>
  </div>
</template>

<script>
//
//组件交互相关的代码（数据方法）
//下面这个叫分别暴露
  export default {
    name:'Student',
    data(){
      return {
        studentName: '北京尚硅谷',
        age: '北京昌平区'
      }
    }
  }
  //export {school}统一暴露
  // export default {school}默认暴露
</script>


