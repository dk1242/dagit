#include "../include/repo.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <cassert>
#include <fstream>

using namespace std;
Repo::Repo(){
    std::cout<<"Repo object Initialised\n";
}

Repo::Repo(const char* path){
    std::cout<<"Repo object Initialised with "<< path<<"\n";
    this->worktree = path;
    this->gitdir = (std::filesystem::path(path) / "gitf").string();
    // cout<<gitdir<<"\n";
}

void Repo::printRepo()
{
    //TODO: add this
    std::cout<<"worktree: "<<worktree<<"\n";
    std::cout<<"git dir: "<<gitdir<<"\n";
}

string Repo::repoPath(Repo *repo, const char* path)
{
    return repo->gitdir + path;
}

string Repo::repoDir(Repo *repo, const char* path, bool mkdir)
{   
    // cout<<path<<"\n";
    if (std::filesystem::exists(repo->gitdir + path)) {
        if (std::filesystem::is_directory(repo->gitdir + path)) {
            return repo->gitdir + path;
        } else {
            throw std::runtime_error("Not a directory " + string(path));
        }
    }
    if (mkdir) {
        std::filesystem::create_directories(repo->gitdir + path); // Create directories recursively
        return repo->gitdir + path;
    } else {
        return ""; // Return empty string if directory doesn't exist and mkdir is false
    }
}

string Repo::repoFile(Repo *repo, const char* path, bool mkdir)
{
    string rpath = string(path);
    size_t first_pos = rpath.find_first_of('/');
    size_t last_pos = rpath.find_last_of('/');
    if (first_pos != std::string::npos && last_pos != std::string::npos) {
        rpath = rpath.substr(first_pos, last_pos - first_pos + 1);
    } else {
        rpath = "";
    }
    if(repoDir(repo, rpath.c_str(), mkdir) != "")
        return repoPath(repo, path);
    return "";
}

void Repo::createRepo(Repo *repo, const char* path){
    
    if (std::filesystem::exists(repo->gitdir)) {
        if (!std::filesystem::is_directory(repo->gitdir)) {
            throw std::runtime_error(string(path) + " is not a directory!");
        }
        // if (std::filesystem::exists(repo.gitdir) && !std::filesystem::is_empty(repo.gitdir)) {
        //     throw std::runtime_error(repo.gitdir + " is not empty!");
        // }
    } else {
        std::filesystem::create_directories(repo->gitdir);
    }

    repoDir(repo, "/branches", true);
    repoDir(repo, "/objects", true);
    repoDir(repo, "/refs/tags", true);
    repoDir(repo, "/refs/heads", true);

    std::string filename = repoFile(repo, "/HEAD");
    std::ofstream f(filename);
    if (f.is_open()) {
        f << "ref: refs/heads/master\n";
        f.close();
        // std::cout << "File written successfully.\n";
    }
    // return repo;
}

Repo* Repo::findRepo(const char* path, bool required){
    namespace fs = std::filesystem;

    fs::path current_path = fs::absolute(path);

    while (true) {
        fs::path git_dir = current_path / ".git";
        string curr = git_dir;
        if (fs::is_directory(git_dir)) {
            // @TODO: need to find something different solution 
            Repo* curRepo = new Repo(curr.c_str());
            return curRepo;
        }

        fs::path parent_path = current_path.parent_path();
        if (parent_path == current_path) {
            if (required) {
                throw std::runtime_error("No git directory.");
            } else {
                return nullptr; // Assuming GitRepository has a default constructor
            }
        }

        current_path = parent_path;
    }
}

Repo::~Repo()
{
    this->worktree = "";
    this->gitdir = "";
}
