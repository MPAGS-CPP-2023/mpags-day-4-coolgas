#ifndef MPAGSCIPHER_PLAYFAIRCIPHER_HPP
#define MPAGSCIPHER_PLAYFAIRCIPHER_HPP

#include "CipherMode.hpp"

#include <string>
#include <map>

/**
 * \file PlayfairCipher.hpp
 * \brief Contains the declaration of the PlayfairCipher class
*/

/**
 * \class PlayfairCipher
 * \brief Encrypt or decrypt text using the Playfair cipher with the given key
*/

class PlayfairCipher
{
public:
    /**
     * \brief Create a new PlayfairCipher with the given key
     * 
     * \param key the string used to construct the 5x5 key table
    */
    explicit PlayfairCipher(const std::string& key);

    /**
     * \brief Apply the cipher to the provided text
     * 
     * \param inputText the text to encrypt or decrypt
     * \param cipherMode whether to encrypt or decrypt the input text
     * \return the result of applying the cipher to the input text
    */
    std::string applyCipher(const std::string& inputText, const CipherMode cipherMode) const;

private:
    std::string key_{""};
    std::map<char, std::pair<std::size_t, std::size_t>> str2coords_;
    std::map<std::pair<std::size_t, std::size_t>, char> coords2str_;

    void setKey_(const std::string& key);
};

#endif
