#include "../include/repo.h"
#include <string>
#include <iostream>
#include <filesystem>

Repo::Repo(){
    std::cout<<"Repo object Initialised\n";
}

Repo::Repo(string &path){
    std::cout<<"Repo object Initialised with "<< path<<"\n";
    this->worktree = path;
    this->gitdir = (std::filesystem::path(path) / ".git").string();
}

void Repo::printRepo()
{
    //TODO: add this
    std::cout<<"worktree: "<<worktree<<"\n";
    std::cout<<"git dir: "<<gitdir<<"\n";
}

string Repo::repoPath(Repo &repo, string &path)
{
    return repo->gitdir + path;
}

string Repo::repoDir(Repo &repo, string &path, bool mkdir = false)
{
    if (std::filesystem::exists(path)) {
        if (std::filesystem::is_directory(path)) {
            return path;
        } else {
            throw std::runtime_error("Not a directory " + path);
        }
    }
    if (mkdir) {
        std::filesystem::create_directories(path); // Create directories recursively
        return path;
    } else {
        return ""; // Return empty string if directory doesn't exist and mkdir is false
    }
}

string Repo::repoFile(Repo &repo, string &path, bool mkdir = false)
{
    if(repoDir(repo, path[:-1], mkdir))
        return repoPath(repo, path);
    return NULL;
}

Repo Repo::createRepo(string &path){
    Repo r = new Repo(path);

    if (std::filesystem::exists(worktree)) {
        if (!std::filesystem::is_directory(worktree)) {
            throw std::runtime_error(worktree + " is not a directory!");
        }
        if (std::filesystem::exists(gitdir) && !std::filesystem::is_empty(gitdir)) {
            throw std::runtime_error(gitdir + " is not empty!");
        }
    } else {
        std::filesystem::create_directories(worktree);
    }

    assert(repoDir(r, "branches", true));
    assert(repoDir(r, "objects", true));
    assert(repoDir(r, "refs", "tags", true));
    assert(repoDir(r, "refs", "heads", true));
    return r;
}

Repo::~Repo()
{
    this->worktree = NULL;
    this->gitdir = NULL;
}
