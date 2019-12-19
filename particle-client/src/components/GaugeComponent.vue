<template>
    <div v-if="!loading" class="gauge">
        <h1 class="gauge-title">{{title}}</h1>
        <div class="gauge-main">
            <i class="material-icons"></i>
            <h1 class="gauge-value">{{value + calibrationValue}}°</h1>
        </div>
        <button v-if="!calibrate" @click="toggleCalibrate">Calibrate</button>
        <div v-if="calibrate" class="calibration-container">
            <p class="calibration-title">Kalibrer</p>
            <p class="calibration-warning">Advarsel: Dette endrer målingen for alltid</p>
            <input v-model.number="vCalibrationValue" type="number" placeholder="0.00">
            <button @click="approveCalibration">Bekreft</button>
        </div>
    </div>
</template>

<script>

    import {ref} from '@vue/composition-api';
    import store from '../store/index'
    import {useGetters} from "@u3u/vue-hooks";


    export default {
        name: 'DashboardComponent.vue',
        components: {},
        props: {
            title: String,
            value: Number,
            calibrationValue: Number,
            calibrationFunc: String
        },
        setup(props) {

            const calibrate = ref(false);
            const {loading, error} = useGetters(['loading', 'error']);
            const vCalibrationValue = ref(props.calibrationValue);
            const vTitle = ref(props.title);
            const vValue = ref(props.value);

            const toggleCalibrate = () => {
                calibrate.value = !calibrate.value
            };

            const approveCalibration = () => {
                store.dispatch(props.calibrationFunc, {
                    deviceId:process.env.VUE_APP_DEVICE_ID,
                    value:vCalibrationValue.value
                });
            };

            return {
                toggleCalibrate,
                approveCalibration,
                vCalibrationValue,
                calibrate,
                loading,
                error,
                vTitle,
                vValue
            }
        }
    }
</script>

<style scoped lang="scss">

    .gauge {

        border-radius: 4px;
        width: 150px;

        background: #9a67ea;
        overflow: hidden;

        display: flex;
        flex-direction: column;

        margin: 15px;
        border-color: #000;
        border-width: 20px;

        &:hover {
            box-shadow: 0 1px 2px rgba(0, 0, 0, .25);
        }

        .gauge-title {
            margin: 0;
            font-size: 15px;
            color: #673ab7;
            text-align: center;
            font-weight: 600;
            border-bottom: 1px solid #673ab7;
            background-color: #FFF;
            top: 0;
            padding: 5px 10px;
        }

        .gauge-main {
            display: flex;
            flex-direction: column;
            justify-content: center;
            align-items: center;
            padding: 15px 0;
        }

        .gauge-value {
            color: #FFF;
            font-size: 20spx;
            text-align: center;
        }

        .material-icons {
            font-size: 36px;
            color: #000;
            margin-bottom: 5px;
        }

    }
</style>