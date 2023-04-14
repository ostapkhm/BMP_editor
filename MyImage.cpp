#include "MyImage.h"

#include <utility>


MyImage::MyImage(int width, int height): height_(height), width_(width) {
    // Create 2d pixel matrix of image size
    matrix_ = new Pixel*[height_];
    for(int i = 0; i < height_; i++){
        matrix_[i] = new Pixel[width_];
    }
}

MyImage *MyImage::CreateBlank(int width, int height) {
    if(width > 0 && height > 0){
        return new MyImage(width, height);
    }
    return nullptr;
}

MyImage *MyImage::LoadFromFile(const std::string &filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if(!file.is_open()){
        std::cerr << "File could not be opened!" << std::endl;
        return nullptr;
    }

    BMPHeader header { };
    const int file_header_size = 54;

    file.read(reinterpret_cast<char*>(&header), file_header_size);

    // Check whether it's a BMP file
    if(header.type != 0x4d42){
        std::cerr << "Provided file is not a bmp file!" << std::endl;
        file.close();
        return nullptr;
    }

    // Check whether this file has only 3 channels (RGB)
    if(header.bits_per_pixel != channels_ * 8){
        std::cerr << "Provided file doesn't have 3 channels" << std::endl;
        file.close();
        return nullptr;
    }

    // Extract important parameters
    int width = header.width_px;
    int height = header.height_px;
    int padding = (4 - (channels_ * width) % 4) % 4;

    MyImage* image = new MyImage(width, height);

    unsigned char color[channels_];
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            file.read(reinterpret_cast<char*>(color), channels_);
            image->matrix_[y][x].set(color[2], color[1], color[0]);
        }
        file.ignore(padding);
    }
    file.close();
    return image;
}

MyImage::~MyImage() {
    for(int i = 0; i < height_; i++){
        delete matrix_[i];
    }
    delete[] matrix_;
}

void MyImage::Save(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);

    if(!file.is_open()){
        std::cerr << "File could not be created!" << std::endl;
        exit(1);
    }

    const int bitmap_header_size = 14;
    const int dib_header_size = 40;
    int padding = (4 - (channels_ * width_) % 4) % 4;
    int image_size = width_ * height_ * channels_ + padding * height_;
    int file_size = bitmap_header_size + dib_header_size + image_size;

    BMPHeader header = {0x4d42, static_cast<uint32_t>(file_size), 0, 0,
                        bitmap_header_size + dib_header_size, dib_header_size,
                        width_, height_, 0, static_cast<uint16_t>(channels_ * 8),
                        0, static_cast<uint32_t>(image_size), 0, 0, 0, 0 };

    file.write(reinterpret_cast<const char*>(&header), sizeof(header));

    unsigned char bmp_pad[3] = {0, 0, 0};
    unsigned char color[channels_];
    for(int y = 0; y < height_; y++){
        for(int x = 0; x < width_; x++){
            color[2] = matrix_[y][x].red_;
            color[1] = matrix_[y][x].green_;
            color[0] = matrix_[y][x].blue_;

            file.write(reinterpret_cast<char*>(color), 3);
        }
        file.write(reinterpret_cast<char*>(bmp_pad), padding);
    }

    file.close();
}
