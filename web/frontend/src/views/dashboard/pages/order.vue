<template>
  <v-container fluid>
  <v-row justify="center">
    <v-col
      cols="12"
      md="10"
    >
    <base-material-card
      icon="mdi-clipboard-text"
      title="주문 조회"
      class="px-5 py-3"
    >
    <v-form>
      <v-container class="py-0">
        <v-row>
          <v-col
            cols="12"
            md="6"
          >
         <v-text-field
           label="사용자"
           v-model="user"
          />
          </v-col>

          <v-col
            cols="12"
            md="3"
          >
          <v-btn
            class="btn"
            color="success"
            v-on:click="retrieve"
          >
          조회
          </v-btn>
          </v-col>
          <p style="font-size:20px"><br>{{result}}</p>

          <v-col
            cols="12"
            md="12"
          >
          <v-simple-table>
            <thead>
              <tr >
                <th class="primary--text">
                  물품
                </th>
                <th class="primary--text">
                  가격(원)
                </th>
                <th class="primary--text">
                  수량
                </th>
              </tr>
            </thead>

            <tbody>
              <tr v-for="n in current.length/3" v-bind:key="n">
              <td>{{list1[n-1]}} </td>
              <td>{{list3[n-1]}} </td>
              <td>{{list2[n-1]}} </td>
              </tr>
            </tbody>
          </v-simple-table>
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
      list1:[],
      list2:[],
      list3:[],
      user: '',
      current:'',
      total:'',
      result:''
    }
  },
  methods: {
    retrieve() {
      this.result='';
      this.total = 0;
      const headers = {
        "X-M2M-RI": "12345",
        "X-M2M-Origin": "S",
        "Accept": "application/json"
      };

      const url = "http://146.56.166.36:7579/Mobius/app1/"+this.user+"/product/la";
        axios.get(url, { headers }).then((response) => {
          var arr = JSON.stringify(response.data)
          arr = JSON.parse(arr.slice(11,arr.length-1))
          arr = Object.values(JSON.parse(JSON.stringify(arr.con)))
          this.current = arr;
          for (var i = 0; i < arr.length; i += 3) {
            this.list1.push(arr[i]);
            this.list2.push(arr[i+1]);
            this.list3.push(arr[i+2]);
            this.total += arr[i+1] * arr[i+2];
          }
          this.result = '총액 : ' + this.total + '원'
        });

    },
  },
}
</script>