<template>
  <div>
    <h1>点击计数器</h1>
    <p>当前计数：{{ count }}</p>
    <button @click="increment">点击增加</button>
  </div>
</template>

<script>
export default {
  data() {
    return {
      count: 0
    };
  },
  methods: {
    increment() {
      this.count++;
    }
  }
};
</script>

<style>
h1 {
  color: blue;
}
p {
  font-size: 20px;
}
button {
  padding: 10px 20px;
  font-size: 16px;
}
</style>
