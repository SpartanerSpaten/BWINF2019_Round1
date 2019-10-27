//
// Created by worker on 10/21/19.
//

#ifndef TELEPAARTIE2_TREENODE_HPP
#define TELEPAARTIE2_TREENODE_HPP


#include <memory>

#define COLUMNS 3

namespace Global {
    static unsigned int numChilds;
    static uint16_t *constraint;
}

#include "functions.hpp"

class TreeNode {
public:
    virtual void move(unsigned int, unsigned int) = 0;

    virtual void generateChildren() = 0;

    virtual std::tuple<bool, unsigned int, unsigned int> preWarn() = 0;

    static void init();

    void setColls(std::vector<unsigned int> &x) {
        columns = x;
    }

    TreeNode *operator[](int index) {
        return children[index];
    }

    TreeNode *getParent() {
        return parent;
    }

protected:

    std::vector<TreeNode *> children;
    TreeNode *parent;
    std::vector<unsigned int> columns;

    size_t childs;

};

class TreeNodeForward : public TreeNode {
public:
    explicit TreeNodeForward(TreeNodeForward *);

    TreeNodeForward(TreeNodeForward *, std::vector<unsigned int> &);

    TreeNodeForward();

    ~TreeNodeForward();

    void move(unsigned int, unsigned int) override;

    void generateChildren() override;

    std::tuple<bool, unsigned int, unsigned int> preWarn() override;

    TreeNodeForward *finish();

    std::ostream &operator<<(std::ostream &os);

    friend std::ostream &operator<<(std::ostream &os, const TreeNodeForward &obj);

    void insertChildren(std::vector<TreeNodeForward *> &insertInto) {
        insertInto.insert(insertInto.end(), children.begin(), children.end());
    }

    TreeNodeForward *getParent() {
        return parent;
    }

protected:
    TreeNodeForward *easyTeleport(TreeNodeForward *o, std::vector<unsigned int> &, uint16_t x, uint16_t y);

    std::vector<TreeNodeForward *> children;
    TreeNodeForward *parent;
    std::vector<unsigned int> columns;

    size_t childs;

};


class TreeNodeBackward : public TreeNode {
public:
    TreeNodeBackward();

    TreeNodeBackward(TreeNodeBackward *);

    TreeNodeBackward(TreeNodeBackward *, std::vector<unsigned int> &);

    ~TreeNodeBackward();


    void move(unsigned int, unsigned int, bool);

    void move(unsigned int, unsigned int);

    void generateChildren() override;

    std::tuple<bool, unsigned int, unsigned int> preWarn() override;

    TreeNodeBackward *finish();

    bool search(std::vector<unsigned int> &, bool);

    void advancedMove(unsigned int, unsigned int);

    void insertChildren(std::vector<TreeNodeBackward *> &insertInto) {
        insertInto.insert(insertInto.end(), children.begin(), children.end());
    }

    unsigned int getChilds() {
        return childs;
    }

    std::vector<unsigned int> getColumns() {
        return columns;
    }

    friend std::ostream &operator<<(std::ostream &os, const TreeNodeBackward &obj);

protected:
    TreeNodeBackward *parent;
    std::vector<TreeNodeBackward *> children;
};

#endif //TELEPAARTIE2_TREENODE_HPP
