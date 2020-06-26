//
// Created by artemiy on 17.06.2020.
//

#include <iostream>
#include <fstream>
#include "ImageBMP.hpp"
#include "Img_analyzer.hpp"

int main(int argc, char **argv) {
    std::ifstream strm(argv[1], std::ios::binary);
    ImageBMP img(strm);
    std::cout << Analyser(img);
    return 0;
}
