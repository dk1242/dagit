#include "object.h"
#include "treeleaf.h"
#include <string>
#include <vector>

class GitTree: public GitObject{
    const std::string fmt = "tree";
    std::vector<GitTreeLeaf*>items;
    GitTreeLeaf* leaf;
public:
    GitTree();
    GitTree(const std::string& data);
    std::string serialize();
    void deserialize(std::string &data);
};