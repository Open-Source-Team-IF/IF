<template>
  <v-flex>
    <v-layout row>
     <v-flex xs2>
     </v-flex>
      <div class="select">
        카테고리&nbsp;  
        <el-select v-model="Kategorie" placeholder="">
          <el-option
          v-for="item in options"
          :key="item.value"
          :label="item.label"
          :value="item.value">
          </el-option>
        </el-select>
        <br><br><br><br>

        &nbsp; &nbsp;물품 &nbsp; &nbsp;
        <el-select v-model="item" placeholder="">
          <el-option
          v-for="item in options"
          :key="item.value"
          :label="item.label"
          :value="item.value">
          </el-option>
        </el-select>
        <br><br><br><br>
        
        &nbsp;진열대 &nbsp;&nbsp;
        <el-select v-model="shelf" placeholder="">
          <el-option
          v-for="item in options"
          :key="item.value"
          :label="item.label"
          :value="item.value">
          </el-option>
        </el-select>
        <el-button class="but" type="info">등록</el-button>
      </div>
     <v-flex xs2>
     </v-flex>
     <br><br><br>
    456<br>
     {{ Kategorie }}<br>
     {{ item }} <br>
     {{ shelf }}<br>
    </v-layout>
  </v-flex>

</template>

<script>
  export default {
    data() {
      return {
        options: [{
          value: 'Option1',
          label: 'Option1'
        }, {
          value: 'Option2',
          label: 'Option2'
        }, {
          value: 'Option3',
          label: 'Option3'
        }, {
          value: 'Option4',
          label: 'Option4'
        }, {
          value: 'Option5',
          label: 'Option5'
        }],
        Kategorie: '',
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
  left:160px;
  top:120px;
  z-index:4;
}
</style>