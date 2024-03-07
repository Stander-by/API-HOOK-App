# Vite, Vue3, Tailwind CSS (single-page app)

![Vite, Vue, Tailwind CSS](https://user-images.githubusercontent.com/11320080/111277027-a9384c00-8640-11eb-8323-21889bd7c609.png)

This starter template includes:

- [Vite 3](https://vitejs.dev/guide/)
- [Vue 3](https://vuejs.org/guide/introduction.html)
- [Tailwind CSS 3](https://tailwindcss.com/docs/configuration)
- [Vue Router](https://github.com/vuejs/router)
- [@vueuse/head](https://github.com/vueuse/head) - document head manager
- [TypeScript](https://vuejs.org/guide/typescript/overview.html) - write vue files as `<script setup>` or `<script setup lang="ts">`
- [Inter var font](https://github.com/rsms/inter) (self-hosted, woff2, v3.19, with 'preload' attr, check out index.html)
- [Headless UI](https://headlessui.com/vue/menu) - unstyled UI components, designed to integrate beautifully with Tailwind CSS
- [Heroicons](https://github.com/tailwindlabs/heroicons) - beautiful hand-crafted SVG icons,
  by the makers of Tailwind CSS
- [prettier-plugin-tailwindcss](https://tailwindcss.com/blog/automatic-class-sorting-with-prettier) - automatic class sorting with Prettier

First-party plugins needed for Tailwind UI:

- [tailwindcss/forms](https://github.com/tailwindlabs/tailwindcss-forms)
- [tailwindcss/line-clamp](https://github.com/tailwindlabs/tailwindcss-line-clamp)
- [tailwindcss/typography](https://tailwindcss.com/docs/typography-plugin)
- [tailwindcss/aspect-ratio](https://github.com/tailwindlabs/tailwindcss-aspect-ratio)

Unplugin Utilities:

- [unplugin-vue-components](https://github.com/antfu/unplugin-vue-components) - components auto importing
- [unplugin-auto-import](https://github.com/antfu/unplugin-auto-import) - auto import the most used APIs
- [unplugin-vue-router](https://github.com/posva/unplugin-vue-router) - file based routing for vue-router

### Getting Started

```sh
npx degit web2033/vite-vue3-tailwind-starter vvt-app
cd vvt-app
```

```sh
npm i
npm run dev
npm run build
npm run serve
```

[![Deploy to Netlify](https://www.netlify.com/img/deploy/button.svg)](https://app.netlify.com/start/deploy?repository=https://github.com/web2033/vite-vue3-tailwind-starter)
