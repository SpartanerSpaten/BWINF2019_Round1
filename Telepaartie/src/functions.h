//
// Created by worker on 9/29/19.
//

#ifndef TELEPAARTIE_FUNCTIONS_H
#define TELEPAARTIE_FUNCTIONS_H
#include "treenode.h"

namespace Func{

    uint16_t findOther(uint16_t x, uint16_t y);
    bool checkOther(uint16_t x , const unsigned int *colls);
    bool checkOtherIndep(uint16_t x , uint16_t y, const unsigned int *colls);
    uint16_t sumRange(unsigned short x);
    TreeNode * easyTeleport(TreeNode* o, unsigned int *colls, uint16_t x, uint16_t y);
    bool validatesInput(std::string &);

}
#endif //TELEPAARTIE_FUNCTIONS_H
