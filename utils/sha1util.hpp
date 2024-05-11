#include <string>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

std::string computeSHA1(const std::string& data) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(reinterpret_cast<const unsigned char*>(data.c_str()), data.length(), hash);

    std::stringstream sha;
    sha << std::hex << std::setfill('0');
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        sha << std::setw(2) << static_cast<unsigned int>(hash[i]);
    }
    return sha.str();
}