<template>
  <div>
  <div class="pt-2 pb-2 bg-gray-50">
    <svg fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="w-6 h-6 ml-4 duration-100 ease-in-out delay-50 hover:scale-150 hover:text-indigo-600" @click="this.WSpannel=!this.WSpannel">
    <path v-if=this.Connected stroke-linecap="round" stroke-linejoin="round" d="M9 12.75L11.25 15 15 9.75M21 12a9 9 0 11-18 0 9 9 0 0118 0z" />
    <path v-else stroke-linecap="round" stroke-linejoin="round" d="M9.75 9.75l4.5 4.5m0-4.5l-4.5 4.5M21 12a9 9 0 11-18 0 9 9 0 0118 0z" />
    </svg>
  </div>

<TransitionRoot appear :show="WSpannel" as="template">
  <TransitionChild as="template" enter="duration-300 ease-out" enter-from="opacity-0 scale-95"
    enter-to="opacity-100 scale-100" leave="duration-200 ease-in" leave-from="opacity-100 scale-100"
    leave-to="opacity-0 scale-95">
    <div class="mb-4 rounded bg-gray-50">

      <!-- 启动路径 -->
      <div class="flex items-center justify-center min-h-full ">
        <div class="w-full max-w-2xl space-y-4">
          <div>
            <input v-model="path_input" required
              class="relative block w-full px-3 py-2 text-gray-900 placeholder-gray-500 border border-gray-300 rounded-md appearance-none focus:z-10 focus:border-indigo-500 focus:outline-none focus:ring-indigo-500 sm:text-sm"
              placeholder="程序路径">
          </div>
          <div>
            <button
              class="relative px-4 py-2 space-x-0 text-sm font-medium text-white bg-indigo-600 border border-transparent rounded-md hover:bg-indigo-700 focus:outline-none focus:ring-2 focus:ring-indigo-500"
              @click="startprocess()">
              启动
            </button>
          </div>
        </div>
      </div>
      
      <!-- 消息列表 -->
      <div class="max-w-screen-xl px-4 py-6 mx-auto sm:px-6 lg:flex lg:items-center lg:justify-between">
          <div style="max-height:30vh" class="overflow-y-scroll resize vertical-align min-w-min scrollbar-thin scrollbar-thumb-indigo-600 scrollbar-thumb-rounded-full scrollbar-track-rounded-full">
            <li v-for="(message) in messages" style="list-style-type: none;" class="p-2 pr-5">
              <Message :title=message.title />
            </li>
          </div>
          <div class="flex mt-8 lg:mt-0 lg:flex-shrink-0">
            <div class="inline-flex ml-3 rounded-md shadow">
              <button @click="initSocket"
                class="inline-flex items-center justify-center px-5 py-3 text-base font-medium leading-6 text-indigo-600 transition duration-150 ease-in-out bg-white border border-transparent rounded-md hover:text-indigo-500 focus:outline-none">
                initWebsocket
              </button>
            </div>
            <div class="inline-flex ml-3 rounded-md shadow">
              <button @click="sendobj({title: 123})"
                class="inline-flex items-center justify-center px-5 py-3 text-base font-medium leading-6 text-indigo-600 transition duration-150 ease-in-out bg-white border border-transparent rounded-md hover:text-indigo-500 focus:outline-none">
                hello!!
              </button>
            </div>
          </div>
        </div>
      </div>
    </TransitionChild>
  </TransitionRoot>
</div>

  <!-- dialog -->
  <TransitionRoot appear :show="connnectFailDialog" as="template">
    <Dialog as="div" class="relative z-10">
      <TransitionChild as="template" enter="duration-300 ease-out" enter-from="opacity-0" enter-to="opacity-100"
        leave="duration-200 ease-in" leave-from="opacity-100" leave-to="opacity-0">
        <div class="fixed inset-0 bg-black bg-opacity-25" />
      </TransitionChild>

      <div class="fixed inset-0 overflow-y-auto">
        <div class="flex items-center justify-center min-h-full p-4 text-center">
          <TransitionChild as="template" enter="duration-300 ease-out" enter-from="opacity-0 scale-95"
            enter-to="opacity-100 scale-100" leave="duration-200 ease-in" leave-from="opacity-100 scale-100"
            leave-to="opacity-0 scale-95">
            <DialogPanel
              class="w-full max-w-md p-6 overflow-hidden text-left align-middle transition-all transform bg-white shadow-xl rounded-2xl">
              <DialogTitle as="h3" class="text-lg font-medium leading-6 text-gray-900">
                连接失败
              </DialogTitle>
              <div class="mt-2">
                <p class="text-sm text-gray-500">
                  websocket连接失败，请检查网络
                </p>
              </div>

              <div class="mt-4">
                <button type="button"
                  class="inline-flex justify-center px-4 py-2 mx-2 text-sm font-medium text-blue-900 bg-blue-100 border border-transparent rounded-md hover:bg-blue-200 focus:outline-none "
                  @click="connnectFailDialog = false; $router.push('/')">
                  重试
                </button>
                <button type="button"
                  class="inline-flex justify-center px-4 py-2 mx-2 text-sm font-medium text-blue-900 bg-blue-100 border border-transparent rounded-md hover:bg-blue-200 focus:outline-none "
                  @click="connnectFailDialog = false;">
                  忽略
                </button>
              </div>
            </DialogPanel>
          </TransitionChild>
        </div>
      </div>
    </Dialog>
  </TransitionRoot>
</template>




<script>
export default {
  setup() {
    useHead({
      title: 'Websocket',
    })
  },
  data() {
    return {
      webSocket: null,
      url: '127.0.0.1:8765',
      messages: ref([]),
      connnectFailDialog: false,
      WSpannel: false,
      Connected: false,
      path_input:'D:\\testCode.exe',
    }
  },
  methods: {
    // 建立连接
    initSocket() {
      // 有参数的情况下：
      let url = `ws://${this.url}`
      // 没有参数的情况:接口
      // let url1 = 'ws://localhost:9998'
      this.webSocket = new WebSocket(url)
      this.webSocket.onopen = this.webSocketOnOpen
      this.webSocket.onclose = this.webSocketOnClose
      this.webSocket.onmessage = this.webSocketOnMessage
      this.webSocket.onerror = this.webSocketOnError
    },
    // 建立连接成功后的状态
    webSocketOnOpen() {
      console.log('websocket连接成功');
      this.Connected = true;
    },
    // 获取到后台消息的事件，操作数据的代码在onmessage中书写
    webSocketOnMessage(res) {
      // res就是后台实时传过来的数据
      //console.log(res);
      if(res.data=="start success"){
        this.WSpannel = false;
        return;
      }
      this.messages.push({ title: res.data })
      try {
        let msg = JSON.parse(res.data)
        if (msg.hasOwnProperty("apiName")) {
          this.$emitter.emit('recv_hook', msg)
        }
      } catch (e) {
      }
      
    },
    // 关闭连接
    webSocketOnClose() {
      this.webSocket.close()
      console.log('websocket连接已关闭');
      this.Connected = false;
    },
    //连接失败的事件
    webSocketOnError(res) {
      console.log('websocket连接失败');
      // 打印失败的数据
      this.connnectFailDialog = true
      console.log(res);
    },
    sendobj(obj) {
      this.webSocket.send(JSON.stringify(obj))
    },
    startprocess() {
      this.sendobj({ cmd: 'start' ,path:this.path_input})
    },
  },
  created() {
    // 页面打开就建立连接，根据业务需要
    this.initSocket()
    //供其他函数调用
    //console.log(this.$emitter);
    this.$emitter.on('send', data => {
      this.sendobj(data)
    });
    
  },
  destroyed() {
    // 页面销毁关闭连接
    this.webSocket.close()
  },
}


</script>