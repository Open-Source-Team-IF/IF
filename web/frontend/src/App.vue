<template>
  <div id="app">
    <el-row> 
      <el-col :span="24"><div class="grid-content bg-purple-dark"></div></el-col>
      <Header />
    </el-row>
    <router-view class="el-main" />
  </div>
</template>

<script>
import Header from "./views/Header";

export default {
  name: "App",
  components: {
    Header
  },
};
</script>