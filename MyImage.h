#ifndef LAB_1_MYIMAGE_H
#define LAB_1_MYIMAGE_H

#include <fstream>
#include <iostream>
#include <utility>

#include "Pixel.h"

class MyImage {
public:
    MyImage(int width, int height, std::string filename);
    explicit MyImage(std::string filepath);
    ~MyImage();


private:
    int BytesToInt(const unsigned char *buffer, int idx);
    void IntToBuffer(unsigned char *buffer, int idx, int value);
    void FillHeaders(unsigned char* file_header, unsigned char* information_header, int file_size);

    void CreateFromMatrix();


    // height and width in pixels
    int height_;
    int width_;

    // RGB is used (24 bits)
    int channels_ = 3;

    Pixel** matrix_;
    std::string filename_;

    friend class Editor;
};


#endif //LAB_1_MYIMAGE_H
