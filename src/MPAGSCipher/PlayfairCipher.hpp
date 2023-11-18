#ifndef MPAGSCIPHER_PLAYFAIRCIPHER_HPP
#define MPAGSCIPHER_PLAYFAIRCIPHER_HPP

#include "CipherMode.hpp"

#include <string>
#include <map>

class PlayfairCipher
{
private:
    std::string key_{""};
    std::map<char, std::pair<std::size_t, std::size_t>> str2coords_;
    std::map<std::pair<std::size_t, std::size_t>, char> coords2str_;

    void setKey_(const std::string& key);
public:
    explicit PlayfairCipher(const std::string& key);
    std::string applyCipher(const std::string& inputText, const CipherMode cipherMode) const;

};

#endif
