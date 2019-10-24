//
// Created by worker on 10/21/19.
//

#include "functions.hpp"
#include <memory>

uint16_t Func::findOther(uint16_t x, uint16_t y) {
    if ((x == 0 && y == 1) || (x == 1 && y == 0))return 2;
    else if ((x == 1 && y == 2) || (x == 2 && y == 1))return 0;
    else if ((x == 0 && y == 2) || (x == 2 && y == 0))return 1;
    return 0;
}


bool Func::checkOtherIndep(uint16_t x, uint16_t y, std::vector<unsigned int> &colls) {
    uint16_t other = Func::findOther(x, y);
    return (colls[other] > colls[x]) || (colls[other] > colls[y]);
}

uint16_t Func::sumRange(unsigned short x) {
    uint16_t ret = 0;
    for (int i = 0; i < x; i++) {
        ret += i;
    }
    return ret;
}

bool Func::validatesInput(std::string &x) {
    return !x.empty() && std::find_if(x.begin(),
                                      x.end(), [](char c) { return !std::isdigit(c); }) == x.end();
}


std::tuple<unsigned int, unsigned int> Func::func(std::tuple<unsigned int, unsigned int> input) {
    if (std::get<0>(input) > std::get<1>(input)) {
        return std::make_tuple(std::get<0>(input) - std::get<1>(input), std::get<1>(input) * 2);
    } else {
        return std::make_tuple(std::get<1>(input) - std::get<0>(input), std::get<0>(input) * 2);
    }
}

std::tuple<unsigned int, unsigned int> Func::revFunc(std::tuple<unsigned int, unsigned int> input) {
    if (std::get<0>(input) > std::get<1>(input)) {
        return std::make_tuple((unsigned int) (std::get<0>(input) / 2),
                               (unsigned int) (std::get<1>(input) + std::get<0>(input) / 2));
    } else {
        return std::make_tuple((unsigned int) (std::get<1>(input) / 2),
                               (unsigned int) (std::get<0>(input) + std::get<1>(input) / 2));
    }
}