#include "../include/repo.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <cassert>
using namespace std;
Repo::Repo(){
    std::cout<<"Repo object Initialised\n";
}

Repo::Repo(char* &path){
    std::cout<<"Repo object Initialised with "<< path<<"\n";
    this->worktree = path;
    this->gitdir = (std::filesystem::path(path) / "git").string();
}

void Repo::printRepo()
{
    //TODO: add this
    std::cout<<"worktree: "<<worktree<<"\n";
    std::cout<<"git dir: "<<gitdir<<"\n";
}

string Repo::repoPath(Repo &repo, char* &path)
{
    return repo.gitdir + path;
}

string Repo::repoDir(Repo &repo, const char* path, bool mkdir = false)
{
    if (std::filesystem::exists(path)) {
        if (std::filesystem::is_directory(path)) {
            return path;
        } else {
            throw std::runtime_error("Not a directory " + string(path));
        }
    }
    if (mkdir) {
        std::filesystem::create_directories(path); // Create directories recursively
        return path;
    } else {
        return ""; // Return empty string if directory doesn't exist and mkdir is false
    }
}

string Repo::repoFile(Repo &repo, char* &path, bool mkdir = false)
{
    string rPath = string(path);
    rPath = rPath.substr(0, rPath.size()-1);

    if(repoDir(repo, rPath.c_str(), mkdir) != "")
        return repoPath(repo, path);
    return NULL;
}

void Repo::createRepo(Repo &repo, char* &path){
    std::cout<<"worktree";
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

    repoDir(repo, "branches", true);
    repoDir(repo, "objects", true);
    // assert(repoDir(r, "refs", "tags", true));
    // assert(repoDir(r, "refs", "heads", true));
    // return repo;
}

Repo::~Repo()
{
    this->worktree = "";
    this->gitdir = "";
}
