<template>
  <div class="notice" style ="line-height:1%">
  <h2> Sold Out </h2>
  <el-divider></el-divider>
    <div v-for="(data, index) in soldout" :key="index" class="user-wrap1">
      <li>{{ data.con }}</li>
      <el-divider></el-divider>
    </div>
  <h2> Error </h2>
  <el-divider></el-divider>
    <div v-for="(data, index) in error" :key="index" class="user-wrap2">
      <li> {{ data.con }}</li>
      <el-divider></el-divider>
    </div>
  </div>
</template>

<script>
export default {
  data() {
    return {
      soldout: [],
      error: [],
    }
  },
  methods: {
    retrieve: function () {
      this.$http.get("/api/mobius/soldout").then((response) => {
      this.soldout = response.data;
      });
    this.$http.get("/api/mobius/error").then((response) => {
      this.error = response.data;
      });
    },
    },
    mounted() {
      setInterval(this.retrieve,1000);
    }
  };
</script>