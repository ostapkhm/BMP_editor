#include "Editor.h"


int Editor::BytesToInt(const unsigned char *buffer, int idx) {
    // transform 4 bytes from buffer to int starting with idx position

    return int(buffer[idx + 3] << 24 |
               buffer[idx + 2] << 16 |
               buffer[idx + 1] << 8 |
               buffer[idx]);
}

void Editor::IntToBuffer(unsigned char *buffer, int idx, int value) {
    // transform 4 bytes from buffer to int starting with idx position
     buffer[idx] = value;
     buffer[idx + 1] = value >> 8;
     buffer[idx + 2] = value >> 16;
     buffer[idx + 3] = value >> 24;
}

Editor::Editor(std::string filename):filename_(std::move(filename)) {
    std::ifstream image(filename_, std::ios::binary);

    if(!image.is_open()){
        std::cerr << "File could not be opened!" << std::endl;
        exit(1);
    }

    const int file_header_size = 14;
    const int information_header_size = 40;

    unsigned char file_header[file_header_size];
    image.read(reinterpret_cast<char*>(file_header), file_header_size);

    unsigned char information_header[information_header_size];
    image.read(reinterpret_cast<char*>(information_header), information_header_size);

    // check whether it's a BMP file
    if((file_header[0] != 'B') || (file_header[1] != 'M')){
        std::cerr << "Provided file is not a bmp file!" << std::endl;
        return;
    }

    // extract important parameters
    file_size_ = BytesToInt(file_header, 2);
    image_width_ = BytesToInt(information_header, 4);
    image_height_ = BytesToInt(information_header, 8);
    padding_ = (4 - (channels_ * image_width_) % 4) % 4;

    // creating 2d pixel matrix
    matrix_ = new Pixel*[image_height_];
    for(int i = 0; i < image_height_; i++){
        matrix_[i] = new Pixel[image_width_];
    }

    unsigned char color[channels_];
    for(int y = 0; y < image_height_; y++){
        for(int x = 0; x < image_width_; x++){
            image.read(reinterpret_cast<char*>(color), channels_);
            matrix_[y][x].set(color[2], color[1], color[1]);
        }
        image.ignore(padding_);
    }

    image.close();
    CreateFromMatrix(matrix_, image_height_, image_width_);
}

Editor::~Editor() {
    for(int i = 0; i < image_height_; i++){
        delete matrix_[i];
    }
    delete matrix_;
}

void Editor::FillHeaders(unsigned char* file_header, unsigned char* information_header, int file_size,
                         int height, int width) {

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

    //Image width
    IntToBuffer(information_header, 4, width);

    //Image height
    IntToBuffer(information_header, 8, height);

    //Planes
    information_header[12] = 1;
    information_header[13] = 0;

    //Bits per pixel (RGB)
    information_header[14] = channels_ * 8;
    information_header[15] = 0;

    //Compression (no compression)
    IntToBuffer(information_header, 16, 0);

    //Image size (no compression)
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

std::string Editor::CreateFromMatrix(Pixel** matrix, int height, int width) {
    const int file_header_size = 14;
    const int information_header_size = 40;

    unsigned char file_header[file_header_size];
    unsigned char information_header[information_header_size];
    int padding = (4 - (channels_ * width) % 4) % 4;
    int file_size = file_header_size + information_header_size + width * height * 3 + padding * height;

    FillHeaders(file_header, information_header, file_size, height, width);

    std::string new_filename = "new_" + filename_;
    std::ofstream new_image(new_filename, std::ios::binary);

    new_image.write(reinterpret_cast<char*>(file_header), file_header_size);
    new_image.write(reinterpret_cast<char*>(information_header), information_header_size);

    unsigned char bmp_pad[3] = {0, 0, 0};
    unsigned char color[channels_];
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            color[2] = matrix[y][x].red_;
            color[1] = matrix[y][x].blue_;
            color[0] = matrix[y][x].green_;

            new_image.write(reinterpret_cast<char*>(color), 3);
        }
        new_image.write(reinterpret_cast<char*>(bmp_pad), padding);
    }
    new_image.close();
    return new_filename;
}
