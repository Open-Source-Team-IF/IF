import Vue from 'vue'
import Router from 'vue-router'

Vue.use(Router)

export default new Router({
  mode: 'hash',
  base: process.env.BASE_URL,
  routes: [
    {
      path: '/',
      component: () => import('@/views/dashboard/Index'),
      children: [
        {
          name: '현황',
          path: '',
          component: () => import('@/views/dashboard/Dashboard'),
        },
        {
          name: '물품 관리',
          path: 'pages/user',
          component: () => import('@/views/dashboard/pages/product'),
        },
        {
          name: '주문 조회',
          path: 'pages/order',
          component: () => import('@/views/dashboard/pages/order'),
        },
      ],
    },
  ],
})
