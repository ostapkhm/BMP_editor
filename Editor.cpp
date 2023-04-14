#include "Editor.h"


void Editor::PutPixel(Point point, Pixel pixel, int thickness) {
    // need to center image
    int x_offset = image_->width_ / 2 ;
    int y_offset = image_->height_ / 2;

    // thickness
    for(int y = point.y - thickness; y <= point.y + thickness; y++){
        for(int x = point.x - thickness; x <= point.x + thickness; x++){
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
    if(std::abs(p2.y - p1.y) < std::abs(p2.x - p1.x)){
        if(p1.x > p2.x){
            DrawLineLowRandom(p2, p1, thickness);
        }
        else{
            DrawLineLowRandom(p1, p2, thickness);
        }
    }
    else{
        if(p1.y > p2.y){
            DrawLineHighRandom(p2, p1, thickness);
        }
        else{
            DrawLineHighRandom(p1, p2, thickness);
        }
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

    unsigned char red;
    unsigned char green;
    unsigned char blue;

    for(int y = p1.y; y <= p2.y; y++){
        if(rand() % 255 > 100){
            //change color
            red = rand() % 255;
            green = rand() % 255;
            blue = rand() % 255;
        }

        PutPixel({x, y}, {red, green, blue}, thickness);
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

    unsigned char red;
    unsigned char green;
    unsigned char blue;

    for(int x = p1.x; x <= p2.x; x++){
        if(rand() % 255 > 100){
            //change color
            red = rand() % 255;
            green = rand() % 255;
            blue = rand() % 255;
        }

        PutPixel({x, y}, {red, green, blue}, thickness);
        if(delta > 0){
            y += y_sign;
            delta += 2 * (dy - dx);
        }
        else{
            delta += 2 * dy;
        }
    }
}
