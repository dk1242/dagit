#include "object.h"
#include <unordered_map>
#include <vector>

class GitCommit : public GitObject {
private:
    std::string fmt;
    std::unordered_map<std::string, std::vector<std::string>> kvlm;

public:
    // Constructor
    GitCommit();
    std::string serialize();
    void deserialize(const std::string &data);
};