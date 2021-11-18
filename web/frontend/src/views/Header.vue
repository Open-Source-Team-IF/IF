<template>
<div>
  <br><br><br>
  <h1>스마트카트 관리자 페이지</h1>
  <el-menu :default-active="activeIndex" class="el-menu-demo" mode="horizontal" @select="handleSelect">
  <el-menu-item activeIndex="1"><router-link to="/main">메인페이지</router-link></el-menu-item>
  <el-menu-item activeIndex="2"><router-link to="/register">물품 등록</router-link></el-menu-item>
  <el-menu-item activeIndex="3"><router-link to="/confirm">주문 조회</router-link></el-menu-item>
  </el-menu>
  <br><br>
</div>
</template>

<script>
  export default {
    data() {
      return {
        activeIndex: '1',
      };
    },
    methods: {
      handleSelect(key, keyPath) {
        console.log(key, keyPath);
      }
    }
  }
</script>

<style>
h1 {
  text-align: center;
}
</style>