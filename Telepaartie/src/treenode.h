//
// Created by worker on 9/26/19.
//

#ifndef BWINF19_TREENODE_H
#define BWINF19_TREENODE_H

#include <vector>
#include <tuple>
#include <cmath>
#include <cstring>

#define COLLUMNS 3

static unsigned int numchilds;
static uint16_t * constraint ;

class TreeNode {
public:
    TreeNode(TreeNode*);
    TreeNode(TreeNode*, unsigned int[COLLUMNS]);
    ~TreeNode();

    // for easy stdout piping
    std::ostream& operator<<(std::ostream&);

    // teleports something creates new Tree Node
    //TreeNode * teleport(uint16_t, uint16_t);

    // check is something found, index, index
    std::tuple<bool, uint16_t , uint16_t > check();

    void random();

    void generate_childs();

    TreeNode * finish();

    static void init();

    int teleport(uint16_t, uint16_t);

    void setcolls(unsigned int x[COLLUMNS]){
        memcpy(colls, x, sizeof(int) * COLLUMNS);
    }

    std::vector<TreeNode*> children;
    TreeNode * parent;

protected:

    unsigned int colls[COLLUMNS];

    size_t childs, constraints;

};


#endif //BWINF19_TREENODE_H
