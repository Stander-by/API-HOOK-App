<template>


    <div class="dev mx-4">
        <h1 class="bg-gray-200">
            {{ selectedPerson }}

        </h1>
        <div class="flex flex-row h-20 my-8">
            <Listbox v-model="selectedPerson" class=" w-60 my-4">
                <div class="relative mt-1">
                    <ListboxButton
                        class="relative w-full cursor-default rounded-lg bg-white py-2 pl-3 pr-10 text-left shadow-md focus:outline-none focus-visible:border-indigo-500 focus-visible:ring-2 focus-visible:ring-white focus-visible:ring-opacity-75 focus-visible:ring-offset-2 focus-visible:ring-offset-orange-300 sm:text-sm">
                        <span class="block truncate">{{ selectedPerson.name }}</span>
                        <span class="pointer-events-none absolute inset-y-0 right-0 flex items-center pr-2">
                            <ChevronUpDownIcon class="h-5 w-5 text-gray-400" aria-hidden="true" />
                        </span>
                    </ListboxButton>
                    <transition leave-active-class="transition duration-100 ease-in" leave-from-class="opacity-100"
                        leave-to-class="opacity-0">
                        <ListboxOptions
                            class="absolute mt-1  w-full overflow-auto rounded-md bg-white py-1 text-base shadow-lg ring-1 ring-black ring-opacity-5 focus:outline-none sm:text-sm">
                            <ListboxOption v-slot="{ active, selected }" v-for="person in people" :key="person.name"
                                :value="person" as="template" @click="ShowPage=true">
                                <li :class="[
                                  active ? 'bg-amber-100 text-amber-900' : 'text-gray-900',
                                  'relative cursor-default select-none py-2 pl-10 pr-4',
                                ]">
                                    <span :class="[
                                      selected ? 'font-medium' : 'font-normal',
                                      'block truncate',
                                    ] ">

                                        {{ person.name }}


                                    </span>
                                    <span v-if="selected"
                                        class="absolute inset-y-0 left-0 flex items-center pl-3 text-amber-600 ">
                                        <CheckIcon class="h-5 w-5" aria-hidden="true" />
                                    </span>
                                </li>
                            </ListboxOption>
                        </ListboxOptions>
                    </transition>
                </div>
            </Listbox>
            <div class="w-20 my-2 mx-4">
                <TrashIcon style="width: 2em; height: 2em; margin-right: 8px;" @click="deleteEle()" />
            </div>
            <div class="flex-auto shadow text-indigo-600 text-center text-xl bg- h-28 rounded-xl">
                {{ selectedPerson }}
            </div>
        </div>
        <!-- 卡片页面 -->
        <ul class="bg-gray-50 my-12">
            <div class="grid grid-col grid-cols-3 grid-rows-3 gap-4">
                <li v-for="(item) in itemArr">
                    <!--   <el-input v-model="item.content"></el-input> -->
                    <div class=" bg-gray-200 text-indigo-600 mb-4 rounded-xl w-auto h-48 hover:bg-gray-400">
                        <header class=" top-1 left-1 text-black">
                        <b>{{item.content.name}}</b>
                        </header>
                        <div class="mx-6 my-3 h-32 shadow rounded-xl bg-gray-300">
                            <div>
                                {{item.content}}
                            </div>
                            <div class="hover:bg-black" @click="addEle(1)">
                                <AdjustmentsHorizontalIcon style="width: 2em; height: 2em; margin-right: 8px;" />
                            </div>
                           
                        </div>
                        <div class="-insert-y-1 ">
                            <AdjustmentsHorizontalIcon style="width: 2em; height: 2em; margin-right: 8px;" />
                        </div>

                    </div>
                </li>
            </div>
        </ul>


    </div>

    <!-- 对话框 -->
    <TransitionRoot appear :show=ShowPage as="template">
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
                            class="w-full max-w-md h-auto p-6 overflow-hidden text-left align-middle transition-all transform bg-white shadow-xl rounded-2xl">
                            <DialogTitle as="h3" class="text-lg font-medium leading-6 text-gray-900 my-4">
                                {{selectedPerson.name}}
                            </DialogTitle>
                            <div>
                                <input class="rounded-lg font-mono my-2" type="text"
                                    v-model="selectedPerson.Info_before" placeholder="Infor_before">
                                <input class="rounded-lg font-mono my-2" type="text" v-model="selectedPerson.Info_after"
                                    placeholder="Infor_after">
                            </div>

                            <div class="mt-4">
                                <button type="button"
                                    class="inline-flex justify-center px-4 py-2 mx-2 text-sm font-medium text-blue-900 bg-blue-100 border border-transparent rounded-md hover:bg-blue-200 focus:outline-none "
                                    @click="ShowPage=false; addEle(selectedPerson);">
                                    add
                                </button>
                                <button type="button"
                                    class="inline-flex justify-center px-4 py-2 mx-2 text-sm font-medium text-blue-900 bg-blue-100 border border-transparent rounded-md hover:bg-blue-200 focus:outline-none "
                                    @click="ShowPage=false">
                                    Esc
                                </button>
                            </div>
                        </DialogPanel>
                    </TransitionChild>
                </div>
            </div>
        </Dialog>
    </TransitionRoot>

</template> 
  
<script setup>
import { ref } from 'vue'
import { AdjustmentsHorizontalIcon, TrashIcon, HomeIcon } from '@heroicons/vue/24/outline'
import {
    Listbox,
    ListboxButton,
    ListboxOptions,
    ListboxOption,
} from '@headlessui/vue'
const people = [
    { id: 1, name: 'Api1', unavailable: true, Info_before: "", Info_after: "",num:0 },
    { id: 2, name: 'Api2', unavailable: true, Info_before: "", Info_after: "",num:0 },
    { id: 3, name: 'Api3', unavailable: true, Info_before: "", Info_after: "",num:0 },
    { id: 4, name: 'Api4', unavailable: true, Info_before: "", Info_after: "",num:0 },
    { id: 5, name: 'Api5', unavailable: true, Info_before: "", Info_after: "",num:0 },
]
const selectedPerson = ref(people[0])
let msg = "this a good "
let count = 0
let ShowPage = ref(false)
let itemArr = [{
    content: { id: 1, name: 'Api0', unavailable: true, Info_before: "", Info_after: "" }
}]

// 点击添加
function addEle(id) {
    if(id==1){
        console.log("S");
    }
    count++;
    selectedPerson.id=count;
    itemArr.push({
        content: selectedPerson
    })


}
// 删除一项
function deleteEle(index) {
    console.log("ff")
    itemArr.splice(index, 1);
}


</script>