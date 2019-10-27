//
// Created by worker on 10/19/19.
//

#include <iostream>

#include "treenode.hpp"
#include "set.hpp"

std::vector<std::vector<unsigned int>> generateRoots(int n) {
    unsigned int size = 1;
    std::vector<std::vector<unsigned int>> ret;
    while (n - size * 2 > 1) {
        if (size % 2 == 0) {
            ret.push_back({size, size, n - 2 * size});
        }
        size++;
    }
    return ret;
}

bool searchVector(std::vector<TreeNodeBackward *> &s, TreeNodeBackward *a) {
    for (TreeNodeBackward *y: s) {
        if (y->getColumns() == a->getColumns()) {
            return true;
        }
    }
    return false;
}


std::vector<TreeNodeBackward *> sortOut(std::vector<TreeNodeBackward *> &current) {
    std::vector<TreeNodeBackward *> returnVal;
    for (TreeNodeBackward *y: current) {
        if (!std::get<0>(y->preWarn()) && !searchVector(returnVal, y)) {
            returnVal.push_back(y);
        }
    }
    return returnVal;
}

unsigned int distanceFunction(std::vector<unsigned int> data) {
    auto root = new TreeNodeForward(nullptr, data);

    // Sets Start data
    //root->setColls(data);

    unsigned short current_iter = 0;
    unsigned int iteration_size = 1; // Number of Parents

    std::vector<TreeNodeForward *> parents; //Current Nodes
    std::vector<TreeNodeForward *> temp_new_parents; // Merged Noded
    std::vector<TreeNodeForward *> leaves; // Nodes with LLL
    unsigned int d = 0;

    bool done_flag = false; // Is True when something is found

    std::tuple<bool, size_t, size_t> temp;
    parents.push_back(root);

    while (current_iter < 6 && !done_flag) {
        for (unsigned int i = 0; i < iteration_size; i++) {
            temp = parents[i]->preWarn();
            if (std::get<0>(temp)) {
                d = current_iter;
                done_flag = true;
                break;
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
    delete root;

    return d;
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Not enough arguments" << std::endl;
        exit(1);
    }

    int num = std::stoi(argv[1]);

    std::vector<std::vector<unsigned int>> data = generateRoots(num);
    TreeNode::init();

    std::tuple<bool, unsigned int, unsigned int> tempWarn;

    std::vector<TreeNodeBackward *> current;
    std::vector<TreeNodeBackward *> temporaryList;
    TreeNodeBackward *head;
    bool done;
    int record, timeout, counter;
    record = -10;
    std::vector<unsigned int> best;
    for (std::vector<unsigned int> startValues : data) {
        head = new TreeNodeBackward(nullptr, startValues);
        current.push_back(head);
        done = false;
        timeout = 7;
        counter = 0;

        while (!done && timeout >= 1) {
            for (TreeNodeBackward *temp : current) {
                temp->generateChildren();
                temp->insertChildren(temporaryList);
            }
            if (counter > 2 && num > 10) {
                current = sortOut(temporaryList);
            } else {
                current = temporaryList;
            }

            timeout--;
            counter++;
        }
        int d = 0;
        for (TreeNodeBackward *temp: current) {
            d = distanceFunction(temp->getColumns());
            if (d > record) {
                best = temp->getColumns();
                record = d;
            }
        }

        delete head;
        current.clear();
        temporaryList.clear();
    }

    for (unsigned int y: best) {
        std::cout << y << " ";
    }
    std::cout << std::endl;

    return 0;

}