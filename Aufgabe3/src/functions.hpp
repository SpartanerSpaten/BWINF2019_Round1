//
// Created by worker on 10/21/19.
//

#ifndef TELEPAARTIE2_FUNCTIONS_HPP
#define TELEPAARTIE2_FUNCTIONS_HPP

#include <tuple>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>

namespace Func {

    uint16_t findOther(uint16_t x, uint16_t y);

    bool checkOther(uint16_t x, const unsigned int *colls);

    bool checkOtherIndep(uint16_t x, uint16_t y, std::vector<unsigned int> &colls);

    uint16_t sumRange(unsigned short x);

    bool validatesInput(std::string &);

    std::tuple<unsigned int, unsigned int> func(std::tuple<unsigned int, unsigned int>);

    std::tuple<unsigned int, unsigned int> revFunc(std::tuple<unsigned int, unsigned int>);

}


#endif //TELEPAARTIE2_FUNCTIONS_HPP
