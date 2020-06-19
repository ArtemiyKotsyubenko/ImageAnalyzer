//
// Created by artemiy on 19.06.2020.
//

#ifndef DRAFT_IMG_ANALYZER_HPP
#define DRAFT_IMG_ANALYZER_HPP
#include "ImageBMP.hpp"

// кривая Гаусса - нормальное изображение
// высокий пик в центре - малоконтрастное изображение
// высокий пик слева - тёмное изображение
// высокий пик справа - засвеченное изображение
// два пика по краям - контрастное изображение




struct ImgAnalyser{
private:

public:
    std::string operator()(const ImageBMP& img);
};

#endif //DRAFT_IMG_ANALYZER_HPP
