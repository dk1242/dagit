// blob.h

#ifndef BLOB_H
#define BLOB_H

#include "repo.h"
#include "object.h"

class GitBlob: public GitObject{
    std::string blobData;
    const std::string fmt = "blob";
public:
    GitBlob();
    GitBlob(const std::string& data);
    std::string serialize();
    void deserialize(const std::string &data);
};

#endif