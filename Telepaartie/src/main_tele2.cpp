//
// Created by worker on 10/19/19.
//

#include "set.hpp"
#include <iostream>
#include "treenode.hpp"


std::vector<std::vector<unsigned int>> generateRoots(int n) {
    unsigned int size = 1;
    std::vector<std::vector<unsigned int>> ret;
    while (n - size * 2 > 1) {
        ret.push_back({size, size, n - 2 * size});
        size++;
    }
    return ret;
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
    record = 0;
    std::vector<unsigned int> best;
    for(std::vector<unsigned int> startValues : data){
        head = new TreeNodeBackward(nullptr, startValues);
        current.push_back(head);
        done = false;
        timeout = 7;
        counter = 0;

        while (!done && timeout >= 1) {
            for (TreeNodeBackward *temp : current) {
                temp->generateChildren();
                done = temp->getChilds() == 0 && !std::get<0>(temp->preWarn());
                if (done) {
                    if (counter > record) {
                        best = temp->getColumns();
                        record = counter;
                    }
                    break;
                }
                temp->insertChildren(temporaryList);
            }
            current = temporaryList;
            timeout--;
            counter++;
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