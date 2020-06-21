//
// Created by artemiy on 17.06.2020.
//

#include <iostream>
#include <fstream>
#include <cstdint>
#include "ImageBMP.hpp"
#include "Img_analyzer.hpp"

int main(int argc, char **argv) {
    int cnt = 0;

    std::ifstream strm(argv[1]);
    ImageBMP img(strm);
    std::cout << Analyser(img);
    return 0;

}
