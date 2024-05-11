// object.h

#ifndef OBJECT_H
#define OBJECT_H

#include "repo.h"
#include <map>
#include <string>
#include <zlib.h>

class GitObject
{
    std::string data;
    const std::string fmt = "object";
public:
    GitObject();
    GitObject(std::string data);
    virtual std::string serialize();
    virtual void deserialize(const std::string &data);
    virtual void init();
    GitObject* ObjectRead(Repo *repo, const std::string& sha);
    std::string ObjectWrite(GitObject *obj, Repo *repo = NULL);
    std::string ObjectHash(std::ifstream& fd, const std::string& fmt, Repo *repo = NULL);
};

#endif