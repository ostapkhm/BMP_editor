#include "MyImage.h"

#include <utility>

MyImage::MyImage(int width, int height, std::string filename): height_(height), width_(width), filename_(std::move(filename)) {
    // Create 2d pixel matrix of image size
    matrix_ = new Pixel*[height_];
    for(int i = 0; i < height_; i++){
        matrix_[i] = new Pixel[width_];
    }

    CreateFromMatrix();
}

MyImage::MyImage(std::string filepath) {
    filename_ = std::move(filepath);

    std::ifstream file(filename_, std::ios::binary);
    if(!file.is_open()){
        std::cerr << "File could not be opened!" << std::endl;
        exit(1);
    }

    const int file_header_size = 14;
    const int information_header_size = 40;

    unsigned char file_header[file_header_size];
    file.read(reinterpret_cast<char*>(file_header), file_header_size);

    unsigned char information_header[information_header_size];
    file.read(reinterpret_cast<char*>(information_header), information_header_size);

    // check whether it's a BMP file
    if((file_header[0] != 'B') || (file_header[1] != 'M')){
        std::cerr << "Provided file is not a bmp file!" << std::endl;
        return;
    }

    // extract important parameters
    width_ = BytesToInt(information_header, 4);
    height_ = BytesToInt(information_header, 8);
    int padding = (4 - (channels_ * width_) % 4) % 4;

    // Create 2d pixel matrix of image size
    matrix_ = new Pixel*[height_];
    for(int i = 0; i < height_; i++){
        matrix_[i] = new Pixel[width_];
    }

    unsigned char color[channels_];
    for(int y = 0; y < height_; y++){
        for(int x = 0; x < width_; x++){
            file.read(reinterpret_cast<char*>(color), channels_);
            matrix_[y][x].set(color[2], color[1], color[1]);
        }
        file.ignore(padding);
    }

    file.close();
}


void MyImage::CreateFromMatrix() {
    const int file_header_size = 14;
    const int information_header_size = 40;

    unsigned char file_header[file_header_size];
    unsigned char information_header[information_header_size];
    int padding = (4 - (channels_ * width_) % 4) % 4;
    int file_size = file_header_size + information_header_size + width_ * height_ * 3 + padding * height_;

    FillHeaders(file_header, information_header, file_size);

    std::ofstream file(filename_, std::ios::binary);

    if(!file.is_open()){
        std::cerr << "File could not be created!" << std::endl;
        exit(1);
    }

    file.write(reinterpret_cast<char*>(file_header), file_header_size);
    file.write(reinterpret_cast<char*>(information_header), information_header_size);

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

MyImage::~MyImage() {
    for(int i = 0; i < height_; i++){
        delete matrix_[i];
    }
    delete matrix_;
}

int MyImage::BytesToInt(const unsigned char *buffer, int idx) {
    // transform 4 bytes from buffer to int starting with idx position

    return int(buffer[idx + 3] << 24 |
               buffer[idx + 2] << 16 |
               buffer[idx + 1] << 8 |
               buffer[idx]);
}

void MyImage::IntToBuffer(unsigned char *buffer, int idx, int value) {
    // transform 4 bytes from buffer to int starting with idx position
    buffer[idx] = value;
    buffer[idx + 1] = value >> 8;
    buffer[idx + 2] = value >> 16;
    buffer[idx + 3] = value >> 24;
}

void MyImage::FillHeaders(unsigned char *file_header, unsigned char *information_header, int file_size) {
    const int file_header_size = 14;
    const int information_header_size = 40;

    // File type
    file_header[0] = 'B';
    file_header[1] = 'M';

    // File size
    IntToBuffer(file_header, 2, file_size);

    // Reserved
    file_header[6] = 0;
    file_header[7] = 0;
    file_header[8] = 0;
    file_header[9] = 0;

    //Pixel data offset
    file_header[10] = file_header_size + information_header_size;
    file_header[11] = 0;
    file_header[12] = 0;
    file_header[13] = 0;

    //Header size
    information_header[0] = information_header_size;
    information_header[1] = 0;
    information_header[2] = 0;
    information_header[3] = 0;

    //MyImage width
    IntToBuffer(information_header, 4, width_);

    //MyImage height
    IntToBuffer(information_header, 8, height_);

    //Planes
    information_header[12] = 1;
    information_header[13] = 0;

    //Bits per pixel (RGB)
    information_header[14] = channels_ * 8;
    information_header[15] = 0;

    //Compression (no compression)
    IntToBuffer(information_header, 16, 0);

    //MyImage size (no compression)
    IntToBuffer(information_header, 20, 0);

    //X pixels per meter (not specified)
    IntToBuffer(information_header, 24, 0);

    //Y pixels per meter (not specified)
    IntToBuffer(information_header, 28, 0);

    //Total colors (color palette not used)
    IntToBuffer(information_header, 32, 0);

    //Important colors (generally ignored)
    IntToBuffer(information_header, 36, 0);
}


