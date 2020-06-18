//
// Created by artemiy on 18.06.2020.
//

#ifndef DRAFT_IMAGE_HPP
#define DRAFT_IMAGE_HPP

#include <cinttypes>


struct BMP_image_tag;

template<typename ImageTag>
class Image {
private:
    uint64_t height_;
    uint64_t width_;


public:

    struct Pixel {
        uint8_t red = 0;
        uint8_t green = 0;
        uint8_t blue = 0;
    };

    Image(const Image &other) = default;

    Image(Image &&other) noexcept = default;

    Image &operator=(const Image &other) = default;

    Image &operator=(Image &&other) noexcept = default;

    virtual ~Image() = default;

    virtual Pixel &operator[](const uint64_t t) = 0;

    virtual const Pixel &operator[](const uint64_t t) const = 0;

    inline uint64_t height() const noexcept { return height_; }

    inline uint64_t width() const noexcept { return width_; }

};

#endif //DRAFT_IMAGE_HPP
