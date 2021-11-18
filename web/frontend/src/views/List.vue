<template>
  <div class="notice" style ="line-height:1%">
  <h2> 물품 목록 </h2>
  <el-divider></el-divider>
    <div v-for="(data, index) in list" :key="index" class="user-wrap1">
      <li>{{ JSON.parse(data.con).product }} {{ JSON.parse(data.con).price }} {{ JSON.parse(data.con).quantity }} {{ JSON.parse(data.con).shelf }}</li>
      <el-divider></el-divider>
    </div>
  </div>
</template>

<script>
import axios from "axios";
export default {
  data() {
    return {
      list: []
    }
  },
  methods: {
    retrieve () {
      axios.get("/api/mobius/list").then((response) => {
          this.list = response.data
      });
    },
    },
    mounted() {
      setInterval(this.retrieve,1000);
    }
  };
</script>