#pragma once

class Box{
public:

    /**
     * @brief constract box
    */
    Box(const double& low_lat,const double& low_lon,
    const double& hight_lat,const double& high_lon);

    /**
     * @brief get the area of 
     * the box
    */
    double getArea()const;

    /**
     * @brief union the box to one
     * @param other - the other box 
     * we union with
    */
    void Union(const Box& other);

    /**
     * @brief check if the point is on box
    */
    bool isInBox(const double& lat,const double lon)const;
private:
    double low_lat,low_lon;
    double high_lat,high_lon;
};