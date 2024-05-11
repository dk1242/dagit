#include "../include/commitobj.h"
#include "../utils/kvlm.hpp"
#include <iostream>

GitCommit::GitCommit(){
    std::cout<<"Commit object Initialised\n";

    this->fmt = "commit";
    this->kvlm.clear();
}
std::string GitCommit::serialize(){
    return kvlm_serialize(this->kvlm);
}
void GitCommit::deserialize(const std::string &data){
    std::unordered_map<std::string, std::vector<std::string>>* dct = new std::unordered_map<std::string, std::vector<std::string>>();
    this->kvlm = kvlm_parse(data.c_str(),0, *dct);
}