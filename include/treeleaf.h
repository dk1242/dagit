#include <string>
#include <vector>

class GitTreeLeaf{
    std::string path;
    std::string mode;
    std::string sha;
public:
    GitTreeLeaf(std::string path, std::string mode, std::string sha);
    std::pair<size_t, GitTreeLeaf*>treeParseOne(std::string &raw, size_t start = 0);
    std::vector<GitTreeLeaf*>treeParse(std::string &raw);
    std::string tree_leaf_sort_key() const;
    std::string tree_serialize(std::vector<GitTreeLeaf*>& items);
};