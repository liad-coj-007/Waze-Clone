export class Point {
    #point_marker;
    #msg;
    constructor(point_marker,msg){
        this.#point_marker = point_marker;
        this.#msg = msg;
    }

    getPos(){
        const ll = this.#point_marker.getLatLng();
        return { lat: ll.lat, lon: ll.lng }; 
    }

    Popup(){
        this.#point_marker.bindPopup(this.#msg).openPopup();
    }
}