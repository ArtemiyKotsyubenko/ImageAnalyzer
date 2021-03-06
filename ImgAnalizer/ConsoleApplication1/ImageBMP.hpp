//
// Created by artemiy on 18.06.2020.
//

#ifndef DRAFT_IMAGEBMP_HPP
#define DRAFT_IMAGEBMP_HPP

#include <iosfwd>
#include <vector>
#include <fstream>
#include "Image.hpp"


class ImageBMP : public Image {
private:

    struct BitMapFileHeader {
        uint16_t bf_type = 0;
        uint32_t bf_size = 0;
        //32 bits reserved
        uint16_t legacy_1 = 0;
        uint16_t legacy_2 = 0;
        uint32_t bf_of_bits = 0;
    } bmfh;

    struct BitMapInfoHeader {
        //WINAPY - weight 0f the struct
        uint32_t legacy = 0;
        uint32_t width = 0;
        uint32_t height = 0;
        uint16_t planes = 0;
        uint16_t bit_cnt = 0;
        uint32_t compression = 0;
        uint32_t img_size = 0;
        uint32_t X_pixels_per_meter = 0;
        uint32_t Y_pixels_per_meter = 0;
        uint32_t colors_used = 0;
        uint32_t colors_important = 0;

    } bmih;

    std::vector<std::vector<uint8_t>> img;

    //template<typename Stream>
    friend std::ifstream &operator>>(std::ifstream &strm, BitMapFileHeader &bmfh);

    //template<typename Strm>
    friend std::ifstream &operator>>(std::ifstream &strm, BitMapInfoHeader &bmih);

public:
    struct PixelBMP : public Pixel {
        uint8_t reserved;
    };

private:



    std::vector<PixelBMP> palette;

    struct proxy{
    private:
        const std::vector<PixelBMP>& palette_;
        const std::vector<uint8_t>& row_;
    public:
        proxy( const std::vector<PixelBMP>& palette, const std::vector<uint8_t>& row): palette_(palette), row_(row){}
        const PixelBMP& operator[](const uint64_t index) const {
            return palette_[row_[index]];
        }
    };

public:

    ImageBMP(std::ifstream &strm) {

        strm >> bmfh;
        strm >> bmih;

        if (bmih.colors_used == 0 || bmih.colors_used == 256) {
            palette.resize(256);
        } else if (bmih.colors_used == 4) {
            palette.resize(16);
        } else if (bmih.colors_used == 1) {
            palette.resize(2);
        }


        for (auto &it : palette) {
            it.blue = strm.get();
            it.green = strm.get();
            it.red = strm.get();
            it.reserved = strm.get();
        }

        strm.seekg(bmfh.bf_of_bits, std::ios::beg);

        img.resize(bmih.height);

        uint8_t extra_cells = (bmih.width % 4 == 0) ? 0 : 4 - (bmih.width % 4);

        for (auto &row: img) {
            row.resize(extra_cells + bmih.width);
        }

        for (int i = 0; i < bmih.height; ++i) {
            for (int j = 0; j < img[i].size(); ++j) {
                img[i][j] = strm.get();
            }
        }
    }

    inline uint64_t height() const noexcept override { return bmih.height; };

    inline uint64_t width() const noexcept override { return bmih.width; };

    //proxy operator[](const uint64_t index){ return proxy(palette, img[index]);}
    const proxy operator[](const uint64_t index) const { return proxy(palette, img[index]);}

};

std::ifstream &operator>>(std::ifstream &strm, ImageBMP::BitMapFileHeader &bmfh) {
    uint8_t temp;
    //read first 2 bytes(Must be == BM)
    for (int i = 0; i < 2; ++i) {
        bmfh.bf_type <<= 8u;
        strm >> temp;
        bmfh.bf_type |= temp;
    }

    //read size
    for (int i = 0; i < 4; ++i) {
        temp = strm.get();
        bmfh.bf_size |= static_cast<uint32_t>(temp) << (i * 8u);
    }

    //skip reserved null-bytes
    for (int i = 0; i < 4; ++i) {
        strm.get();
    }

    //read start
    for (int i = 0; i < 4; ++i) {
        temp = strm.get();
        bmfh.bf_of_bits |= static_cast<uint32_t>(temp) << (i * 8u);
    }
    return strm;
}

std::ifstream &operator>>(std::ifstream &strm, ImageBMP::BitMapInfoHeader &bmih) {
    uint8_t temp;

    //skip reserved null-bytes
    for (int i = 0; i < 4; ++i) {
        strm >> temp;
    }

    //read width
    for (int i = 0; i < 4; ++i) {
        temp = strm.get();
        bmih.width |= static_cast<uint32_t>(temp) << (i * 8u);
    }

    //read height
    for (int i = 0; i < 4; ++i) {
        temp = strm.get();
        bmih.height |= static_cast<uint32_t>(temp) << (i * 8u);
    }

    //read planes cnt
    for (int i = 0; i < 2; ++i) {
        temp = strm.get();
        bmih.planes |= static_cast<uint32_t>(temp) << (i * 8u);
    }

    //read bit_cnt per pixel
    for (int i = 0; i < 2; ++i) {
        temp = strm.get();
        bmih.bit_cnt |= static_cast<uint32_t>(temp) << (i * 8u);
    }

    //read compression
    for (int i = 0; i < 4; ++i) {
        temp = strm.get();
        bmih.compression |= static_cast<uint32_t>(temp) << (i * 8u);
    }

    //read img size
    for (int i = 0; i < 4; ++i) {
        temp = strm.get();
        bmih.img_size |= static_cast<uint32_t>(temp) << (i * 8u);
    }

    //read pixels per meter on X
    for (int i = 0; i < 4; ++i) {
        temp = strm.get();
        bmih.X_pixels_per_meter |= static_cast<uint32_t>(temp) << (i * 8u);
    }
    //read pixels per meter on Y
    for (int i = 0; i < 4; ++i) {
        temp = strm.get();
        bmih.Y_pixels_per_meter |= static_cast<uint32_t>(temp) << (i * 8u);
    }

    //read used colors cnt
    for (int i = 0; i < 4; ++i) {
        temp = strm.get();
        bmih.colors_used |= static_cast<uint32_t>(temp) << (i * 8u);
    }

    //read used colors important
    for (int i = 0; i < 4; ++i) {
        temp = strm.get();
        bmih.colors_important |= static_cast<uint32_t>(temp) << (i * 8u);
    }
    return strm;
}


#endif //DRAFT_IMAGEBMP_HPP
