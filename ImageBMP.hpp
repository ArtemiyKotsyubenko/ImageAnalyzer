//
// Created by artemiy on 18.06.2020.
//

#ifndef DRAFT_IMAGEBMP_HPP
#define DRAFT_IMAGEBMP_HPP

#include "Image.hpp"
//typedef uint32_t DWORD;   // DWORD = unsigned 32 bit value
//typedef uint16_t WORD;    // WORD = unsigned 16 bit value
//typedef uint8_t BYTE;     // BYTE = unsigned 8 bit value
//typedef long LONG;
using DWORD = uint32_t;
using WORD = uint16_t;
using BYTE = uint8_t;
using LONG = long;

typedef struct tagBITMAPFILEHEADER {
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

//************************

typedef struct tagBITMAPINFOHEADER {
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;


typedef struct tagRGBQUAD {
    BYTE rgbBlue;
    BYTE rgbGreen;
    BYTE rgbRed;
    BYTE rgbReserved;
} RGBQUAD;

class ImageBMP : public Image {
private:
    struct BitMapFileHeader{
        char bf_type[2];
        uint32_t bf_size;
        //two bytes reserved
        uint32_t bf_of_bits;
    };
    struct BitMapInfoHeader {
        uint32_t width;
        uint32_t height;
        uint8_t planes;
        uint8_t bit_cnt;
        uint8_t compression;
        uint32_t img_size;
        uint32_t X_pixels_per_meter;
        uint32_t Y_pixels_per_meter;
        uint32_t colors_used;
        uint32_t colors_important;

    };

public:
    struct PixelBMP : public Pixel {
        uint8_t reserved;
    };


};

#endif //DRAFT_IMAGEBMP_HPP
