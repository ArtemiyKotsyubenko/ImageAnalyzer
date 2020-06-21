//
// Created by artemiy on 19.06.2020.
//

#ifndef DRAFT_IMG_ANALYZER_HPP
#define DRAFT_IMG_ANALYZER_HPP

#include "ImageBMP.hpp"
#include <vector>
#include <string>

// кривая Гаусса - нормальное изображение
// высокий пик в центре - малоконтрастное изображение
// высокий пик слева - тёмное изображение
// высокий пик справа - засвеченное изображение
// два пика по краям - контрастное изображение


#include <iostream>
#include <cmath>

struct ImgAnalyser {
private:

public:
    std::string operator()(const ImageBMP &img);
};

std::string Analyser(const ImageBMP &img) {
    std::vector<uint64_t> histogram(256, 0);
    uint32_t cnt = 0;

    //build histogram
    for (int i = 0; i < img.height(); ++i) {
        for (int j = 0; j < img.width(); ++j) {
            //std::cout << (int)img[i][j].red << ' '<< (int)img[i][j].green <<' '<< (int)img[i][j].blue << '\n';
            histogram[ImageBMP::count_brightness(img[i][j])] += 1;
            //histogram[img[i][j].red] += 1;
            //histogram[img.palette[img.img[i][j]].red] += 1;
            ++cnt;
        }
    }

    //normalize histogram
//    for (auto & it: histogram){
//        it /= cnt;
//    }

    double control = 0;

    double avg = 0;

    int64_t max = -1;
    cnt = 0;

    //uint64_t cumulative_amount = 0;
//    std::vector<uint64_t> cumulative_amount(256, 0);
//
//    for (auto it: histogram) {
//
//        cumulative_amount[cnt] = (cnt == 0 ? it : cumulative_amount[cnt - 1] + it);
//        std::cout << cumulative_amount[cnt] << '\n';
//       // std::cout.precision(2);
//        //std::cout << cnt << " : " << it << '\n';
//        //max = std::max(max, it);
//        //control += it;
//        ++cnt;
//
//    }

    std::vector<int64_t> blocks(5, 0);
    for (int i = 0; i < 5; ++i) {
        //blocks[i] = cumulative_amount[50 + 50 * i] - cumulative_amount[0 + 50 * i];
        for (int j = 0 + i * 50; j < 50 + i * 50; ++j) {
            blocks[i] += histogram[j];
        }
    }
    blocks[4] += histogram.back();

    auto copy = blocks;

    std::sort(copy.begin(), copy.end());

    for (auto &item: blocks) {
        if (item < copy[2] / 3) {
            item = -1;
        }
    }


    std::string dark = "too_dark";
    std::string bright = " too_bright";
    std::string contrast = "contrast";
    std::string soft = "soft";
    std::string normal = "normal";

    if (blocks[0] == -1 && blocks[1] == -1 && blocks[2] != -1 && blocks[3] != -1 && blocks[4] != -1) {
        return bright;
    } else if (blocks[3] == -1 && blocks[4] == -1 && blocks[0] != -1 && blocks[1] != -1 && blocks[2] != -1) {
        return dark;
    } else if (blocks[0] == -1 && blocks[4] == -1) {
        return soft;
    } else if ( blocks[2] == -1 ) {
        return contrast;
    } else {
        const double normalizing_coefficient = 1024;
        long double dark_sum = 0;
        long double bright_sum = 0;
        long double mid_sum = 0;

        for (int i = 0; i < 256; ++i) {
            long double exp = std::exp(-i * i / normalizing_coefficient);
            dark_sum += std::exp(-i * i / normalizing_coefficient) * histogram[i] * exp;
        }

        for (int i = 0; i < 256; ++i) {
            long double exp = std::exp(-i * i / normalizing_coefficient);
            bright_sum += std::exp(-i * i / normalizing_coefficient) * histogram[255 - i] * exp;
        }

        for (int i = 0; i < 128; ++i) {
            long double exp = std::exp(-i * i / normalizing_coefficient);
            mid_sum +=
                    std::exp(-i * i / normalizing_coefficient) * (histogram[127 - i] * exp + histogram[128 + i] * exp) /
                    2;
        }
        long double avg = (dark_sum + bright_sum + mid_sum) / 3;
        std::cout << "drk = " << dark_sum << "\nbright = " << bright_sum << "\nmid = " << mid_sum << "\n avg = " << avg
                  << '\n';

        if (dark_sum / mid_sum > 25 && dark_sum / bright_sum > 25) {
            return dark;
        } else if (bright_sum / mid_sum > 25 && bright_sum / dark_sum > 25) {
            return bright;
        } else if (mid_sum / dark_sum > 100 && mid_sum / bright_sum > 100) {
            return soft;
        } else if (((dark_sum / bright_sum > 1 && dark_sum / bright_sum < 3) ||
                    (bright_sum / dark_sum > 1 && dark_sum / bright_sum < 3)) &&
                   (dark_sum / mid_sum > 5 || bright_sum / mid_sum > 5)) {
            return contrast;
        } else {
            return normal;
        }


    }


//    avg = control / cnt;
//    std::cout.precision(5);
//    std::cout << "\n****************\n" << avg << '\n';
//
//    std::cout << max << '\n';
//    std::cout << control;

    return std::string();
// нормальное распределение/ нет контраста - определенный процент оставшихся пикселей лежит  в окрестности.
// при низкон монтрасте значение намного выше
// аналогично по концентрации пересвеченные и затемненные


}

#endif //DRAFT_IMG_ANALYZER_HPP
