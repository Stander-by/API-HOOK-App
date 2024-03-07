<template>
    <div class="flex flex-col justify-center px-2 bg-white shadow w-14 rounded-r-xl">
        <div class="mx-auto">
            <HomeIcon class="w-8 h-8 my-4 text-indigo-600 cursor-pointer hover:scale-110"
            @click="$router.push('/')"/>
            <ChartPieIcon class="w-8 h-8 my-4 text-indigo-600 cursor-pointer hover:scale-110"
            @click="$router.push('/status')" />
            <CodeBracketSquareIcon class="w-8 h-8 my-4 text-indigo-600 cursor-pointer hover:scale-110" 
            @click="$router.push('/inject')"/>
        </div>
    </div>
</template>
<script>
import { HomeIcon, ChartPieIcon, CodeBracketSquareIcon } from '@heroicons/vue/24/outline'

export default {
    components: { HomeIcon, ChartPieIcon, CodeBracketSquareIcon }
}
</script>
    