//
// Created by worker on 10/21/19.
//

#include "treenode.hpp"
#include <cmath>

void TreeNode::init() {
    Global::numChilds = Func::sumRange(COLUMNS);
    Global::constraint = new uint16_t[Global::numChilds * 2];
    int i = 0;
    for (int x = 0; x < ceil(COLUMNS / 2) + 1; x++) {
        for (int y = ceil(COLUMNS / 2); y < COLUMNS; y++) {
            if (x != y) {
                Global::constraint[i] = x;
                Global::constraint[i + 1] = y;
                i += 2;
            }
        }
    }
}

std::ostream &operator<<(std::ostream &os, const TreeNodeForward &obj) {
    for (int i = 0; i < COLUMNS; i++) {
        std::cout << obj.columns[i] << " / ";
    }
    return std::cout;
}

std::ostream &operator<<(std::ostream &os, const TreeNodeBackward &obj) {
    for (int i = 0; i < COLUMNS; i++) {
        std::cout << obj.columns[i] << " / ";
    }
    return std::cout;
}


std::ostream &TreeNodeForward::operator<<(std::ostream &os) {
    for (int i = 0; i < COLUMNS; i++) {
        std::cout << columns[i] << " / ";
    }
    return std::cout;
}

TreeNodeForward::TreeNodeForward() {
    parent = nullptr;
    childs = 0;
}

TreeNodeForward::TreeNodeForward(TreeNodeForward *ptr) {
    parent = ptr;
    childs = 0;
}

TreeNodeForward::TreeNodeForward(TreeNodeForward *ptr, std::vector<unsigned int> &icolumns) {
    parent = ptr;
    childs = 0;
    columns = icolumns;
}

TreeNodeForward::~TreeNodeForward() {
    for (TreeNodeForward *x : children) {
        delete x;
    }
}

void TreeNodeForward::move(unsigned int x, unsigned int y) {
    if (columns[y] > columns[x]) {
        columns[y] -= columns[x];
        columns[x] *= 2;

    } else {
        columns[x] -= columns[y];
        columns[y] *= 2;

    }
}

void TreeNodeForward::generateChildren() {
    TreeNodeForward *j = nullptr;
    for (unsigned int x = 0; x < Global::numChilds + 2; x += 2) {
        j = new TreeNodeForward(this, this->columns);
        j->move(Global::constraint[x], Global::constraint[x + 1]);
        children.push_back(j);
        childs++;
    }
}

std::tuple<bool, unsigned int, unsigned int> TreeNodeForward::preWarn() {
    for (unsigned int x = 0; x < Global::numChilds * 2; x += 2) {
        if ((columns[Global::constraint[x]] == 2 * columns[Global::constraint[x + 1]] ||
             columns[Global::constraint[x + 1]] == 2 * columns[Global::constraint[x]]) &&
            Func::checkOtherIndep(Global::constraint[x], Global::constraint[x + 1], columns)) {
            return std::make_tuple(true, Global::constraint[x], Global::constraint[x + 1]);
        } else if (columns[Global::constraint[x]] == columns[Global::constraint[x + 1]]) {
            return std::make_tuple(true, Global::constraint[x], Global::constraint[x + 1]);
        } else if ((columns[Global::constraint[x]] == 3 * columns[Global::constraint[x + 1]] ||
                    columns[Global::constraint[x + 1]] == 3 * columns[x])) {
            return std::make_tuple(true, Global::constraint[x], Global::constraint[x + 1]);
        }
    }
    return std::make_tuple(false, 0, 0);
}

TreeNodeForward *TreeNodeForward::finish() {
    TreeNodeForward *ret = nullptr;
    TreeNodeForward *temp = nullptr;
    std::tuple<bool, uint16_t, uint16_t> x = preWarn();
    if (!std::get<0>(x))return this;

    if (columns[std::get<1>(x)] == columns[std::get<2>(x)]) {
        ret = easyTeleport(this, this->columns, std::get<1>(x), std::get<2>(x));
        return ret;
    } else if ((columns[std::get<1>(x)] == 2 * columns[std::get<2>(x)] ||
                columns[std::get<2>(x)] == 2 * columns[std::get<1>(x)]) &&
               Func::checkOtherIndep(std::get<1>(x), std::get<2>(x), columns)) {
        temp = new TreeNodeForward(this, columns);
        uint16_t other = Func::findOther(std::get<1>(x), std::get<2>(x));
        if (columns[std::get<1>(x)] > columns[std::get<2>(x)]) {
            temp->move(other, std::get<2>(x));
        } else {
            temp->move(std::get<1>(x), other);
        }
        ret = easyTeleport(temp, temp->columns, std::get<1>(x), std::get<2>(x));
        return ret;

    } else if (columns[std::get<1>(x)] == 3 * columns[std::get<2>(x)] ||
               columns[std::get<2>(x)] == 3 * columns[std::get<1>(x)]) {
        temp = easyTeleport(this, columns, std::get<1>(x), std::get<2>(x));
        ret = easyTeleport(temp, temp->columns, std::get<1>(x), std::get<2>(x));
        return ret;
    }
    return nullptr;
}

TreeNodeForward *TreeNodeForward::easyTeleport(TreeNodeForward *o, std::vector<unsigned int> &column,
                                               uint16_t x, uint16_t y) {
    auto *temp = new TreeNodeForward(o, column);
    temp->move(x, y);
    return temp;
}


TreeNodeBackward::TreeNodeBackward() {
    parent = nullptr;
    childs = 0;
}

TreeNodeBackward::TreeNodeBackward(TreeNodeBackward *iptr) {
    parent = iptr;
    childs = 0;
}

TreeNodeBackward::TreeNodeBackward(TreeNodeBackward *iptr, std::vector<unsigned int> &data) {
    columns = data;
    parent = iptr;
    childs = 0;
}

TreeNodeBackward::~TreeNodeBackward() {
    for (TreeNodeBackward *x: children) {
        delete x;
    }
}

void TreeNodeBackward::move(unsigned int x, unsigned int y, bool sec) {
    if (columns[x] > columns[y] && columns[x] % 2 == 0 && sec) {
        columns[x] /= 2;
        columns[y] += columns[x];
    } else if (columns[y] > columns[x] && columns[y] % 2 == 0 && sec) {
        columns[y] /= 2;
        columns[x] += columns[y];
    } else if (columns[x] > columns[y] && columns[y] % 2 == 0) {
        columns[y] /= 2;
        columns[x] += columns[y];
    } else if (columns[y] > columns[x] && columns[x] % 2 == 0) {
        columns[x] /= 2;
        columns[y] += columns[x];
    }
}

void TreeNodeBackward::advancedMove(unsigned int x, unsigned int y) {
    auto *j = new TreeNodeBackward(this, columns);
    j->move(x, y, true);
    if (!j->search(j->columns, false)) {
        children.push_back(j);
        childs++;
    } else {
        delete j;
    }
    if (columns[x] % 2 == 0 and columns[y] % 2 == 0) {
        j = new TreeNodeBackward(this, columns);
        j->move(y, x, false);
        if (!j->search(j->columns, false)) {
            children.push_back(j);
            childs++;
        } else {
            delete j;
        }
    }
}

void TreeNodeBackward::move(unsigned int, unsigned int) {}


void TreeNodeBackward::generateChildren() {
    for (unsigned int x = 0; x < Global::numChilds * 2; x += 2) {
        advancedMove(Global::constraint[x], Global::constraint[x + 1]);
    }
}

bool TreeNodeBackward::search(std::vector<unsigned int> &s, bool pass) {
    // The boolean value ist just preventing that it compares it to it self
    std::sort(s.begin(), s.end());
    std::sort(columns.begin(), columns.end());
    if (s == columns && pass) {
        return true;
    }
    if (parent != nullptr) {
        return parent->search(s, true);
    }
    return false;
}

std::tuple<bool, unsigned int, unsigned int> TreeNodeBackward::preWarn() {
    for (unsigned int x = 0; x < Global::numChilds * 2; x += 2) {
        if ((columns[Global::constraint[x]] == 2 * columns[Global::constraint[x + 1]] ||
             columns[Global::constraint[x + 1]] == 2 * columns[Global::constraint[x]]) &&
            Func::checkOtherIndep(Global::constraint[x], Global::constraint[x + 1], columns)) {
            return std::make_tuple(true, Global::constraint[x], Global::constraint[x + 1]);
        } else if (columns[Global::constraint[x]] == columns[Global::constraint[x + 1]]) {
            return std::make_tuple(true, Global::constraint[x], Global::constraint[x + 1]);
        } else if ((columns[Global::constraint[x]] == 3 * columns[Global::constraint[x + 1]] ||
                    columns[Global::constraint[x + 1]] == 3 * columns[x])) {
            return std::make_tuple(true, Global::constraint[x], Global::constraint[x + 1]);
        } else if (columns[Global::constraint[x]] > columns[Global::constraint[x + 1]] &&
                   columns[Global::constraint[x]] - columns[Global::constraint[x + 1]] ==
                   columns[Func::findOther(Global::constraint[x + 1], Global::constraint[x])]) {
            return std::make_tuple(true, Global::constraint[x], Global::constraint[x + 1]);
        } else if (columns[Global::constraint[x + 1]] > columns[Global::constraint[x]] &&
                   columns[Global::constraint[x + 1]] - columns[Global::constraint[x]] ==
                   columns[Func::findOther(Global::constraint[x], Global::constraint[x + 1])]) {
            return std::make_tuple(true, Global::constraint[x], Global::constraint[x + 1]);
        }
    }
    return std::make_tuple(false, 0, 0);
}