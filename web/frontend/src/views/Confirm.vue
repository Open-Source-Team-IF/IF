 <template>
  <v-flex>
    <v-layout row>
      <v-flex xs2>
     </v-flex>
     고객정보&nbsp; &nbsp; &nbsp;
     <div class="select">
      <el-input
      size="small"
      placeholder="Please Input"
      prefix-icon="el-icon-search"
      v-model="id">
      </el-input>
      </div>
     <v-flex xs2>
     </v-flex>
     <el-button class="but" v-on:click="retrieve">조회</el-button>
     <div class="table">
       <table border="1" style="border-collapse:collapse;" class="inform">
         <tr><th>{{tmp1}}</th><th>{{tmp2}}</th><th>{{tmp3}}</th></tr>
        <tr v-for="n in current.length/3" v-bind:key="n">
            <td width="130px">{{list1[n-1]}} </td>
            <td width="70px">{{list3[n-1]}}\ </td>
            <td width="50px">{{list2[n-1]}} </td>
        </tr>
    </table>
    {{total}}
     </div>
    </v-layout>
  </v-flex>
</template>

<script>
import axios from "axios";
export default {
  data() {
    return {
      response:'',
      list1:[],
      list2:[],
      list3:[],
      id: '',
      response1:'',
      current:'',
      tmp1:'',
      tmp2:'',
      tmp3:'',
      total:''
    }
  },
  methods: {
    retrieve() {
      this.total = 0;
      const headers = {
        "X-M2M-RI": "12345",
        "X-M2M-Origin": "S",
        "Accept": "application/json"
      };

      const url = "http://146.56.166.36:7579/Mobius/app1/user1/product/la";
        axios.get(url, { headers }).then((response1) => {
          var arr = JSON.stringify(response1.data)
          arr = JSON.parse(arr.slice(11,arr.length-1))
          arr = Object.values(JSON.parse(JSON.stringify(arr.con)))
          this.current = arr;
          for (var i = 0; i < arr.length; i += 3) {
            this.list1.push(arr[i]);
            this.list2.push(arr[i+1]);
            this.list3.push(arr[i+2]);
            this.total += arr[i+1] * arr[i+2];
          }
        });
        this.tmp1='물품'
        this.tmp2='가격'
        this.tmp3='개수'
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
  height: 33px;
  right:-80px;
}
.table {
  position:relative;
  left:-300px;
  top: 100px;
}
.inform{
  position: relative;
  left:-50px;
  text-align: center;
}
</style>
