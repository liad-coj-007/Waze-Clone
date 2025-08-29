export class Road{
    #road;
    #map
    constructor(map){
        this.#road = null;
        this.#map = map;
    }

    BuildRoad(new_road){
        if(this.#road){
            this.#road.remove();
        }

        this.#road = L.polyline(new_road ,{color: 'red',
        weight: 5,
        opacity: 0.8,
        lineJoin: 'round'
        }).addTo(this.#map);
    }


}