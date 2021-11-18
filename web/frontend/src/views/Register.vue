<template>
  <v-flex>
    <v-layout row>
     <v-flex xs2>
     </v-flex>
      <div class="select">
         물품<br><br>
        <el-input
         size="small"
         placeholder="Please Input"
         v-model="item">
        </el-input>
       <br><br><br>
        수량 &nbsp; &nbsp; &nbsp;
       <el-input-number v-model="num" :min="1" :max="100"></el-input-number>
       <br><br><br>
       <div>
         가격<br><br>
        <el-input
         size="small"
         placeholder="Please Input"
         v-model="price">
        </el-input>
      </div>
      <br><br><br>
        진열대 &nbsp;&nbsp;
        <el-select v-model="shelf" placeholder="">
         <el-option
          v-for="item in option"
          :key="item"
          :value="item">
         </el-option>
         </el-select>
      </div>
     <v-flex xs2>
     </v-flex>
     <br><br><br>
     <br><br><br>
     <el-button class="but" type="info" v-on:click="reg">등록</el-button>
     {{ tmp1 }} <br>
    </v-layout>
  </v-flex>
</template>

<script>
import axios from "axios";
  export default {
    data() {
      return {
        item: '',
        shelf: '',
        price: '',
        num: 1,
        tmp1: '',
        option: ['shelf1','shelf2', 'shelf3', 'shelf4', 'shelf5'],
      }
    },
    methods: {
      reg() {
        var query = []
        const headers = {
          "X-M2M-RI": "12345",
          "X-M2M-Origin": "S",
          "Content-Type": "application/vnd.onem2m-res+json;ty=4"
          };
        const url = "http://146.56.166.36:7579/Mobius/server/product";
        query = {product: this.item, price:this.price, quantity:this.num,shelf:this.shelf}
        const body = {
        "m2m:cin": {
            "con": query
          }};
        axios.post(url, body, { headers });
        alert('Succeed')
        this.tmp1= "진열대 " + this.shelf + "에 물품 " + this.item + " " + this.num + "개를 적재했습니다."
        },
      },
    }
</script>

<style scoped>
.select {
  height: 70vh;
}
.but {
  position:relative;
  height: 35px;
  left:-100px;
  top:280px;
  z-index:4;
}
</style>