#ifndef LAB_1_PIXEL_H
#define LAB_1_PIXEL_H

#include <string>

struct Point{
    Point(int x_, int y_) {
        x = x_;
        y = y_;
    }

    int x;
    int y;
};

class Pixel {
public:
    Pixel()=default;
    Pixel(unsigned char red, unsigned char green, unsigned char blue): red_(red), green_(green), blue_(blue) {  }

    void set(unsigned char red, unsigned char green, unsigned char blue){
        red_ = red;
        green_ = green;
        blue_ = blue;
    }

    std::string ToString(){
        return "R:" + std::to_string(red_) + " G:" + std::to_string(green_) + " B:" + std::to_string(blue_);
    }

    unsigned char red_;
    unsigned char green_;
    unsigned char blue_;
};


#endif //LAB_1_PIXEL_H
