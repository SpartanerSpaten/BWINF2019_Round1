//
// Created by worker on 9/26/19.
//

#include "treenode.hpp"
#include <iostream>
#include <memory>

#define MAXITERATIONS 6

std::vector<TreeNodeForward *> iterate(std::vector<unsigned int> data) {
    // Inits essential Static Variables
    TreeNode::init();
    // Creating Tree Root Node
    auto root = new TreeNodeForward(nullptr, data);

    // Sets Start data
    //root->setColls(data);

    unsigned short current_iter = 0;
    unsigned int iteration_size = 1; // Number of Parents

    std::vector<TreeNodeForward *> parents; //Current Nodes
    std::vector<TreeNodeForward *> temp_new_parents; // Merged Noded
    std::vector<TreeNodeForward *> pathtolll; // Nodes that provide a result
    std::vector<TreeNodeForward *> leaves; // Nodes with LLL

    bool done_flag = false; // Is True when something is found

    std::tuple<bool, size_t, size_t> temp;
    parents.push_back(root);

    while (current_iter < MAXITERATIONS && !done_flag) {
        for (unsigned int i = 0; i < iteration_size; i++) {
            temp = parents[i]->preWarn();
            if (std::get<0>(temp)) {
                pathtolll.push_back(parents[i]);
                done_flag = true;
            } else {
                parents[i]->generateChildren();
            }
        }
        if (!done_flag) {
            temp_new_parents.clear();
            for (unsigned int i = 0; i < iteration_size; i++) {
                parents[i]->insertChildren(temp_new_parents);
            }
            iteration_size = temp_new_parents.size();
            parents = temp_new_parents;
        }
        current_iter++;
    }
    for (TreeNodeForward *winningNode: pathtolll) {
        leaves.push_back(winningNode->finish());
    }

    return leaves;
}


int main(int argc, char *argv[]) {

    if (argc < 4) {
        std::cout << "Not enough arguments" << std::endl;
        exit(1);
    }

    std::vector<unsigned int> data = {};

    std::cout << "============================== Telepaartie Aufgabe3 ==============================" << std::endl;

    std::string temp_string;
    for (int i = 0; i < 3; i++) {
        temp_string = std::string(argv[i + 1]);
        if (Func::validatesInput(temp_string)) {
            data.push_back(std::stoi(argv[i + 1]));
        }
    }

    std::vector<TreeNodeForward *> leave_nodes = iterate(data);

    int i = 0;
    TreeNodeForward *head = nullptr;

    for (TreeNodeForward *current: leave_nodes) {
        std::cout << "********** Solution: " << i << " **********" << std::endl;
        while (current != nullptr) {
            std::cout << *current << std::endl;
            current = current->getParent();
            if (current != nullptr && current->getParent() == nullptr) {
                head = current;
            }
        }
        i++;
    }
    delete head;

    return 0;
};