//
// Created by worker on 9/29/19.
//

#ifndef TELEPAARTIE_FUNCTIONS_H
#define TELEPAARTIE_FUNCTIONS_H
#include "treenode.h"

namespace Func{

    uint16_t find_other(uint16_t x, uint16_t y);
    bool checkother(uint16_t x , const unsigned int colls[COLLUMNS]);
    bool check_other_ind( uint16_t x , uint16_t y, const unsigned int colls[COLLUMNS]);
    uint16_t sum_range(unsigned short x);
    TreeNode * easy_teleport(TreeNode* o, unsigned int colls[COLLUMNS], uint16_t x, uint16_t y);

}
#endif //TELEPAARTIE_FUNCTIONS_H
