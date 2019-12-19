import Vue from 'vue'
import Vuex from 'vuex'
import types from '../types'
import axios from 'axios'

axios.defaults.baseURL = 'https://api.particle.io/v1/devices';

Vue.use(Vuex);

const store = new Vuex.Store({
    state: {
        loading: false,
        error: '',
        air: {
            humidity: {
                current: undefined,
                history: []
            },
            temperature: {
                current: undefined,
                history: []
            }
        },
        waterTemp: {
            current: undefined,
            history: []
        },
        calibration: {
            air: {
                temp: 0,
                humidity: 0,
                timeZone: 1
            },
            water: {
                temp: 0
            },
            timeZone: 1
        }
    },
    getters: {
        currentWaterTemp: state => {
            return state.waterTemp.current;
        },
        currentAirTemp: state => {
            return state.air.temperature.current;
        },
        currentAirHum: state => {
            return state.air.humidity.current;
        },
        getAllData: state => {
            return [
                {
                    title: "Lufttemperatur",
                    value: state.air.temperature.current,
                    calibrationValue: state.calibration.air.temp,
                    calibrationFunc: types.SET_CAL_AIR_TEMP
                },
                {
                    title: "Vanntemperatur",
                    value: state.waterTemp.current,
                    calibrationValue: state.calibration.water.temp,
                    calibrationFunc: types.SET_CAL_WATER_TEMP
                },
                {
                    title: "Luftfuktighet",
                    value: state.air.humidity.current,
                    calibrationValue: state.calibration.air.humidity,
                    calibrationFunc: types.SET_CAL_AIR_HUM
                }
            ]
        },
        loading: state => {
            return state.loading;
        },
        error: state => {
            return state.error;
        },
    },
    mutations: {
        [types.SET_LOADING](state, loading) {
            state.loading = loading;
        },
        [types.SET_ERROR](state, error) {
            state.error = error;
        },
        [types.SET_AIR_HUM](state, airHum) {
            state.air.humidity.current = airHum;
        },
        [types.SET_AIR_TEMP](state, airTemp) {
            state.air.temperature.current = airTemp;
        },
        [types.SET_WATER_TEMP](state, waterTemp) {
            state.waterTemp.current = waterTemp;
        },
        [types.SET_CAL_AIR_HUM](state, calibrationAirHum) {
            state.calibration.air.humidity = calibrationAirHum;
        },
        [types.SET_CAL_AIR_TEMP](state, calibrationAirTemp) {
            state.calibration.air.temp = calibrationAirTemp;
        },
        [types.SET_CAL_WATER_TEMP](state, calibrationWaterTemp) {
            state.calibration.water.temp = calibrationWaterTemp;
        }
    },
    actions: {
        async [types.FETCH_AIR_HUM]({commit}, deviceId) {
            commit(types.SET_LOADING, true);
            axios.get(`/${deviceId}/airHumidity`, {
                params: {
                    'access_token': process.env.VUE_APP_ACCESS_TOKEN
                }
            })
                .then(response => {
                    commit(types.SET_AIR_HUM, response.data.result)
                })
                .catch(err => {
                    commit(types.SET_ERROR, err);
                })
                .finally(() => commit(types.SET_LOADING, false));
        },
        async [types.FETCH_AIR_TEMP]({commit}, deviceId) {
            commit(types.SET_LOADING, true);

            axios.get(`/${deviceId}/airTemp`, {
                params: {
                    'access_token': process.env.VUE_APP_ACCESS_TOKEN
                }
            })
                .then(response => {
                    commit(types.SET_AIR_TEMP, response.data.result)
                })
                .catch(err => {
                    commit(types.SET_ERROR, err);
                })
                .finally(() => commit(types.SET_LOADING, false));
        },
        async [types.FETCH_WATER_TEMP]({commit}, deviceId) {

            axios.get(`/${deviceId}/waterTemp`, {
                params: {
                    'access_token': process.env.VUE_APP_ACCESS_TOKEN
                }
            })
                .then(response => {
                    commit(types.SET_WATER_TEMP, response.data.result)
                })
                .catch(err => {
                    commit(types.SET_ERROR, err);
                })
                .finally(() => commit(types.SET_LOADING, false));
        },
        async [types.FETCH_CAL_AIR_HUM]({commit}, deviceId) {

            axios.get(`/${deviceId}/airHumidityCalibration`, {
                params: {
                    'access_token': process.env.VUE_APP_ACCESS_TOKEN
                }
            })
                .then(response => {
                    commit(types.SET_CAL_AIR_HUM, response.data.result)
                })
                .catch(err => {
                    commit(types.SET_ERROR, err);
                }).finally(() => commit(types.SET_LOADING, false));
        },
        async [types.FETCH_CAL_AIR_TEMP]({commit}, deviceId) {

            axios.get(`/${deviceId}/airTempCalibrationValue`, {
                params: {
                    'access_token': process.env.VUE_APP_ACCESS_TOKEN
                }
            })
                .then(response => {
                    commit(types.SET_CAL_AIR_TEMP, response.data.result)
                })
                .catch(err => {
                    commit(types.SET_ERROR, err);
                }).finally(() => commit(types.SET_LOADING, false));
        },
        async [types.FETCH_CAL_WATER_TEMP]({commit}, deviceId) {

            axios.get(`/${deviceId}/waterTempCalibrationValue`, {
                params: {
                    'access_token': process.env.VUE_APP_ACCESS_TOKEN
                }
            })
                .then(response => {
                    commit(types.SET_CAL_WATER_TEMP, response.data.result)
                })
                .catch(err => {
                    commit(types.SET_ERROR, err);
                }).finally(() => commit(types.SET_LOADING, false));
        },
        async [types.SET_CAL_WATER_TEMP]({commit}, {deviceId, value}) {

            axios.post(`/${deviceId}/calWatTmpF?access_token=${process.env.VUE_APP_ACCESS_TOKEN}&args=${value}`, {

            })
                .then(() => {
                    store.dispatch(types.FETCH_WATER_TEMP, deviceId)
                })
                .catch(err => {
                  commit(types.SET_ERROR, err);
                }).finally(() => commit(types.SET_LOADING, false));
        },
        async [types.SET_CAL_AIR_HUM]({commit}, {deviceId, value}) {
          debugger
            axios.post(`/${deviceId}/calAirHumF?access_token=${process.env.VUE_APP_ACCESS_TOKEN}&args=${value}`, {

            })
                .then(() => {
                    store.dispatch(types.FETCH_AIR_HUM, deviceId)
                })
                .catch(err => {
                  commit(types.SET_ERROR, err);
                }).finally(() => commit(types.SET_LOADING, false));
        },
        async [types.SET_CAL_AIR_TEMP]({commit}, {deviceId, value}) {
            axios.post(`/${deviceId}/calAirTmpF?access_token=${process.env.VUE_APP_ACCESS_TOKEN}&args=${value}`, {

            })
                .then(() => {
                    store.dispatch(types.FETCH_AIR_TEMP, deviceId)
                })
                .catch(err => {
                    commit(types.SET_ERROR, err);
                }).finally(() => commit(types.SET_LOADING, false));
        }
    },
});

export default store;