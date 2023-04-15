#ifndef LAB_1_MYIMAGE_H
#define LAB_1_MYIMAGE_H

#include <fstream>
#include <iostream>
#include <utility>

#include "Pixel.h"


#pragma pack(push, 1) // exact fit - no padding
struct BMPHeader{
    // Bitmap File Header
    uint16_t  type;             // File identifier
    uint32_t  size;             // File size in bytes
    uint16_t  reserved1;        // Not used
    uint16_t  reserved2;        // Not used
    uint32_t  offset;           // Offset to image data in bytes from beginning of file (54 bytes)

    // DIB Header
    uint32_t  dib_header_size;  // DIB Header size in bytes (40 bytes)
    int32_t   width_px;         // Width of the image
    int32_t   height_px;        // Height of image
    uint16_t  num_planes;       // Number of color planes
    uint16_t  bits_per_pixel;   // Bits per pixel
    uint32_t  compression;      // Compression type
    uint32_t  image_size_bytes; // Image size in bytes
    int32_t   x_resolution_ppm; // Pixels per meter
    int32_t   y_resolution_ppm; // Pixels per meter
    uint32_t  num_colors;       // Number of colors
    uint32_t  important_colors; // Important colors
};
#pragma pack(pop)



class MyImage {
public:
    static MyImage* CreateBlank(int width, int height);
    static MyImage* LoadFromFile(const std::string& filepath);
    ~MyImage();

    void Save(const std::string& filename);

private:
    MyImage(int width, int height);

    // height and width in pixels
    int height_;
    int width_;
    // RGB is used (24 bits)
    static const int channels_ = 3;
    Pixel** matrix_;
    friend class Editor;
};


#endif //LAB_1_MYIMAGE_H
