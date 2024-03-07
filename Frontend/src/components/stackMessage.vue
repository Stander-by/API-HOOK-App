<template>
    <div class="p-2 mx-4 transition duration-100 ease-in-out bg-white rounded-md shadow-sm hover:translate-y-0 hover:scale-105 hover:ring-indigo-500 hover:ring-1 hover:cursor-pointer" @click="updateDetail(id)">
        <!-- {{apiName}}/{{shortInfo}}/{{time}}/{{id}}/{{safety}}  -->
        <header class="flex mx-auto my-auto">
            <!-- <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor"
                class="flex-none w-6 h-6">
                <path stroke-linecap="round" stroke-linejoin="round"
                    d="M7.5 8.25h9m-9 3H12m-9.75 1.51c0 1.6 1.123 2.994 2.707 3.227 1.129.166 2.27.293 3.423.379.35.026.67.21.865.501L12 21l2.755-4.133a1.14 1.14 0 01.865-.501 48.172 48.172 0 003.423-.379c1.584-.233 2.707-1.626 2.707-3.228V6.741c0-1.602-1.123-2.995-2.707-3.228A48.394 48.394 0 0012 3c-2.392 0-4.744.175-7.043.513C3.373 3.746 2.25 5.14 2.25 6.741v6.018z" />
            </svg> -->
    
        </header>
        <div class="pl-2">
            <div class="flex pr-2 my-0 top-2">
                <div class="flex-auto my-auto text-lg text-slate-900">
                    {{apiName}}
                </div>
        
                <div>
                    <p v-if="safetywarn" class="text-lg text-pink-600 ordinal">!</p>
                </div>
            </div>
        
            <div class="bottom-0 flex mt-4">
                <div class="flex-auto my-auto text-sm text-slate-700">
                    {{shortInfo}}
                </div>
        
                <div>
                    <p class="text-xs ordinal text-slate-700"> {{formatDate(time)}} / {{id+1}}</p>
                </div>
            </div>
        </div>
    </div>
</template>



<script>
import { defineComponent } from 'vue'


export default defineComponent({
    name: 'stackMessage',
    methods: {
        updateDetail(id) {
            this.$emitter.emit('updateDetail', id)
        },
        
        formatDate(value) {
        let date = new Date(value);
        let y = date.getFullYear();
        let MM = date.getMonth() + 1;
        MM = MM < 10 ? "0" + MM : MM;
        let d = date.getDate();
        d = d < 10 ? "0" + d : d;
        let h = date.getHours();
        h = h < 10 ? "0" + h : h;
        let m = date.getMinutes();
        m = m < 10 ? "0" + m : m;
        let s = date.getSeconds();
        s = s < 10 ? "0" + s : s;
        //return y + "-" + MM + "-" + d + " " + h + ":" + m + ":" + s;
        return   h + ":" + m + ":" + s;
}
    },
    props: {
        apiName: {
            //type: String,
            required: true
        },
        shortInfo: {
            //type: String,
            required: true,
        },
        time: {
            //type: String,
            required: true
        },
        id: {
            //type: Number,
            required: true
        },
        safetywarn: {
            //type: [],
            default: false
        },
    },
})
</script>
      