#include "PlayfairCipher.hpp"

#include <map>
#include <string>
#include <iostream>
#include <algorithm>

PlayfairCipher::PlayfairCipher(const std::string& key) : key_{""}
{
   this->setKey_(key);
}

void PlayfairCipher::setKey_(const std::string& key)
{   
    // store the original key
    key_ = key;

    // Append the alphabet
    key_ += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Make sure the key is upper case
    std::transform( key_.begin(), key_.end(),
                    key_.begin(), ::toupper );

    // Remove non-alpha characters
    key_.erase( std::remove_if(key_.begin(), key_.end(), [](char c){ return !std::isalpha(c); }), 
                key_.end() );

    // Change J -> I
    std::transform( key_.begin(),  key_.end(),
                    key_.begin(), [](char c){ return (c=='J') ? 'I' : c ;});

    // Remove duplicated letters
    std::string lettersFound{""};
    auto detectDuplicates = [&](char c) {
        if (lettersFound.find(c) == std::string::npos) {
            lettersFound += c;
            return false;
        } else {
            return true;
        }
    };

    key_.erase( std::remove_if(key_.begin(), key_.end(), detectDuplicates), key_.end() );

    // Store the coords of each letter
    for (std::size_t i = 0; i < 25; i++) {
        std::size_t col_idx = i % 5;
        std::size_t row_idx = (i-col_idx)/5;
        auto p1{ std::make_pair(row_idx, col_idx) };
        auto p2{ std::make_pair(key_[i], p1) };
        str2coords_.insert(p2);
    }

    // Store the playfair cihper key map
    for (std::size_t i = 0; i < 25; i++) {
        for (std::size_t j = 0; j < 25; j++) {
            std::size_t idx = i * 5 + j;
            auto p1{ std::make_pair(i, j) };
            auto p2{ std::make_pair(p1, key_[idx])};
            coords2str_.insert(p2);
        }
    }
}

std::string PlayfairCipher::applyCipher(const std::string& inputText, const CipherMode cipherMode) const
{

    // Change J → I

    // If repeated chars in a digraph add an X or Q if XX

    // if the size of input is odd, add a trailing Z

    // Loop over the input in Digraphs

    // - Find the coords in the grid for each digraph

    // - Apply the rules to these coords to get 'new' coords

    // - Find the letter associated with the new coords


    switch (cipherMode)
    {
    case CipherMode::Encrypt:
        std::cout << "Test encryption can be called" <<std::endl;
        break;
    case CipherMode::Decrypt:
        std::cout << "Test decryption can be called" <<std::endl;
        break;
    default:
        break;
    }
    
    // return the text
    return inputText;
}

