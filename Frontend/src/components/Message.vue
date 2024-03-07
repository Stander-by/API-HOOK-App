<template>
<div class="shadow-sm bg-white rounded-md p-2">
  {{title}}
</div>
</template>
  
  <script>
  import { defineComponent } from 'vue'
  
  export default defineComponent({
    name: 'WSmessage',
    props: {
      title: {
        type: String,
        required: true
      },
    }
  })
  </script>
  