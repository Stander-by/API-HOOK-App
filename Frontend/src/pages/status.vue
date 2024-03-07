<route lang="json">
{
    "meta": {
        "title": "数据"
    }
}
</route>
    
<script setup>
import * as echarts from "echarts";
import { getCurrentInstance } from 'vue'
import { ref } from 'vue'
import { Disclosure, DisclosureButton, DisclosurePanel } from '@headlessui/vue'
import { ChevronUpIcon } from '@heroicons/vue/20/solid'
import { TabGroup, TabList, Tab, TabPanels, TabPanel } from '@headlessui/vue'
useHead({
    title: '数据',
})

const apiType=['MessageBox', 'File','Reg','Heap','Socket']
//右侧数据详情
let categories = ref({
    // "概览": [
    // {'API名称':""},
    // ],
    "输入": [
        {'请选择':""}
    ],
    "输出": [
    {'请选择':""}

    ],
    "安全性":[
    {'请选择':""}
    ]
})
let stackMessages = ref([])
//时间筛选
let start = ref(0)
let end = ref(0)
//类别筛选
let type_selected=ref({MessageBox: true, File: true, Reg: true, Heap: true, Socket: true})
let stackMsgFiltered=computed(()=>
stackMessages.value
// .filter(
//     item=>item.time>=start.value &&item.time<=end.value
//     &&type_selected.value[item.type]==true)
)
const instance = getCurrentInstance()
let emitter = instance.appContext.config.globalProperties.$emitter

let myChart;
let option;
let data= []
option = {
        tooltip: {
            trigger: 'axis'
        },
        title: {
            text: 'API捕获',
            left: 'center'
        },
        legend: {
            top: 40,
            data: apiType
        },
        dataZoom: [
            {
                type: 'inside',
                // start: 0,
                // end: 10
            },
            {
                //start: 0,
                //end: 0
            },
        ],
        singleAxis: {
            // top: '8%',
            axisTick: {},
            axisLabel: {},
            type: 'time',
            // position: 'top',
            splitLine: {
                show: true,
                lineStyle: {
                    type: 'dashed',
                    opacity: 0.2
                }
            }
        },
        series: [
            {
                type: 'themeRiver',
                itemStyle: {
                    emphasis: {
                        shadowBlur: 20,
                        shadowColor: 'rgba(0, 0, 0, 0.5)'
                    }
                },
                data: data
            }
        ]
    };
onMounted(() => {
    myChart= echarts.init(document.getElementById("chart"));
    initchart();
    //监听数据消息

    //更新数据消息
    // setInterval(() => {
    //     let nowtime=new Date().getTime()
    //     for (let i in apiType) {
    //     option.series[0].data.push([nowtime, 0, apiType[i]]);
    //     } 
    //     myChart.setOption(option);
    // }, 1000);
    
    emitter.on('recv_hook', data => {
        data.safetywarn = false
        if (data.hasOwnProperty("safety")) {
            for (let i in data['safety']) {
                if (data['safety'][i]['value']) {
                    data.safetywarn = true
                }
            }
        }
        stackMessages.value.push(data)
      //option.series[0].data.push([data.time, 10 ,data.type]);
      //更新图表
        for (let i in apiType) {
            if (apiType[i] == data.type) {
                option.series[0].data.push([data.time, 100, apiType[i]]);
            }
            else {
                option.series[0].data.push([data.time, 0, apiType[i]]);
            }
        } 
        // myChart.dispatchAction({
        //     type: 'dataZoom',
        // }); 
      //console.log("push",,data.type=='MessageBox',data.type)

      myChart.setOption(option);
    });
    emitter.on('updateDetail', id => {
        //console.log(id)
        let current = stackMessages.value.find(item => item.id == id)
        categories.value["输入"]=[]
        categories.value["输出"]=[];
        categories.value["安全性"]=[]

        if(current.hasOwnProperty("param")){
            for (let key in current.param) {
                categories.value["输入"].push({[key]:current.param[key]})
            }
        }
        
        if(current.hasOwnProperty("return")){
            for (let key in current['return']) {
                categories.value["输出"].push({[key]:current.return[key]})
            }
        }        
        
        if(current.hasOwnProperty("safety")){
            for (let key in current.safety) {
                categories.value["安全性"].push({[key]:current.safety[key]})
            }
        }
    });
})

function initchart() {
    myChart.on('dataZoom', function () {
        var option = myChart.getOption();
        start.value = option.dataZoom[0].startValue.toPrecision(13);
        end.value = option.dataZoom[0].endValue.toPrecision(13);    
        //console.log(stackMsgFiltered.value)
    });
    window.onresize = function () {
        myChart.resize();
    };
    myChart.setOption(option);
    //初始化数据缩放范围
    // myChart.dispatchAction({
    //     type: 'dataZoom',
    //     startValue: 0,
    //     endValue: 1000
    // });

    //更新筛选的数据范围
    myChart.on('legendselectchanged', (data) => {
        type_selected.value=data.selected
        console.log(type_selected.value)
    })
}

function addData() {

    //由websocket组件监听
    emitter.emit('send', { "title": "add" })
}


function formatDate(value) {
        let date = new Date(parseInt(value));
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
        return  h + ":" + m + ":" + s;
}
</script>
    
<template>
    <div id="chart" class="mt-8" :style="{ width: '100%', height: '600px' }"></div>

    <div class="h-screen bg-gray-50">

        <div
            class="max-w-screen-xl px-4 py-12 mx-auto sm:px-6 lg:flex lg:items-center lg:justify-between lg:py-16 lg:px-8">
            <h2 class="text-3xl font-extrabold leading-9 tracking-tight text-gray-900 sm:text-4xl sm:leading-10">
                About Page
                <br />
                <span class="text-indigo-600">Vite + Vue 3 + Tailwind CSS</span>
            </h2>
            <div class="text-3xl font-extrabold leading-9 tracking-tight text-gray-900 ">
                 {{formatDate(start) }} / {{formatDate(end) }}
                
            </div>
            <div class="flex mt-8 lg:mt-0 lg:flex-shrink-0">
                <div class="inline-flex rounded-md shadow">
                    <router-link to="/"
                        class="inline-flex items-center justify-center px-5 py-3 text-base font-medium leading-6 text-white transition duration-150 ease-in-out bg-indigo-600 border border-transparent rounded-md hover:bg-indigo-500 focus:outline-none">
                        Home</router-link>
                </div>
                <div
                    class="inline-flex ml-3 transition duration-150 ease-in-out rounded-md shadow hover:-translate-y-1">
                    <button
                        class="inline-flex items-center justify-center px-5 py-3 text-base font-medium leading-6 text-indigo-600 bg-white border border-transparent rounded-md focus:outline-none"
                        @click="addData()">
                        Add a data
                    </button>
                </div>
            </div>
        </div>

        
        <div class="flex flex-row bg-gray-100">
            <!-- 数据列表 -->
            <div class="flex-grow-0 h-screen bg-slate-50" style="width:37%">
                <!-- <header class="mx-4 my-4 text-3xl font-extrabold leading-9 tracking-tight text-gray-900 sm:text-4xl sm:leading-10">
                    Top
                </header> -->
                <div class="max-h-screen bg-gray-100 rounded-lg">
                    <div class="flex items-center justify-between max-h-screen px-4 py-6">
                        <div
                            style="max-height:85vh;"
                            class="flex-auto overflow-y-scroll p-t-4 vertical-align scrollbar-thin scrollbar-thumb-indigo-600 scrollbar-thumb-rounded-full scrollbar-track-rounded-full">
                            <li v-for="(stackMessage) in stackMsgFiltered" style="list-style-type: none;" class="p-2 pr-5">
                                <stack-message :apiName="stackMessage.apiName" :shortInfo="stackMessage.shortInfo"
                                    :time="stackMessage.time" :id="stackMessage.id" :safetywarn="stackMessage.safetywarn">
                                </stack-message>
                            </li>
                        </div>
                    </div>
                </div>
            </div>

            <!-- 数据详情 -->
            <div class="flex-grow h-screen bg-zinc-50">
                <div class="w-full px-2 ">
                    <TabGroup>
                        <TabList class="flex p-1 space-x-1 bg-gray-400 rounded-xl">
                            <Tab v-for="category in Object.keys(categories)" as="template" :key="category"
                                v-slot="{ selected }">
                                <button :class="[
                                  'w-full rounded-lg py-2.5 text-sm font-medium leading-5 text-indigo-600',
                                  
                                  'ring-white ring-opacity-20 ring-offset-1 focus:outline-none focus:ring-2',
                                  selected
                                    ? 'bg-white shadow'
                                    : 'text-white hover:bg-white/[0.12] hover:text-white',
                                ]">
                                    {{ category }}
                                </button>
                            </Tab>
                        </TabList>

                        <TabPanels class="mt-2">
                            <TabPanel v-for="items in Object.values(categories)" :class="[
                              'rounded-xl bg-white p-3',
                              'ring-white ring-opacity-60 ring-offset-2 focus:outline-none focus:ring-2',
                            ]">
                                <ul>
                                    <li v-for="item in items"
                                        class="relative p-3 rounded-md hover:bg-gray-100">

                                        <Disclosure :defaultOpen="true" v-slot="{ open }">
                                            <DisclosureButton
                                                class="flex justify-between w-full px-4 py-2 text-sm font-medium text-left bg-white rounded-lg text-neutral-900 focus:outline-none focus-visible:ring ">
                                                <h3 class="text-sm font-medium leading-5">
                                                    {{ Object.keys(item)[0] }} / 
                                                    {{ (Object.values(item)[0])['description'] }}

                                                </h3>
                                                <ChevronUpIcon :class="open ? 'rotate-180 transform' : ''"
                                                    class="w-5 h-5 text-indigo-500" />
                                            </DisclosureButton>
                                            <transition enter-active-class="transition ease-out duration-50" enter-from-class="transform scale-95 opacity-0"
                                                enter-to-class="transform scale-100 opacity-100" leave-active-class="transition duration-75 ease-out"
                                                leave-from-class="transform scale-100 opacity-100" leave-to-class="transform scale-95 opacity-0">
                                            <DisclosurePanel >
                                                <ul
                                                    class="flex mt-1 space-x-1 font-normal leading-4 text-gray-500 text-x">
                                                    
                                                    {{ (Object.values(item)[0])['value'] }}
                                                    
                                                 
                                                </ul>
                                            </DisclosurePanel>
                                        </transition>
                                        </Disclosure>
                                    </li>
                                </ul>
                            </TabPanel>

                        </TabPanels>
                    </TabGroup>
                </div>
            </div>
        </div>

    </div>
</template>
    