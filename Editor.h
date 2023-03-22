#ifndef LAB_1_EDITOR_H
#define LAB_1_EDITOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <utility>

#include "Pixel.h"

class Editor {
public:
    Editor(std::string filename);
    ~Editor();

private:
    int BytesToInt(const unsigned char *buffer, int idx);
    void IntToBuffer(unsigned char *buffer, int idx, int value);

    std::string CreateFromMatrix(Pixel** matrix, int height, int width);
    void FillHeaders(unsigned char* file_header, unsigned char* information_header, int file_size,
                     int height, int width);

    // height and width in pixels
    int image_width_;
    int image_height_;
    int file_size_;
    int padding_;

    // RGB is used (24 bits)
    int channels_ = 3;

    std::string filename_;
    Pixel** matrix_;
};


#endif //LAB_1_EDITOR_H
