// repo.h

#ifndef REPO_H
#define REPO_H

#include <string>

class Repo
{
    string worktree = "";
    string gitdir = "";
public:
    Repo();
    Repo(string &path);
    void printRepo();
    string repoPath(Repo &repo, string &path);
    string repoDir(Repo &repo, string &path, bool mkdir);
    string repoFile(Repo &repo, string &path, bool mkdir);
    Repo createRepo(string &path);
    ~Repo();
};


#endif