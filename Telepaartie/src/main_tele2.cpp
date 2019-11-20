//
// Created by worker on 10/19/19.
//

#include <iostream>

#include "treenode.hpp"

std::vector<std::vector<unsigned int>> generateRoots(int n) {
    unsigned int size = 1;
    int intSize = 1;
    std::vector<std::vector<unsigned int>> ret;
    while (n - intSize * 2 >= 1) {
        ret.push_back({size, size, (unsigned int) n - 2 * intSize});
        size++;
        intSize++;
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

bool is_number(const std::string &s) {
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
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
    if (!is_number(std::string(argv[1]))) {
        std::cerr << "Given parameter should be a positive number" << std::endl;
        return 1;
    }
    int num = std::stoi(argv[1]);

    if (num < 0) {
        std::cerr << "The number has to be positive" << std::endl;
        return 1;
    }

    std::vector<std::vector<unsigned int>> data = generateRoots(num);
    TreeNode::init();
    std::vector<unsigned int> best;

    if (num > 5) {
        std::tuple<bool, unsigned int, unsigned int> tempWarn;

        std::vector<TreeNodeBackward *> current;
        std::vector<TreeNodeBackward *> temporaryList;
        TreeNodeBackward *head;
        int record, timeout, counter;
        record = -10;

        for (std::vector<unsigned int> startValues : data) {
            head = new TreeNodeBackward(nullptr, startValues);
            current.push_back(head);
            timeout = 7;
            counter = 0;

            while (timeout >= 1) {
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
                d = (int) distanceFunction(temp->getColumns());
                if (d > record) {
                    best = temp->getColumns();
                    record = d;
                }
            }

            delete head;
            current.clear();
            temporaryList.clear();
        }
    } else {
        switch (num) {
            case 5:
                best = {1, 2, 3};
                break;
            case 4:
                best = {1, 1, 2};
                break;
            case 3:
                best = {1, 1, 1};
                break;
            case 2:
                best = {1, 1, 0};
                break;
            case 1:
                best = {1, 0, 0};
                break;
            case 0:
                best = {0, 0, 0};
                break;
        }
    }

    for (unsigned int y: best) {
        std::cout << y << " ";
    }
    std::cout << std::endl;

    return 0;

}