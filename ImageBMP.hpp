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
    WORD bfType;//16
    DWORD bfSize;//32
    WORD bfReserved1;//16
    WORD bfReserved2;//16
    DWORD bfOffBits;//32
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

//************************

typedef struct tagBITMAPINFOHEADER {
    DWORD biSize;// 32
    LONG biWidth;//long//32
    LONG biHeight;//long//32
    WORD biPlanes;//16
    WORD biBitCount;//16
    DWORD biCompression;//32
    DWORD biSizeImage;//32
    LONG biXPelsPerMeter;//long//32
    LONG biYPelsPerMeter;//long//32
    DWORD biClrUsed;//32
    DWORD biClrImportant;//32
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
        unsigned char bf_type[2];//format
        uint32_t bf_size;//
        //32 bits reserved
        uint32_t bf_of_bits;

//        template<typename strm>
//        friend strm& operator<<(strm&, const BitMapFileHeader& bmfh);
    };

    struct BitMapInfoHeader {
        uint32_t width;
        uint32_t height;
        uint16_t planes;
        uint16_t bit_cnt;
        uint32_t compression;
        uint32_t img_size;
        uint32_t X_pixels_per_meter;
        uint32_t Y_pixels_per_meter;
        uint32_t colors_used;
        uint32_t colors_important;

//        template<typename Strm>
//        friend Strm& operator<<(Strm&, const BitMapInfoHeader& bmih);
    };

public:
    struct PixelBMP : public Pixel {
        uint8_t reserved;
    };


};


#endif //DRAFT_IMAGEBMP_HPP
