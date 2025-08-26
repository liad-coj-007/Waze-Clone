var map = L.map('map').setView([51.505, -0.09], 13);

var osm = L.tileLayer('https://tile.openstreetmap.org/{z}/{x}/{y}.png', {
    maxZoom: 19,
    attribution: '&copy; <a href="http://www.openstreetmap.org/copyright">OpenStreetMap</a>'
}).addTo(map);

osm.addTo(map);

var marker = L.marker([32.07, 34.79]).addTo(map);
marker.bindPopup("vertex").openPopup();