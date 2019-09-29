//
// Created by worker on 9/26/19.
//

#include "./src/treenode.h"
#include <iostream>
#define MAXITERATIONS 6

std::vector<TreeNode*> iterate(unsigned int data[COLLUMNS]){
    // Inits essential Static Variables
    TreeNode::init();
    // Creating Tree Root Node
    auto * root = new TreeNode(nullptr);

    // Sets Start data
    root->setcolls(data);
    TreeNode * focus;

    unsigned short current_iter = 0;
    unsigned int iteration_size = 1; // Number of Parents

    std::vector<TreeNode*> parents; //Current Nodes
    std::vector<TreeNode*> temp_new_partents; // Merged Noded
    std::vector<TreeNode*> pathtolll; // Nodes that provide a result
    std::vector<TreeNode*> leaves; // Nodes with LLL

    bool done_flag = false; // Is True when something is found

    std::tuple<bool, size_t ,size_t > temp;
    parents.push_back(root);

    while (current_iter < MAXITERATIONS && !done_flag){
        for (unsigned int i = 0; i < iteration_size;i++){
            temp = parents[i]->check();
            if(std::get<0>(temp)){
                pathtolll.push_back(parents[i]);
                done_flag = true;
            }else {
                parents[i]->generate_childs();
            }
        }
        if (!done_flag){
            temp_new_partents.clear();
            for (unsigned int i = 0; i < iteration_size;i++){
                temp_new_partents.insert(temp_new_partents.end(), parents[i]->children.begin(), parents[i]->children.end());
            }
            iteration_size = parents.size();
            parents = temp_new_partents;
        }
        current_iter++;
    }

    for (int i = 0; i < pathtolll.size();i++){
        focus = pathtolll[i];
        leaves.push_back(focus->finish());
    }

    return leaves;
}


int main (int argc, char *argv[]){

    unsigned int data[COLLUMNS];

    std::cout << "============================== Telepaartie Aufgabe3 ==============================" << std::endl;

    for (int i = 0; i < 3; i++){
        data[i] = std::stoi(argv[i + 1]);
    }

    std::vector<TreeNode*> leave_nodes = iterate(data);

    TreeNode * current; TreeNode * head;

    for( int i = 0; i < leave_nodes.size();i++){
        current = leave_nodes[i];
        while (current != nullptr){
            current->operator<<(std::cout);
            current = current->parent;
            if (current->parent == nullptr){
                head = current;
            }
        }
    }
    delete head;

    return 0;




}