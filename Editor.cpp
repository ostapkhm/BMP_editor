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
