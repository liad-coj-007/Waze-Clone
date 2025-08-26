export class Point {
    #point_marker;
    #msg;
    constructor(point_marker,msg){
        this.#point_marker = point_marker;
        this.#msg = msg;
    }

    getPos(){
        return this.#point_marker.getLating;
    }

    Popup(){
        this.#point_marker.bindPopup(this.#msg).openPopup();
    }
}