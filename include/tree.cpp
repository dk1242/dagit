#include "tree.h"
#include <iostream>

GitTree::GitTree()
{
    std::cout<<"Tree object Initialised\n";
}

GitTree::GitTree(const std::string &data)
{
    std::cout<<"Tree object Initialised with data\n";
}

std::string GitTree::serialize()
{
    return this->leaf->tree_serialize(this->items);
}

void GitTree::deserialize(std::string &data){
    this->items = this->leaf->treeParse(data);
}
