//
// Created by artemiy on 17.06.2020.
//

#include <iostream>
#include <fstream>
#include <cstdint>
#include "ImageBMP.hpp"
int main(){
    int cnt = 0;

    std::ifstream strm("1.bmp");
    std::ofstream fout ("test.bmp");
    ImageBMP img(strm);
    img.print();

    img.dump(fout, strm);
    //std::cout << static_cast<u_char>(0b01001101u);

//    while (strm.peek()!= EOF){
//        strm.get();
//        ++cnt;
//    }

    //std::cout << cnt;
    //int  a = 0b1110'0010'101'0'0000'0000'0000'000;
    return 0;

}
