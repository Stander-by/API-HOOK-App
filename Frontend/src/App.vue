<script setup>
let counter = ref(0)

setInterval(() => {
  counter.value++
}, 1000)
</script>

<template>
  <div class="flex flex-row w-screen h-screen ">
    <side-nav />
    <div class="flex-auto p-4 overflow-scroll scrollbar-none">
      <header class="bg-white shadow" v-if="$route.meta.title">
        <div class="px-4 py-6">
          <h1 @click="counter = 0" class="text-3xl font-bold leading-tight text-gray-900"
            title="click to reset a counter">
            {{ $route.meta.title }} / {{ counter }}
          </h1>
        </div>
      </header>

      <!-- websocket组件 -->
      <websocket />
      <!-- 路由页面 -->
      <main>
        <router-view />
      </main>
    </div>

  </div>
</template>
