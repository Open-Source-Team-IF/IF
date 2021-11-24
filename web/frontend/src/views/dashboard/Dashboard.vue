<template>
  <v-container fluid>
    <v-row>
      <v-col
        cols="12"
        md="6"
      >
        <base-material-card class="px-5 py-3">
          <template #heading>
            <div class="text-h3 font-weight-light">
              재고 상황
            </div>
          </template>
          <v-card-text>
            <v-data-table
              :headers="headers"
              :items="items"
            />
          </v-card-text>
        </base-material-card>
      </v-col>
      <v-col
        cols="12"
        md="6"
      >
        <base-material-card
          color="warning"
          class="px-5 py-3"
        >
          <template #heading>
            <v-tabs
              v-model="tabs"
              background-color="transparent"
              slider-color="white"
            >
              <span
                class="subheading font-weight-light mx-3"
                style="align-self: center"
              >Tasks:</span>
              <v-tab class="mr-3">
                <v-icon class="mr-1">
                </v-icon>
                오류
              </v-tab>
              <v-tab class="mr-1">
                재고
              </v-tab>
            </v-tabs>
          </template>

          <v-tabs-items
            v-model="tabs"
            class="transparent"
          >
            <v-tab-item
              v-for="n in 2"
              :key="n"
            >
              <v-card-text>
                <template v-for="(task, i) in tasks[tabs]">
                  <v-row
                    :key="i"
                    align="center"
                  >
                    <v-col cols="9">
                      <div
                        class="font-weight-light"
                        v-text="task"
                      />
                    </v-col>
                  </v-row>
                </template>
              </v-card-text>
            </v-tab-item>
          </v-tabs-items>
        </base-material-card>
      </v-col>

      <v-col
        cols="12"
        lg="4"
      >
        <base-material-chart-card
          :data="dailySalesChart.data"
          :options="dailySalesChart.options"
          color="success"
          hover-reveal
          type="Line"
        >
          <h4 class="card-title font-weight-light mt-2 ml-2">
            일별 매출
          </h4>

          <p class="d-inline-flex font-weight-light ml-2 mt-1">
            <v-icon
              color="green"
              small
            >
              mdi-arrow-up
            </v-icon>
            <span class="green--text">55%</span>&nbsp;
          </p>
        </base-material-chart-card>
      </v-col>

      <v-col
        cols="12"
        sm="6"
        lg="3"
      >
        <base-material-stats-card
          color="success"
          icon="mdi-store"
          title="매출"
          value="134,000원"
          sub-icon="mdi-calendar"
          sub-text="Last 24 Hours"
        />
      </v-col>
    </v-row>
  </v-container>
</template>

<script>
  import axios from 'axios'
  export default {
    name: 'DashboardDashboard',

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
            sortable: false,
            text: '물품',
            value: 'product',
          },
          {
            sortable: false,
            text: '가격',
            value: 'price',
            align: 'right',
          },
          {
            sortable: false,
            text: '수량',
            value: 'quantity',
            align: 'right',
          },
          {
            sortable: false,
            text: 'Location',
            value: 'stand',
            align: 'right',
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
        error:[]
      }
    },

    mounted() {
      this.retrieve()
      setInterval(this.retrieve,10000);
    },
    methods: {
      async retrieve () {
        this.items = [];
        this.tasks[0] = []
        this.tasks[1] = []
        await axios.get('/api/mobius/list').then((response) => {
          this.list = response.data
        });
        for(var i = 0; i < this.list.length; i++){
          this.items.push(JSON.parse(this.list[i].con))
        }

        await axios.get("/api/mobius/error").then((response) => {
          this.error = response.data;
        });
        for(var j = 0; j < this.error.length; j++){
          this.tasks[0].push(this.error[j].con)
        }
        await axios.get("/api/mobius/soldout").then((response) => {
          this.soldout = response.data;
        });
        for(var k = 0; k < this.soldout.length; k++){
          this.tasks[1].push(this.soldout[k].con)
        }
      },
    },
  }
</script>
