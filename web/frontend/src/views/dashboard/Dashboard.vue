<template>
  <v-container fluid>
    <v-row>
      <v-col cols="12" md="6">
        <base-material-card class="px-5 py-3" id="itemtable">
          <template #heading>
              <p class="text-h3 font-weight-light" align="center">물품별 재고 현황</p>
          </template>
          <v-card-text>
            <v-data-table
              :headers="headers"
              :items="items"
            />
          </v-card-text>
        </base-material-card>
      </v-col>
      <v-col cols="12" md="6">
        <base-material-card color="warning" class="px-5 py-3" id="errtable">
          <template #heading>
            <v-tabs
              v-model="tabs"
              background-color="transparent"
              slider-color="white"
            >
              <span
                class="subheading font-weight-light mx-3"
                style="align-self: center"
              >&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;</span>
              <v-tab class="mr-4">
                오류목록
              </v-tab>
              <v-tab>
                재고소진
              </v-tab>
            </v-tabs>
          </template>
          <v-tabs-items v-model="tabs">
            <v-tab-item v-for="n in 2" :key="n">
              <v-card-text>
                <template v-for="(task, i) in tasks[tabs]">
                  <v-row :key="i" align="center">
                    <div v-text="task"/>
                    <v-col class="text-right">
                    <v-icon small @click="delerr(task)">
                    mdi-delete
                    </v-icon>
                    </v-col>
                  </v-row>
                  <br :key="i">
                  <v-divider :key="i"></v-divider>
                  <br :key="i">
                </template>
              </v-card-text>
            </v-tab-item>
          </v-tabs-items>
        </base-material-card>
      </v-col>

      <v-col cols="12" md="6">
        <base-material-chart-card
          :data="dailySalesChart.data"
          :options="dailySalesChart.options"
          color="success"
          type="Line"
          style="height:292px"
        >
        <br>
        <h4 class="card-title font-weight-light mt-2 ml-2">
          매출동향
        </h4>
        <p class="d-inline-flex font-weight-light ml-2 mt-1">
          <v-icon color="green" small>
            mdi-arrow-up
          </v-icon>
          <span class="green--text">55%</span>&nbsp;
        </p>
        <template #actions>
          <span class="text-caption grey--text font-weight-light"></span>
        </template>
        </base-material-chart-card>
      </v-col>

      <v-col cols="12" md="4">
        <base-material-stats-card
          color="success"
          icon="mdi-store"
          title="일매출"
          v-bind:value="`${dailysales}원`"
        />
        <br>
        <base-material-stats-card
          color="success"
          icon="mdi-store"
          title="월매출"
          v-bind:value="`${monthlysales}원`"
        />
      </v-col>

      <v-col cols="12" md="2">
        <base-material-card class="px-5 py-1">
          <template #heading>
            <p align="center">카트현황</p>
          </template>
          <v-sheet class="py-2" v-for="(n,index) in onoff" :key="index">
            <v-switch
              v-model="onoff[index]"
              dense
              inset
              readonly
              :color="`${onoffstyle[index]}`"
            >
            <template v-slot:label>
              <span style="color:black">카트{{Number(index)+1}}</span>
            </template>
            </v-switch>
          </v-sheet>
        </base-material-card>
      </v-col>
    </v-row>
  </v-container>
</template>

<script>
import axios from 'axios'
  export default {
    data () {
      return {
        dailySalesChart: {
          data: {
            labels: ['월', '화', '수', '목', '금', '토', '일'],
            series: [
              [12, 17, 7, 17, 23, 18, 38],
            ],
          },
          options: {
            lineSmooth: this.$chartist.Interpolation.cardinal({
              tension: 0,
            }),
            low: 0,
            high: 50,
            chartPadding: {
              top: 0,
              right: 0,
              bottom: 0,
              left: 0,
            },
          },
        },
        headers: [
          {
            text: '물품',
            value: 'product',
          },
          {
            text: '가격',
            value: 'price',
          },
          {
            text: '수량',
            value: 'quantity',
          },
          {
            text: '위치',
            value: 'stand',
          },
        ],
        items: [],
        tabs: 0,
        tasks: {
          0: [
          ],
          1: [
          ],
        },
        list: {},
        soldout:[],
        error:[],
        dailysales:'',
        monthlysales:'',
        onoff:{0:false,1:false,2:false},
        onoffstyle : {0:"green",1:"green",2:"green"}
      }
    },
    // 정보를 가져오는 retrieve 함수를 5초마다 실행
    mounted() {
      this.retrieve()
      setInterval(this.retrieve,5000);
    },
    methods: {
      async retrieve () {
        this.items = []
        this.tasks[0] = []
        this.tasks[1] = []

        // 물품별 재고 현황
        await axios.get('/api/mobius/list').then((response) => {
          this.list = response.data
        })
        for(var i = 0; i < this.list.length; i++){
          this.items.push(JSON.parse(this.list[i].con))
        }

        // 오류 목록 및 재고 소진 현황
        await axios.get("/api/mobius/error").then((response) => {
          this.error = response.data;
        })
        for(var j = 0; j < this.error.length; j++){
          this.tasks[0].push(this.error[j].con)
        }
        await axios.get("/api/mobius/soldout").then((response) => {
          this.soldout = response.data;
        })
        for(var k = 0; k < this.soldout.length; k++){
          this.tasks[1].push(this.soldout[k].con)
        }

        // 위의 두 요소의 크기 맞추기
        var itemtable = document.getElementById('itemtable')
        var errtable = document.getElementById('errtable')
        errtable.style.height  = itemtable.offsetHeight+ "px"

        const headers = {
          "X-M2M-RI": "12345",
          "X-M2M-Origin": "S",
          "Accept": "application/json"
        }

        // 일매출 데이터
        const url1 = "http://146.56.166.36:7579/Mobius/server/dailysales/la"
        await axios.get(url1, { headers }).then((response) => {
          var arr = JSON.stringify(response.data)
          arr = JSON.parse(arr.slice(11,arr.length-1))
          this.dailysales = JSON.parse(JSON.stringify(arr.con)).replace(/\B(?<!\.\d*)(?=(\d{3})+(?!\d))/g, ",");
        })
        // 월매출 데이터
        const url2 = "http://146.56.166.36:7579/Mobius/server/monthlysales/la"
        await axios.get(url2, { headers }).then((response) => {
          var arr = JSON.stringify(response.data)
          arr = JSON.parse(arr.slice(11,arr.length-1))
          this.monthlysales = JSON.parse(JSON.stringify(arr.con)).replace(/\B(?<!\.\d*)(?=(\d{3})+(?!\d))/g, ",");
        })

        // 카트 현황
        for(var idx = 1; idx < Object.keys(this.onoff).length + 1; idx++) {
          const url = "http://146.56.166.36:7579/Mobius/cart"+idx+"/status/la"
          await axios.get(url, { headers }).then((response) => {
            var arr = JSON.stringify(response.data)
            arr = JSON.parse(arr.slice(11,arr.length-1))
            arr = JSON.parse(JSON.stringify(arr.con))
            if(arr !="waiting") {
              this.onoff[idx-1] = true
            }
            else {
              this.onoff[idx-1] = false
            }
          })
          this.onoffstyle[idx-1] = "green"
        }
        // 카트에서 오류 발생 시, 빨간색으로 표시
        for (var j = 0; j < this.tasks[0].length; j++){
          var chk = this.tasks[0][j]
          if(chk.substring(0,2)=="카트") {
            this.onoffstyle[Number(chk.substring(2,3))-1] = "red"
          }
        }
      },

      // 오류 목록 및 재고 부족 현황 삭제 기능
      async delerr (task) {
        await axios.post("/api/mobius/delerr", {
          task: task
        });
          alert('삭제완료')
          this.retrieve();
        },
      }
  }
</script>

<style scoped>
p{
  margin:0;
  padding:0;
}
</style>