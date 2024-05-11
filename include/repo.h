// repo.h

#ifndef REPO_H
#define REPO_H

#include <string>

class Repo
{
    std::string worktree = "";
    std::string gitdir = "";
public:
    Repo();
    Repo(const char* path);
    void printRepo();
    std::string repoPath(Repo *repo, const char* path);
    std::string repoDir(Repo *repo, const char* path, bool mkdir = false);
    std::string repoFile(Repo *repo, const char* path, bool mkdir = false);
    void createRepo(Repo *repo, const char* path);
    Repo* findRepo(const char* path = ".", bool required = true);
    ~Repo();
};


#endif