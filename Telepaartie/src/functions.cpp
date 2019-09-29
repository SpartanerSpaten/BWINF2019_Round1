//
// Created by worker on 9/29/19.
//
#include "functions.h"


uint16_t Func::find_other(uint16_t x, uint16_t y){
    if((x==0&&y==1)||(x==1&&y==0))return 2;
    else if((x==1&&y==2)||(x==2&&y==1))return 0;
    else if((x==0&&y==2)||(x==2&&y==0))return 1;
}

bool Func::checkother(uint16_t x , const unsigned int colls[COLLUMNS]){
    uint16_t other = find_other(constraint[x],constraint[x+1]);
    return  (colls[other] > colls[constraint[x]]) || (colls[other] > colls[constraint[x+1]]);
}

bool Func::check_other_ind( uint16_t x , uint16_t y, const unsigned int colls[COLLUMNS]){
    uint16_t other = Func::find_other(x,y);
    return  (colls[other] > colls[x]) || (colls[other] > colls[y]);
}

uint16_t Func::sum_range(unsigned short x){
    uint16_t ret = 0;
    for (int i = 0; i < x; i++){
        ret += i;
    }
    return ret;
}

TreeNode * Func::easy_teleport(TreeNode* o,unsigned int colls[COLLUMNS], uint16_t x, uint16_t y){
    auto * temp = new TreeNode(o);
    temp->setcolls(colls);
    temp->teleport(x, y);
    return temp;
}