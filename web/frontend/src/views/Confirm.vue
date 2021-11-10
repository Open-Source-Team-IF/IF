<template>
  <v-flex>
    <v-layout row>
      <v-flex xs1>
     </v-flex>
     <p1>고객정보&nbsp; &nbsp;</p1>
     <div class="select">
      <el-input
      size="small"
      placeholder="Please Input"
      prefix-icon="el-icon-search"
      v-model="input">
      </el-input>
      </div>
     <v-flex xs2>
     </v-flex>
     <el-button class="but">조회</el-button>
     
    </v-layout>
  </v-flex>

</template>

<script>
  export default {
    data() {
      return {
        input: '',
        item: '',
        shelf: ''
      }
    }
  }
</script>

<style scoped>
.select {
  height: 70vh;
}
.but {
  position:relative;
  height: 35px;
}
</style>