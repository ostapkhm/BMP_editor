#include "Editor.h"


void Editor::PutPixel(Point point, Pixel pixel) {
    // need center image
    int x_offset = image_->width_ / 2 ;
    int y_offset = image_->height_ / 2;

    image_->matrix_[point.y + y_offset][point.x + x_offset] = pixel;
}

void Editor::Save() {
    image_->CreateFromMatrix();
}

void Editor::DrawAxis() {
    for(int i = 0; i < image_->height_; i++){
        image_->matrix_[i][image_->width_ / 2] = Pixel(0, 0, 0);
    }

    for(int i = 0; i < image_->width_; i++){
        image_->matrix_[image_->height_ / 2][i] = Pixel(0, 0, 0);
    }
}

void Editor::DrawLine(Point p1, Point p2) {
    if(std::abs(p2.y - p1.y) < std::abs(p2.x - p1.x)){
        if(p1.x > p2.x){
            DrawLine_(p2, p1);
        }
        else{
            DrawLine_(p1, p2);
        }
    }
    else{
        if(p1.y > p2.y){
            DrawLine_(p2, p1);
        }
        else{
            DrawLine_(p1, p2);
        }
    }

}

void Editor::DrawLine_(Point p1, Point p2) {
    // Assume that p1 is on the left upper conner compared to p2

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
        PutPixel({x, y}, {255,0,0});
        if(delta > 0){
            y += y_sign;
            delta += 2 * (dy - dx);
        }
        else{
            delta += 2 * dy;
        }
    }
}
