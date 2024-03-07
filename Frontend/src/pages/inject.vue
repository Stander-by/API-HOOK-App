
<template>

    <div class="h-screen bg-gray-50">
        <!-- 数据列表 -->
        <another />
        <div class="flex flex-row bg-gray-100">
            
            <TabGroup>
            <!-- 左 -->
            <div class="flex-grow-0 h-screen bg-slate-50" style="width:37%">
                <div class="max-h-screen rounded bg-gray-50">
                    <div class="flex items-center justify-between max-h-screen px-4 py-6">
                        <div
                            class="flex-auto max-h-screen overflow-y-scroll p-t-4 vertical-align scrollbar-thin scrollbar-thumb-indigo-600 scrollbar-thumb-rounded-full scrollbar-track-rounded-full">
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
                        </div>
                    </div>
                </div>
            </div>
            <!-- 右 -->
            <div class="flex-grow h-screen bg-zinc-50">
                <div class="w-full px-2 ">
                        

                        <TabPanels class="mt-2">
                            <TabPanel v-for="(posts, idx) in Object.values(categories)" :key="idx" :class="[
                              'rounded-xl bg-white p-3',
                              'ring-white ring-opacity-60 ring-offset-2 ring-offset-indigo-500 focus:outline-none focus:ring-2',
                            ]">
                                <ul>
                                    <li v-for="post in posts" :key="post.id"
                                        class="relative p-3 rounded-md hover:bg-gray-100">

                                        <Disclosure v-slot="{ open }">
                                            <DisclosureButton
                                                class="flex justify-between w-full px-4 py-2 text-sm font-medium text-left bg-white rounded-lg text-neutral-900 focus:outline-none focus-visible:ring ">
                                                <h3 class="text-sm font-medium leading-5">
                                                    {{ post.title }}
                                                </h3>
                                                <ChevronUpIcon :class="open ? 'rotate-180 transform' : ''"
                                                    class="w-5 h-5 text-indigo-500" />
                                            </DisclosureButton>
                                            <DisclosurePanel>
                                                <ul
                                                    class="flex mt-1 space-x-1 text-xs font-normal leading-4 text-gray-500">
                                                    <li>{{ post.date }}</li>
                                                    <li>&middot;</li>
                                                    <li>{{ post.commentCount }} comments</li>
                                                    <li>&middot;</li>
                                                    <li>{{ post.shareCount }} shares</li>
                                                </ul>
                                            </DisclosurePanel>
                                        </Disclosure>
                                    </li>
                                </ul>
                            </TabPanel>

                        </TabPanels>
                </div>
            </div>
        </TabGroup>
        </div>

    </div>
</template>
    
<script setup>
import { TabGroup, TabList, Tab, TabPanels, TabPanel } from '@headlessui/vue'
let categories = ref({
    Recent: [
        {
            id: 1,
            title: 'Does drinking coffee make you smarter?',
            date: '5h ago',
            commentCount: 5,
            shareCount: 2,
        },
        {
            id: 2,
            title: "So you've bought coffee... now what?",
            date: '2h ago',
            commentCount: 3,
            shareCount: 2,
        },
    ],
    Popular: [
        {
            id: 1,
            title: 'Is tech making coffee better or worse?',
            date: 'Jan 7',
            commentCount: 29,
            shareCount: 16,
        },
        {
            id: 2,
            title: 'The most innovative things happening in coffee',
            date: 'Mar 19',
            commentCount: 24,
            shareCount: 12,
        },
    ],
    Trending: [
        {
            id: 1,
            title: 'Ask Me Anything: 10 answers to your questions about coffee',
            date: '2d ago',
            commentCount: 9,
            shareCount: 5,
        },
        {
            id: 2,
            title: "The worst advice we've ever heard about coffee",
            date: '4d ago',
            commentCount: 1,
            shareCount: 2,
        },
    ],
})
</script>