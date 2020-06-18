//
// Created by artemiy on 17.06.2020.
//

#include <iostream>
#include <fstream>
#include <cstdint>
typedef uint32_t DWORD;   // DWORD = unsigned 32 bit value
typedef uint16_t WORD;    // WORD = unsigned 16 bit value
typedef uint8_t BYTE;     // BYTE = unsigned 8 bit value
typedef long LONG;






int main(){
    int cnt = 0;

    std::ifstream strm("01 (1).bmp");

    while (strm.peek()!= EOF){
        strm.get();
        ++cnt;
    }

    std::cout << cnt;

    return 0;
}
