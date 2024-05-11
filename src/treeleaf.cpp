#include "../include/treeleaf.h"
#include <cassert>
#include <sstream>
#include <algorithm>

GitTreeLeaf::GitTreeLeaf(std::string path, std::string mode, std::string sha){
    this->path = path;
    this->mode = mode;
    this->sha = sha;
}
std::pair<size_t, GitTreeLeaf*> GitTreeLeaf::treeParseOne(std::string &raw, size_t start)
{
    size_t x = raw.find(' ', start);
    assert(x - start == 5 || x - start == 6);
    std::string mode = raw.substr(start, x - start);
    if (mode.length() == 5) {
        // Normalize to six bytes
        mode = " " + mode;
    }
    size_t y = raw.find('\0', x);
    assert(y != std::string::npos);
    std::string path = raw.substr(x + 1, y - x - 1);

    std::string sha = "";
    // Todo: It can be done with substr
    for (size_t i = y + 1; i < y + 21; ++i) {
        sha += raw[i];
    }
    GitTreeLeaf* obj = new GitTreeLeaf(mode, path, sha);
    return {y + 21, obj};
}

std::vector<GitTreeLeaf*> GitTreeLeaf::treeParse(std::string &raw)
{
    size_t pos = 0;
    size_t maxl = raw.length();
    std::vector<GitTreeLeaf*>res;
    while(pos<maxl){
        auto it = treeParseOne(raw, pos);
        pos = it.first;
        res.push_back(it.second);
    }
    return res;
}
std::string GitTreeLeaf::tree_leaf_sort_key() const
{
    if (this->mode.find("10") == 0) {
        return this->path;
    } else {
        return this->path + "/";
    }
}

std::string GitTreeLeaf::tree_serialize(std::vector<GitTreeLeaf*> &items)
{
    std::vector<GitTreeLeaf*> sorted_items = items;
    std::sort(sorted_items.begin(), sorted_items.end(), [](const GitTreeLeaf* a, const GitTreeLeaf* b) {
        return a->tree_leaf_sort_key() < b->tree_leaf_sort_key();
    });

    // Serialize sorted items
    std::stringstream ss;
    for (const auto& item : sorted_items) {
        ss << item->mode << " " << item->path << '\0' << item->sha;
    }
    return ss.str();
}
