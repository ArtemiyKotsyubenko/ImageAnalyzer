//
// Created by artemiy on 17.06.2020.
//

#ifndef DRAFT_STREAMS_HPP
#define DRAFT_STREAMS_HPP
#include <fstream>
#include <iostream>

class Ofstream {
private:
    std::ofstream file;
public:


    explicit Ofstream(const char *path) : file(path) {
        if (file.fail()) {
            std::cerr << "Error opening file \n";
            exit(1);
        }
    }

    ~Ofstream() {
        file.close();
    }

};

class Ifstream {
    std::ifstream file;
public:


    explicit Ifstream(const char *path) : file(path) {
        if (file.fail()) {
            std::cerr << "Error opening file \n";
            exit(1);
        }
    }

    ~Ifstream() {
        file.close();
    }
};

#endif //DRAFT_STREAMS_HPP
