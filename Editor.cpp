#include "Editor.h"


void Editor::PutPixel(Point point, Pixel pixel) {
    image_->matrix_[point.y][point.x] = pixel;
}

void Editor::Save() {
    image_->CreateFromMatrix();
}
