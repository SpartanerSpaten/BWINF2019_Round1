//
// Created by worker on 9/26/19.
//

#include "treenode.h"
#include <iostream>

uint16_t find_other(uint16_t x, uint16_t y){
    if((x==0&&y==1)||(x==1&&y==0))return 2;
    else if((x==1&&y==2)||(x==2&&y==1))return 0;
    else if((x==0&&y==2)||(x==2&&y==0))return 1;
}

bool checkother(uint16_t x, unsigned int colls[COLLUMNS]){
    uint16_t other = find_other(constraint[x],constraint[x+1]);
    return  (colls[other] > colls[constraint[x]]) || (colls[other] > colls[constraint[x+1]]);
}


void TreeNode::init() {
    numchilds = std::pow(COLLUMNS, 2) - COLLUMNS;
    constraint = (uint16_t*) malloc((numchilds * 2) * sizeof(uint16_t));
    int i = 0;
    for (int x = 0; x < ceil(COLLUMNS / 2)+1; x++){
        for(int y = ceil(COLLUMNS / 2); y < COLLUMNS;y++){
            if (x != y){
                constraint[i] = x;
                constraint[i+1] = y;
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

TreeNode::~TreeNode() {}

std::tuple<bool, uint16_t, uint16_t> TreeNode::check() {
    for (int x = 0; x < numchilds * 2; x+= 2){
        std::cout << constraint[x] << "/" << constraint[x+1] << std::endl;
        if ((colls[constraint[x]] == 2 * colls[constraint[x+1]] || colls[constraint[x+1]] == 2 * colls[x]) && checkother(x, colls)){
            return std::make_tuple(true, constraint[x], constraint[x+1]);
        }else if (colls[constraint[x]] == colls[constraint[x+1]] ){
            return std::make_tuple(true, constraint[x], constraint[x+1]);
        }
    }
    return std::make_tuple(false, 0, 0);
}

void TreeNode::random() {
    for (int i = 0; i < COLLUMNS; i++){
        colls[i] = rand() % 100;
    }
}

void TreeNode::generate_childs() {
    int status = 0;
    TreeNode * j;
    for (int x = 0; x < numchilds; x+= 2){
        if (status == 0){
            j = new TreeNode(this);
        }
        j->setcolls(this->colls);
        status = j->teleport( constraint[x], constraint[x+1]);
        if (status == 0){
            children.push_back(j);
        }
        childs++;
    }
}


int TreeNode::teleport(uint16_t obj1, uint16_t obj2) {
    int copy = 0;
    if (colls[obj2] >= 2 * colls[obj1]){
        copy = colls[obj1];
        colls[obj1] += copy;
        colls[obj2] -= copy;
        return 0;

    }else if (colls[obj1] >= 2 * colls[obj2]){
        copy = colls[obj2];
        colls[obj2] += copy;
        colls[obj1] -= copy;
        return 0;
    }else{
        return 1;
    }
}