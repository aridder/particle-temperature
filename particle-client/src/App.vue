<template>
  <div id="app">
    <router-view />

    <div class="overlay" v-show="loading">
      <div class="loading-spinner">
        <div class="dot dotOne"></div>
        <div class="dot dotTwo"></div>
        <div class="dot dotThree"></div>
      </div>
    </div>
  </div>
</template>

<script>
import {useGetters} from "@u3u/vue-hooks";
export default {
  setup() {
    const { loading } = useGetters(["loading"]);

    return {
      loading
    };
  }
};
</script>

<style lang="scss">

body {
  background-color: #673ab7;
}

.loading-spinner {
  position: absolute;
  top: 10%;
  left: 50%;
  -webkit-transform: translateX(-50%) translateY(-50%);
  -moz-transform: translateX(-50%) translateY(-50%);
  transform: translateX(-50%) translateY(-50%);
}

.dot {
  background: black;
  border-radius: 100%;
  color: white;
  height: 8px;
  line-height: 8px;
  text-align: center;
  width: 8px;
}

.dotOne {
  -webkit-animation: dotOneKeyframes 5s ease infinite;
  background: #f9e610;
  position: absolute;
  top: 0;
  left: 0;
}

.dotTwo {
  -webkit-animation: dotTwoKeyframes 5s ease 0.4166666666666s infinite;
  background: #efdb06;
  position: absolute;
  top: 0;
  left: 14px;
}

.dotThree {
  -webkit-animation: dotThreeKeyframes 5s ease 0.83333333333s infinite;
  background: #dbc906;
  position: absolute;
  top: 14px;
  left: 14px;
}

@-webkit-keyframes dotOneKeyframes {
  0% {
    top: 0;
    left: 0;
  }
  8.3333333333% {
    top: 14px;
    left: 0;
  }
  16.6666666666% {
  }
  25% {
    top: 14px;
    left: 0;
  }
  33.3333333333% {
    top: 14px;
    left: 14px;
  }
  41.6666666666% {
  }
  50% {
    top: 14px;
    left: 14px;
  }
  58.3333333333% {
    top: 0;
    left: 14px;
  }
  66.6666666666% {
  }
  75% {
    top: 0;
    left: 14px;
  }
  83.3333333333% {
    top: 0;
    left: 0;
  }
  91.6666666666% {
  }
  100% {
  }
}

@-webkit-keyframes dotTwoKeyframes {
  0% {
    top: 0;
    left: 14px;
  }
  8.3333333333% {
    top: 0;
    left: 0;
  }
  16.6666666666% {
  }
  25% {
    top: 0;
    left: 0;
  }
  33.3333333333% {
    top: 14px;
    left: 0;
  }
  41.6666666666% {
  }
  50% {
    top: 14px;
    left: 0;
  }
  58.3333333333% {
    top: 14px;
    left: 14px;
  }
  66.6666666666% {
  }
  75% {
    top: 14px;
    left: 14px;
  }
  83.3333333333% {
    top: 0;
    left: 14px;
  }
  91.6666666666% {
  }
  100% {
  }
}

@-webkit-keyframes dotThreeKeyframes {
  0% {
    top: 14px;
    left: 14px;
  }
  8.3333333333% {
    top: 0;
    left: 14px;
  }
  16.6666666666% {
  }
  25% {
    top: 0;
    left: 14px;
  }
  33.3333333333% {
    top: 0;
    left: 0;
  }
  41.6666666666% {
  }
  50% {
    top: 0;
    left: 0;
  }
  58.3333333333% {
    top: 14px;
    left: 0;
  }
  66.6666666666% {
  }
  75% {
    top: 14px;
    left: 0;
  }
  83.3333333333% {
    top: 14px;
    left: 14px;
  }
  91.6666666666% {
  }
  100% {
  }
}
</style>
