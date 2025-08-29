import {Point } from "./Point.js";
import { Road } from "./Road.js";

//colors 
// ===============================================================
var redIcon = L.icon({
  iconUrl: 'https://cdn.jsdelivr.net/gh/pointhi/leaflet-color-markers@master/img/marker-icon-red.png',
  shadowUrl: 'https://unpkg.com/leaflet@1.9.4/dist/images/marker-shadow.png',
  iconSize: [25, 41],
  iconAnchor: [12, 41],
  popupAnchor: [1, -34],
  shadowSize: [41, 41]
});

var greenIcon = L.icon({
  iconUrl: 'https://cdn.jsdelivr.net/gh/pointhi/leaflet-color-markers@master/img/marker-icon-green.png',
  shadowUrl: 'https://unpkg.com/leaflet@1.9.4/dist/images/marker-shadow.png',
  iconSize: [25, 41],
  iconAnchor: [12, 41],
  popupAnchor: [1, -34],
  shadowSize: [41, 41]
});
// ========================================================

var map_pos = [32.07, 34.79];

var map = L.map('map').setView(map_pos, 13);


var osm = L.tileLayer('https://tile.openstreetmap.org/{z}/{x}/{y}.png', {
    maxZoom: 19,
    attribution: '&copy; <a href="http://www.openstreetmap.org/copyright">OpenStreetMap</a>'
}).addTo(map);

osm.addTo(map);

var start_point = new Point(L.marker([32.07, 34.79], { draggable: true,icon: greenIcon}).addTo(map),"start");
start_point.Popup();
var end_point = new Point(L.marker([31.9, 34.79], { draggable: true,icon: redIcon}).addTo(map),"finish");
end_point.Popup();

const run_button = document.getElementById("run");
run_button.addEventListener("click",find_path);

var road = new Road(map);


/**
 * @brief draw the road
 * to the user
 * @param {*} res 
 * @returns 
 */
function buildRoad(res){
  if(!res.success){
    console.error("the road is not exist!");
    return;
  }

  road.BuildRoad(res.road);

}


/**
 * find the path 
 * for the user
 * @param {*} event 
 */
async function find_path(event) {
  event.preventDefault();

  const data = {
    start_point: {
      lat: start_point.getPos().lat,
      lon: start_point.getPos().lon
    },
    end_point: {
      lat: end_point.getPos().lat,
      lon: end_point.getPos().lon
    }
  };

  try {
    await fetch('http://localhost:3000/save', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify(data)
    });
    console.log('Saved to server');

    const res = await fetch('/run-binary', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify(data)
    });

    const result = await res.json();
    buildRoad(result);
  } catch (err) {
    console.error(err);
  }
}


