import { createApp } from 'vue'
import './tailwind.css'
import App from './App.vue'
import { createRouter, createWebHistory } from 'vue-router/auto'
import { createHead } from '@vueuse/head'
import * as echarts from 'echarts'
import mitt from 'mitt'

const emitter = mitt()
const app = createApp(App)
const head = createHead()

const router = createRouter({
  history: createWebHistory(),
})

emitter.on('foo', e => {
  console.log('foo', e) 
  console.log('foo0000000000000000') 
})
app.config.globalProperties.$emitter = emitter

app.config.globalProperties.$echarts = echarts
app.use(router)
app.use(head)
app.mount(document.body)
