#include "Editor.h"


void Editor::PutPixel(Point point, Pixel pixel, int thickness) {
    // need to center the image
    int x_offset = image_->width_ / 2 ;
    int y_offset = image_->height_ / 2;

    // thickness
    for(int y = point.y - thickness; y <= point.y + thickness; y++){
        for(int x = point.x - thickness; x <= point.x + thickness; x++){
            if(y + y_offset < 0 || y + y_offset >= image_->height_){
                throw std::invalid_argument("Y-coordinate exceeds available range!");
            }
            if(x + x_offset < 0 || x + x_offset >= image_->width_){
                throw std::invalid_argument("X-coordinate exceeds available range!");
            }

            image_->matrix_[y + y_offset][x + x_offset] = pixel;
        }
    }
}

void Editor::Save(const std::string& filename) {
    image_->Save(filename);
}

void Editor::DrawAxis() {
    for(int i = 0; i < image_->height_; i++){
        image_->matrix_[i][image_->width_ / 2] = Pixel(0, 0, 0);
    }

    for(int i = 0; i < image_->width_; i++){
        image_->matrix_[image_->height_ / 2][i] = Pixel(0, 0, 0);
    }
}

void Editor::DrawLine(Point p1, Point p2, Pixel pixel, int thickness) {
    try{
        if(std::abs(p2.y - p1.y) < std::abs(p2.x - p1.x)){
            if(p1.x > p2.x){
                DrawLineLow(p2, p1, thickness, pixel);
            }
            else{
                DrawLineLow(p1, p2, thickness, pixel);
            }
        }
        else{
            if(p1.y > p2.y){
                DrawLineHigh(p2, p1, thickness, pixel);
            }
            else{
                DrawLineHigh(p1, p2, thickness, pixel);
            }
        }
    }
    catch(std::invalid_argument& exp){
        std::cerr << exp.what() << std::endl;
    }
}

void Editor::DrawLineLow(Point p1, Point p2, int thickness, Pixel pixel) {
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;

    int y_sign = 1;
    if(dy < 0){
        y_sign = -1;
        dy = -dy;
    }

    int delta = 2 * dy - dx;
    int y = p1.y;

    for(int x = p1.x; x <= p2.x; x++){
        PutPixel({x, y}, pixel, thickness);
        if(delta > 0){
            y += y_sign;
            delta += 2 * (dy - dx);
        }
        else{
            delta += 2 * dy;
        }
    }
}

void Editor::DrawLineHigh(Point p1, Point p2, int thickness, Pixel pixel) {
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;

    int x_sign = 1;
    if(dx < 0){
        x_sign = -1;
        dx = -dx;
    }

    int delta = 2 * dy - dx;
    int x = p1.x;

    for(int y = p1.y; y <= p2.y; y++){
        PutPixel({x, y}, pixel, thickness);
        if(delta > 0){
            x += x_sign;
            delta += 2 * (dx - dy);
        }
        else{
            delta += 2 * dx;
        }
    }
}

void Editor::DrawRandomColouredLine(Point p1, Point p2, int thickness) {
    try {
        if (std::abs(p2.y - p1.y) < std::abs(p2.x - p1.x)) {
            if (p1.x > p2.x) {
                DrawLineLowRandom(p2, p1, thickness);
            } else {
                DrawLineLowRandom(p1, p2, thickness);
            }
        } else {
            if (p1.y > p2.y) {
                DrawLineHighRandom(p2, p1, thickness);
            } else {
                DrawLineHighRandom(p1, p2, thickness);
            }
        }
    }
    catch(std::invalid_argument& exp){
        std::cerr << exp.what() << std::endl;
    }
}

void Editor::DrawLineHighRandom(Point p1, Point p2, int thickness) {
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;

    int x_sign = 1;
    if(dx < 0){
        x_sign = -1;
        dx = -dx;
    }

    int delta = 2 * dy - dx;
    int x = p1.x;

    for(int y = p1.y; y <= p2.y; y++){
        PutPixel({x, y}, GetRandomPixel(), thickness);
        if(delta > 0){
            x += x_sign;
            delta += 2 * (dx - dy);
        }
        else{
            delta += 2 * dx;
        }
    }
}

void Editor::DrawLineLowRandom(Point p1, Point p2, int thickness) {
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;

    int y_sign = 1;
    if(dy < 0){
        y_sign = -1;
        dy = -dy;
    }

    int delta = 2 * dy - dx;
    int y = p1.y;

    for(int x = p1.x; x <= p2.x; x++){
        PutPixel({x, y}, GetRandomPixel(), thickness);
        if(delta > 0){
            y += y_sign;
            delta += 2 * (dy - dx);
        }
        else{
            delta += 2 * dy;
        }
    }
}

Pixel Editor::GetRandomPixel() {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    std::uniform_int_distribution<int> int_distro(0, 255);


    // change color
    red = int_distro(random_engine_);
    green = int_distro(random_engine_);
    blue = int_distro(random_engine_);

    return {red, green, blue};
}
