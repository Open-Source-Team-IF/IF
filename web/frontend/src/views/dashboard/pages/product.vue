<template>
  <v-container fluid>
    <v-row justify="center">
      <v-col cols="12" md="5">
        <base-material-card>
          <template #heading>
            <p class="text-h3 font-weight-light" align="center">물품 등록</p>
          </template>
          <v-form>
            <v-container class="py-0">
              <v-row>
                <v-col cols="12">
                  <v-text-field label="물품" v-model="product"/>
                </v-col>

                <v-col cols="12" md="7">
                  <v-text-field label="가격(원)" v-model="price"/>
                </v-col>

                <v-col cols="12" md="5">
                  <v-text-field label="수량" v-model="quantity"/>
                </v-col>

                <v-col cols="12" md="7">
                  <v-select :items="option" label="진열대" v-model = "stand"/>
                </v-col>
                <v-col cols="12" md="5" class="text-right">
                  <br>
                  <v-btn color="success" v-on:click="register">
                    등록
                  </v-btn>
                </v-col>
              </v-row>
            </v-container>
          </v-form>
        </base-material-card>
      </v-col>

      <v-col cols="12" md="1"/>

      <v-col cols="12" md="5">
      <base-material-card color="warning">
          <template #heading>
            <p align="center" class="text-h3 font-weight-light">물품 삭제</p>
          </template>
          <v-form>
            <v-container class="py-0">
              <v-row>
                <v-col cols="12">
                  <v-text-field label="물품" v-model="target1"/>
                </v-col>
                <v-col cols="12">
                  <v-select :items="option" label="진열대" v-model = "target2"/>
                </v-col>

                <v-col cols="12" md="5"/>

                <v-col cols="12" md="1">
                  <br>
                  <v-btn color="warning" v-on:click="remove">
                    삭제
                  </v-btn>
                </v-col>
              </v-row>
            </v-container>
          </v-form>
        </base-material-card>
      </v-col>
    </v-row>
  </v-container>
</template>

<script>
import axios from "axios";
  export default {
    data() {
      return {
        product: '',
        stand: '',
        price: '',
        target1: '',
        target2:'',
        list: {},
        option: ['진열대1','진열대2','진열대3']
      }
    },
    methods: {
      // 물품 등록 함수
      async register() {
        this.result=''
        var query = []
        var tmp = this.quantity

        // 중복되는 데이터의 처리를 위한 코드
        // 입력한 데이터와 같은 진열대에 같은 물품이 존재하면,
        // 기존의 데이터를 삭제하고 입력한 수량에 기존의 수량을 더해줌.
        await axios.get("/api/mobius/list").then((response) => {
          this.list = response.data
        });
        for(var i = 0; i < this.list.length; i++){
          var data = JSON.parse(this.list[i].con)
          if(data.product==this.product && data.stand==this.stand) {
            await axios.post("/api/mobius/delete", {
              product: this.product,
              stand: this.stand
            })
            this.quantity = String(parseInt(this.quantity) + parseInt(data.quantity))
            break
          }
        }

        // JSON 형식으로 서버에 데이터 전송
        const headers = {
          "X-M2M-RI": "12345",
          "X-M2M-Origin": "S",
          "Content-Type": "application/vnd.onem2m-res+json;ty=4"
        };
        const url = "http://146.56.166.36:7579/Mobius/web/product";

        query = {product: this.product, price:this.price, quantity:this.quantity, stand:this.stand}
        const body = {
        "m2m:cin": {
            "con": query
          }};
        axios.post(url, body, { headers });
        alert(this.stand + "에 " + this.product + " " + tmp + "개를 적재했습니다.")
        },

      // 물품 삭제 함수
      async remove() {
        this.result=''
        axios.post("/api/mobius/delete", {
          product: this.target1,
          stand: this.target2
        });
        alert(this.target2+ "의 " + this.target1 + "를 삭제하였습니다.")
      }
    }
  }
</script>

<style scoped>
p{
  margin:0;
  padding:0;
}
</style>