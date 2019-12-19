<template>
    <div class="dashboard" v-if="!loading">
        <div class="gauges">
            <GaugeComponent v-for="data in getAllData"
                            :key="data.title"
                            :title="data.title"
                            :value="data.value"
                            :calibrationValue="data.calibrationValue"
                            :calibrationFunc="data.calibrationFunc"
            />
        </div>
        <mapbox
                :access-token="mapboxToken"
                :map-options="{
        style: 'mapbox://styles/mapbox/light-v9',
        center: [11.1407, 59.137891],
        zoom: 12,
      }"
                :geolocate-control="{
                show: true,
                position: 'top-left',
        }"
                :scale-control="{
        show: true,
        position: 'top-left',
        }"
                :fullscreen-control="{
        show: true,
        position: 'top-left',
}"
                @map-load="loaded"
        />
    </div>
</template>

<script>
    import GaugeComponent from './GaugeComponent.vue'
    import {useGetters, useActions} from "@u3u/vue-hooks";
    import types from "../types";
    import {onMounted} from "@vue/composition-api";
    import Mapbox from 'mapbox-gl-vue'


    export default {
        name: 'DashboardComponent',
        components: {
            GaugeComponent,
            Mapbox
        },
        setup() {

            const {loading, error, getAllData, currentWaterTemp} = useGetters(['loading', 'error', 'getAllData', 'currentWaterTemp']);
            const {FETCH_AIR_TEMP, FETCH_AIR_HUM, FETCH_WATER_TEMP} = useActions([types.FETCH_AIR_TEMP, types.FETCH_AIR_HUM, types.FETCH_WATER_TEMP]);

            const fetch = () => {
                FETCH_AIR_TEMP({
                    deviceId: 'lazy-snitch'
                });
            };

            const loaded = (map) => {
                map.addLayer({
                    id: 'points',
                    type: 'symbol',
                    source: {
                        type: 'geojson',
                        data: {
                            type: 'FeatureCollection',
                            features: [
                                {
                                    type: 'Feature',
                                    geometry: {
                                        type: 'Point',
                                        coordinates: [11.140269, 59.137781]
                                    },
                                    properties: {
                                        title: currentWaterTemp.value
                                    },
                                }
                            ],
                        },
                    },
                    layout: {
                        'icon-image': '{icon}-15',
                        'text-field': '{title}',
                        'text-font': ['Open Sans Semibold', 'Arial Unicode MS Bold'],
                        'text-offset': [0, 0.6],
                        'text-anchor': 'top',
                    },
                })
            }

            const mapboxToken = process.env.VUE_APP_MAPBOX_ACCESS_TOKEN;

            onMounted(() => {
                    FETCH_AIR_TEMP(process.env.VUE_APP_DEVICE_ID);
                    FETCH_AIR_HUM(process.env.VUE_APP_DEVICE_ID);
                    FETCH_WATER_TEMP(process.env.VUE_APP_DEVICE_ID);
                }
            );

            return {
                loading,
                error,
                getAllData,
                fetch,
                mapboxToken,
                loaded
            }
        }
    }
</script>

<style>

    #map {
        width: 80%;
        height: 300px;
        margin: auto;
    }

    .gauges {
        font-family: 'Open Sans', sans-serif;
        width: 70%;
        height: 100px;
        display: flex;
        flex-direction: row;
        justify-content: space-evenly;
        flex-wrap: wrap;
        margin: 15% auto;
    }
</style>