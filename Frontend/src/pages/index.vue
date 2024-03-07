<route lang="json">
{
  "meta": {
    "title": "概览"
  }
}
</route>

<script setup>
import * as echarts from "echarts";
import sizedata from '../assets/echarts-package-size.json'
useHead({
      title: 'Home',
    })
  
onMounted(() => {
initchart();
})


function initchart(){
  
  let myChart = echarts.init(document.getElementById("chart_treemap"));
  var option;
  var data=sizedata;
  const treemapOption = {
    series: [
      {
        type: 'treemap',
        id: 'echarts-package-size',
        animationDurationUpdate: 1000,
        roam: false,
        nodeClick: undefined,
        data: data.children,
        universalTransition: true,
        label: {
          show: true
        },
        breadcrumb: {
          show: false
        }
      }
    ]
  };

  const sunburstOption = {
    series: [
      {
        type: 'sunburst',
        id: 'echarts-package-size',
        radius: ['20%', '90%'],
        animationDurationUpdate: 1000,
        nodeClick: undefined,
        data: data.children,
        universalTransition: true,
        itemStyle: {
          borderWidth: 1,
          borderColor: 'rgba(255,255,255,.5)'
        },
        label: {
          show: false
        }
      }
    ]
  };

  let currentOption = treemapOption;

  myChart.setOption(currentOption);

  setInterval(function () {
    currentOption =
      currentOption === treemapOption ? sunburstOption : treemapOption;
    myChart.setOption(currentOption);
  }, 3000);
  option && myChart.setOption(option);
}
</script>
  



<template>

  <div id="chart_treemap" class="w-screen h-screen p-20"></div>

  <div class="h-screen bg-gray-50">
    <div class="max-w-screen-xl px-4 py-12 mx-auto sm:px-6 lg:flex lg:items-center lg:justify-between lg:py-16 lg:px-8">
      <h2 class="text-3xl font-extrabold leading-9 tracking-tight text-gray-900 sm:text-4xl sm:leading-10">
        Ready to dive in?
        <br />
        <span class="text-indigo-600">Vite + Vue 3 + Tailwind CSS</span>
      </h2>
      <div class="flex mt-8 lg:mt-0 lg:flex-shrink-0">
        <div class="inline-flex rounded-md shadow">
          <router-link to="/about"
            class="inline-flex items-center justify-center px-5 py-3 text-base font-medium leading-6 text-white transition duration-150 ease-in-out bg-indigo-600 border border-transparent rounded-md hover:bg-indigo-500 focus:outline-none">
            Next Page</router-link>
        </div>
        <ButtonRepo />
      </div>
    </div>
  </div>

</template>
