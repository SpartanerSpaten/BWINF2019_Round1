//
// Created by worker on 9/29/19.
//
#include "functions.h"
#include <algorithm>
#include <iostream>

uint16_t Func::findOther(uint16_t x, uint16_t y){
    if((x==0&&y==1)||(x==1&&y==0))return 2;
    else if((x==1&&y==2)||(x==2&&y==1))return 0;
    else if((x==0&&y==2)||(x==2&&y==0))return 1;
    return 0;
}

bool Func::checkOther(uint16_t x , const unsigned int *colls){
    std::cout << Global::constraint;
    uint16_t other = Func::findOther(Global::constraint[x], Global::constraint[x + 1]);
    return  (colls[other] > colls[ Global::constraint[x]]) || (colls[other] > colls[ Global::constraint[x+1]]);
}

bool Func::checkOtherIndep(uint16_t x , uint16_t y, const unsigned int *colls){
    uint16_t other = Func::findOther(x, y);
    return  (colls[other] > colls[x]) || (colls[other] > colls[y]);
}

uint16_t Func::sumRange(unsigned short x){
    uint16_t ret = 0;
    for (int i = 0; i < x; i++){
        ret += i;
    }
    return ret;
}

TreeNode * Func::easyTeleport(TreeNode* o, unsigned int *colls, uint16_t x, uint16_t y){
    auto * temp = new TreeNode(o);
    temp->setColls(colls);
    temp->teleport(x, y);
    return temp;
}

bool Func::validatesInput(std::string &x ) {
    return !x.empty() && std::find_if(x.begin(),
                                      x.end(), [](char c) { return !std::isdigit(c); }) == x.end();
}
