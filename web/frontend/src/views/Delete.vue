<template>
    <div>
    <el-input
      size="small"
      placeholder="Please Input"
      v-model="product">
    </el-input>
    <el-button class="but" v-on:click="remove">삭제</el-button>
    {{detail}}
    </div>
</template>

<script >
import axios from "axios";
export default{
  data() {
    return {
      product:'',
      detail:''
    }
  },
  methods: {
    async remove() {
      axios.post("/api/mobius/delete", {
        product: this.product
      });
      alert('Succeed')
      this.detail=this.product+"를 삭제하였습니다."
    }
  }
}
</script>