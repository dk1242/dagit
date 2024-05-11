#include "../include/blob.h"
#include <iostream>

using namespace std;

GitBlob::GitBlob(){
    std::cout<<"Blob object Initialised\n";
}

GitBlob::GitBlob(const std::string& data) : GitObject(data){
    std::cout<<"Blob object Initialised with data\n";
}

std::string GitBlob::serialize(){
    return this->blobData;
}
void GitBlob::deserialize(const std::string &data){
    // Todo set correct val
    this->blobData = data;
}