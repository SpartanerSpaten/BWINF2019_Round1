//
// Created by worker on 9/26/19.
//

#include "treenode.h"
#include "./functions.h"
#include <iostream>

void TreeNode::init() {
    Global::numchilds = Func::sumRange(COLLUMNS);
    Global::constraint = new uint16_t[Global::numchilds * 2];
    int i = 0;
    for (int x = 0; x < ceil(COLLUMNS / 2)+1; x++){
        for(int y = ceil(COLLUMNS / 2); y < COLLUMNS;y++){
            if (x != y){
                Global::constraint[i] = x;
                Global::constraint[i+1] = y;
                i += 2;
            }
        }
    }
}

TreeNode::TreeNode(TreeNode * ipar) {
    parent = ipar;
    childs = 0;
}
TreeNode::TreeNode(TreeNode * ipar, unsigned int* ix) {
    parent = ipar;
    childs = 0;
    memcpy(colls, ix, COLLUMNS);
}

TreeNode::~TreeNode() {
    for (int i = 0; i < children.size();i++){
        delete children[i];
    }
}

std::tuple<bool, uint16_t, uint16_t> TreeNode::check() {
    for (int x = 0; x <  Global::numchilds * 2; x+= 2){
        if ((colls[ Global::constraint[x]] == 2 * colls[ Global::constraint[x+1]] || colls[ Global::constraint[x+1]] == 2 * colls[x]) &&
                Func::checkOtherIndep(Global::constraint[x], Global::constraint[x + 1], colls)){
            return std::make_tuple(true,  Global::constraint[x],  Global::constraint[x+1]);
        }else if (colls[ Global::constraint[x]] == colls[ Global::constraint[x+1]] ){
            return std::make_tuple(true,  Global::constraint[x],  Global::constraint[x+1]);
        }
        else if((colls[ Global::constraint[x]] == 3 * colls[ Global::constraint[x+1]] || colls[ Global::constraint[x+1]] == 3 * colls[x])){
            return std::make_tuple(true, Global::constraint[x],  Global::constraint[x+1]);
        }
    }
    return std::make_tuple(false, 0, 0);
}

void TreeNode::random() {
    for (int i = 0; i < COLLUMNS; i++){
        colls[i] = rand() % 100;
    }
}

void TreeNode::generateChilds() {
    int status = 0;
    TreeNode * j;
    for (int x = 0; x <  Global::numchilds+2; x+= 2){
        if (status == 0){
            j = new TreeNode(this);
        }
        j->setColls(this->colls);
        status = j->teleport(  Global::constraint[x],  Global::constraint[x+1]);
        if (status == 0){
            children.push_back(j);
        }
        childs++;
    }
}


int TreeNode::teleport(uint16_t obj1, uint16_t obj2) {
    int copy = 0;
    if (colls[obj2] >= colls[obj1]){
        copy = colls[obj1];
        colls[obj1] += copy;
        colls[obj2] -= copy;
        return 0;

    }else if (colls[obj1] >= colls[obj2]){
        copy = colls[obj2];
        colls[obj2] += copy;
        colls[obj1] -= copy;
        return 0;
    }else{
        return 1;
    }
}

TreeNode* TreeNode::finish() {
    TreeNode * ret; TreeNode * temp;
    std::tuple<bool, uint16_t, uint16_t> x = check();
    if (!std::get<0>(x))return this;

    if(colls[std::get<1>(x)] == colls[std::get<2>(x)]){
        ret = Func::easyTeleport(this, this->colls, std::get<1>(x), std::get<2>(x));
        return ret;
    }else  if ((colls[std::get<1>(x)] == 2 * colls[std::get<2>(x)] || colls[std::get<2>(x)] == 2 * colls[std::get<1>(x)]) &&
            Func::checkOtherIndep(std::get<1>(x), std::get<2>(x), colls)){
        temp = new TreeNode(this);
        temp->setColls(colls);
        uint16_t other = Func::findOther(std::get<1>(x), std::get<2>(x));
        if (colls[std::get<1>(x)] > colls[std::get<2>(x)]){
            temp->teleport(other, std::get<2>(x));
        }else{
            temp->teleport(std::get<1>(x), other);
        }
        ret = Func::easyTeleport(temp, temp->colls, std::get<1>(x), std::get<2>(x));
        return ret;

    } else if (colls[std::get<1>(x)] == 3 * colls[std::get<2>(x)] || colls[std::get<2>(x)] == 3 * colls[std::get<1>(x)]){
        temp = Func::easyTeleport(this, this->colls, std::get<1>(x), std::get<2>(x));
        ret = Func::easyTeleport(temp, temp->colls, std::get<1>(x), std::get<2>(x));
        return ret;
    }
    return nullptr;
}

std::ostream& operator<<(std::ostream &os, const TreeNode &obj) {
    for (int i = 0; i < COLLUMNS; i++){
        std::cout << obj.colls[i] << " / ";
    }
    return std::cout;
}