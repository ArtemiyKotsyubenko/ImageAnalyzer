//
// Created by artemiy on 18.06.2020.
//

#ifndef DRAFT_IMAGE_HPP
#define DRAFT_IMAGE_HPP

#include <cinttypes>


struct BMP_image_tag;

//template<typename ImageTag>
class Image {
private:
    //uint64_t height_ = 0;
    //uint64_t width_ = 0;


public:


    struct Pixel {
        uint8_t red = 0;
        uint8_t green = 0;
        uint8_t blue = 0;
    };

    Image() = default;

    Image(const Image &other) = default;

    Image(Image &&other) noexcept = default;

    Image &operator=(const Image &other) = default;

    Image &operator=(Image &&other) noexcept = default;

    virtual ~Image() = default;

    static inline double count_brightness(const Pixel &pixel) {
        return 0.2126 * pixel.red + 0.7152 * pixel.green + 0.0722 * pixel.blue;
    }


    virtual inline uint64_t height() const noexcept =0;

    virtual inline uint64_t width() const noexcept = 0;

};

#endif //DRAFT_IMAGE_HPP
