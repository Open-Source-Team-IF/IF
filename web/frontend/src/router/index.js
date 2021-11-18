import Vue from 'vue'
import Router from 'vue-router'
import Main from '../views/Main'
import Register from '../views/Register'
import Confirm from '../views/Confirm'

Vue.use(Router)

export default new Router({
  routes: [
    {
      path: '/',
      component: Main
    },
    {
      path: '/main',
      name: 'Main',
      component: Main
    },
    {
      path: '/register',
      name: 'Register',
      component: Register
    },
    {
      path: '/confirm',
      name: 'Confirm',
      component: Confirm
    },
  ]
})