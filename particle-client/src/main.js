import Vue from 'vue'
import App from './App.vue'
import router from './router'
import store from './store/index'
import hooks from '@u3u/vue-hooks'
import VueCompositionApi from '@vue/composition-api';

Vue.use(VueCompositionApi);
Vue.use(hooks);
Vue.config.productionTip = false

new Vue({
  router: router,
  store: store,
  render: function (h) { return h(App) }
}).$mount('#app')
