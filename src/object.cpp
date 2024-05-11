#include "../include/object.h"
#include "../include/blob.h"
#include "../utils/sha1util.hpp"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

GitObject::GitObject(){
    std::cout<<"Repo object Initialised\n";
}

GitObject::GitObject(std::string data){
    std::cout<<"Repo object Initialised with data\n";
    if (!data.empty()) {
        this->deserialize(data);
    } else {
        this->init();
    }
}

std::string GitObject::serialize(){
    throw std::runtime_error("serialize Unimplemented!");
}
void GitObject::deserialize(const std::string &data){
    throw std::runtime_error("deserialize Unimplemented!");
}

GitObject* GitObject::ObjectRead(Repo *repo, const std::string &sha)
{
    std::string currPath = "objects/"+sha.substr(0, 2)+"/"+sha.substr(2);
    std::string path = repo->repoFile(repo, currPath.c_str());
    std::cout<<path;
    
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        return nullptr;
    }

    std::string raw;
    file.seekg(0, std::ios::end);
    raw.resize(file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(&raw[0], raw.size());

    // Decompress the data
    uLongf uncompressed_size = raw.size() * 2; // Initially assume uncompressed size could be twice the compressed size
    std::string uncompressed(uncompressed_size, 0);
    if (uncompress((Bytef*)&uncompressed[0], &uncompressed_size, (const Bytef*)raw.data(), raw.size()) != Z_OK) {
        throw std::runtime_error("Failed to decompress data");
    }
    uncompressed.resize(uncompressed_size);
    // object type
    size_t x = uncompressed.find(' ');
    std::string fmt = uncompressed.substr(0, x);
    // object size
    size_t y = uncompressed.find('\x00', x);
    size_t size = std::stoi(uncompressed.substr(x, y - x));
    if (size != uncompressed.size() - y - 1) {
        throw std::runtime_error("Malformed object " + sha + ": bad length");
    }
    GitObject* obj = nullptr;
    if (fmt == "blob") {
        obj = new GitBlob(raw.substr(y+1));
    }
    
    return obj;
}

std::string GitObject::ObjectWrite(GitObject *obj, Repo *repo){
    std::string data = obj->serialize();
    std::string result = obj->fmt + " " + std::to_string(data.size()) + '\x00' + data;
    
    std::string sha = computeSHA1(result);
    if(repo){
        std::string curPath = "objects/" + sha.substr(0, 2) + "/" + sha.substr(2);
        std::string path = repo->repoFile(repo, curPath.c_str(), true);

        if (path != "") {
            std::ofstream file(path, std::ios::binary);
            if (file.is_open()) {
                // Compress and write
                std::vector<unsigned char> compressed(result.begin(), result.end());
                compressed.push_back('\0'); // Add null terminator for zlib
                uLongf compressedSize = compressBound(compressed.size());
                std::vector<unsigned char> compressedData(compressedSize);
                if (compress(&compressedData[0], &compressedSize, &compressed[0], compressed.size()) == Z_OK) {
                    file.write(reinterpret_cast<char*>(&compressedData[0]), compressedSize);
                }
            }
        }
    }
    return sha;
}

std::string ObjectHash(std::ifstream& fd, const std::string& fmt, Repo *repo){
    std::string data((std::istreambuf_iterator<char>(fd)), (std::istreambuf_iterator<char>()));

    // Construct GitObject based on format
    GitObject* obj = nullptr;
    if (fmt == "blob")
        obj = new GitBlob(data);
    else
        throw std::runtime_error("Unknown type " + fmt);

    std::string sha = obj->ObjectWrite(obj, repo);
    delete obj;
    return sha;
}

void GitObject::init()
{
    std::cout<<"object base unimplemented";
}