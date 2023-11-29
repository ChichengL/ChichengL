<template>
<!-- 组件的结构   -->
  <div class="demo">
    <h2>学校名称{{ schoolName }}</h2>
    <h2>学校地址{{ address }}</h2>
    <button @click="showName">点我提示学校名</button>
  </div>
</template>

<script>
//
//组件交互相关的代码（数据方法）
//下面这个叫分别暴露
  export const School = Vue.extend({
    name:'School',
    data(){
      return {
        schoolName: '北京尚硅谷',
        address: '北京昌平区'
      }
    },
    methods:{
      showName(){
        alert(this.schoolName)
      }
    }
  })
  //export {school}统一暴露
  // export default {school}默认暴露
</script>

<style>
  /*  组件的样式 */
  .demo{
    background-color: orange;
  }
</style>