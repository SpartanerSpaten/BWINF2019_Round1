//
// Created by worker on 9/26/19.
//

#include "./src/treenode.h"

#define MAXITERATIONS 6

void iterate(unsigned int data[COLLUMNS]){
    // Inits essential Static Variables
    TreeNode::init();
    // Creating Tree Root Node
    auto * root = new TreeNode(nullptr);

    // Sets Start data
    root->setcolls(data);
    TreeNode * focus = root;
    TreeNode * found;

    unsigned short current_iter = 0;
    unsigned int iteration_size = 1; // Number of Parents

    std::vector<TreeNode*> parents;
    parents.push_back(root);

    while (current_iter < MAXITERATIONS){
        for (int i = 0; i < iteration_size;i++){
            parents[i]->generate_childs();



        }


        current_iter++;
    }


}


int main (){


    unsigned int data[COLLUMNS] = {2,4,7};


    std::tuple<bool, size_t , size_t >  z = x->check();
    x->generate_childs();

    return 0;




}