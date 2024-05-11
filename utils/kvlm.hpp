#include <iostream>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <cassert>

std::unordered_map<std::string, std::vector<std::string>> kvlm_parse(const char* raw, int start, 
    std::unordered_map<std::string, std::vector<std::string>>& dct){
    if(dct.empty()){
        dct["!!!!!"]={};
    }
    // base case
    if (raw[start] == '\n' || raw[start] == '\0') {
        if (raw[start] == '\n')
            ++start; // Move past the newline
        std::vector<std::string> message;
        message.emplace_back(raw + start); // Store the message
        dct[std::string()] = message; // None key stores the message
        return dct;
    }
    int spc = -1; // Position of the next space
    int nl = -1;  // Position of the next newline

    // Finding the next space and newline
    const char* spacePtr = strchr(raw + start, ' ');
    if (spacePtr != nullptr)
        spc = spacePtr - raw;
    const char* nlPtr = strchr(raw + start, '\n');
    if (nlPtr != nullptr)
        nl = nlPtr - raw;
    if (spc < 0 || (nl >= 0 && nl < spc)) {
        assert(nl == start); // Ensure it's a blank line
        if (nl == start + 1) // If newline is right after start, means empty line
            ++start; // Move past the newline
        std::vector<std::string> message;
        message.emplace_back(raw + start); // Store the message
        dct[std::string()] = message; // None key stores the message
        return dct;
    }
    std::string key(raw + start, spc - start);

    // Find the end of the value
    int end = start;
    while (true) {
        end = strchr(raw + end + 1, '\n') - raw;
        if (raw[end + 1] != ' ') break;
    }
    std::string value(raw + spc + 1, end - spc - 1);

    // Drop the leading space on continuation lines
    size_t pos;
    while ((pos = value.find("\n ")) != std::string::npos) {
        value.replace(pos, 2, "\n");
    }

    // Store key-value pair
    if (dct.find(key) != dct.end()) {
        dct[key].emplace_back(value); // If key already exists, add value to the list
    } else {
        std::vector<std::string> values;
        values.emplace_back(value);
        dct[key] = values;
    }

    // Recurse for next key-value pair
    return kvlm_parse(raw, end + 1, dct);
}

std::string kvlm_serialize(const std::unordered_map<std::string, std::vector<std::string>>& kvlm) {
    std::string ret;

    // Output fields
    for (const auto& pair : kvlm) {
        // Skip the message itself
        if (pair.first.empty()) continue;
        const std::vector<std::string>& values = pair.second;
        for (const auto& v : values) {
            ret += pair.first + " " + v + "\n";
        }
    }

    // Append message
    ret += "\n" + kvlm.at("")[0] + "\n";

    return ret;
}