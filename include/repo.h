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
    Repo(char* &path);
    void printRepo();
    std::string repoPath(Repo &repo, char* &path);
    std::string repoDir(Repo &repo, const char* path, bool mkdir);
    std::string repoFile(Repo &repo, char* &path, bool mkdir);
    void createRepo(Repo &repo, char* &path);
    ~Repo();
};


#endif