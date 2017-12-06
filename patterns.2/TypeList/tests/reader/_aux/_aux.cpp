//
// Created by Karyamin_A on 06.12.2017.
//

#include "_aux.h"
#include <sstream>

int transformers::SuperDoubleInt::decompress() {
    return int(x * 2);
}

std::basic_istream<char> &transformers::operator>>(std::istream &is, SuperDoubleInt &sd) {
    is >> sd.x;
}

std::basic_istream<char> &transformers::operator>>(std::istream &is, SuperIntInt &sii) {
    is >> sii.x;
}

int transformers::SuperIntInt::decompress() {
    return x*2;
}

double transformers::SuperIntDouble::decompress() {
    return x * 2.0;
}

std::basic_istream<char> &transformers::operator>>(std::istream &is, SuperIntDouble &si) {
    is >> si.x;
}

std::basic_string<char> transformers::SuperIntString::decompress() {
    std::stringstream ss;
    ss << (x * 2);
    return ss.str();
}

std::basic_istream<char> &transformers::operator>>(std::istream &is, SuperIntString &sis) {
    is >> sis.x;
}
