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
    for (std::size_t i = 0; i < key_.length(); i++) {
        std::size_t col_idx = i % 5;
        std::size_t row_idx = (i-col_idx)/5;
        auto p1{ std::make_pair(row_idx, col_idx) };
        auto p2{ std::make_pair(key_[i], p1) };
        str2coords_.insert(p2);
    }

    // Store the playfair cihper key map
    for (std::size_t i = 0; i < 5; i++) {
        for (std::size_t j = 0; j < 5; j++) {
            std::size_t idx = i * 5 + j;
            auto p1{ std::make_pair(i, j) };
            auto p2{ std::make_pair(p1, key_[idx])};
            coords2str_.insert(p2);
        }
    }
}

std::string PlayfairCipher::applyCipher(const std::string& inputText, const CipherMode cipherMode) const
{
    using coord = std::pair<std::size_t, std::size_t>; // Customized type for coordinates

    std::string input = inputText;
    std::string digraphs{""};
    std::string processed_input{""};

    // Change J → I
    std::transform( input.begin(), input.end(), 
                    input.begin(), [](char c){ return (c=='J') ? 'I' : c; } );

    // If repeated chars in a digraph add an X or Q if XX
    for ( size_t i = 0; i < input.length()-1; i += 2 ) {
        char first = input[i];
        char second = input[i+1];
        if ( first == second ) {
            second = (second == 'X') ? 'Q' : 'X';
            i--; // Decrement i to repeat the current letter
        }
        digraphs += first;
        digraphs += second;
    }

    // if the size of input is odd, add a trailing Z
    if ( digraphs.length() % 2 != 0 ) {
        digraphs += 'Z';
    }
    
    // Loop over the input in Digraphs
    for ( size_t i = 0; i < digraphs.length()-1; i += 2 ) {
        char first = digraphs[i];
        char second = digraphs[i+1];

        //  - Find the coords in the grid for each digraph
        auto iter1 = str2coords_.find(first);
        auto iter2 = str2coords_.find(second);
        coord coord1 = (*iter1).second;
        coord coord2 = (*iter2).second;

        coord coord1_new;
        coord coord2_new;
        
        //  - Apply the rules to these coords to get 'new' coords
        std::size_t x1 = coord1.first;
        std::size_t y1 = coord1.second;
        std::size_t x2 = coord2.first;
        std::size_t y2 = coord2.second;

        std::size_t new_x1{0};
        std::size_t new_y1{0};
        std::size_t new_x2{0};
        std::size_t new_y2{0};

        switch (cipherMode)
        {
        case CipherMode::Encrypt:
            if (x1 == x2) {
                new_y1 = (y1+1)%5;
                new_y2 = (y2+1)%5;
                coord1_new = std::make_pair(x1, new_y1);
                coord2_new = std::make_pair(x2, new_y2);
            }else if (y1 == y2) {
                new_x1 = (x1+1)%5;
                new_x2 = (x2+1)%5;
                coord1_new = std::make_pair(new_x1, y1);
                coord2_new = std::make_pair(new_x2, y2);
            } else {
                coord1_new = std::make_pair(x1, y2);
                coord2_new = std::make_pair(x2, y1);
            }
            break;
        case CipherMode::Decrypt:
            if (x1 == x2) {
                new_y1 = (y1+4)%5;
                new_y2 = (y2+4)%5;
                coord1_new = std::make_pair(x1, new_y1);
                coord2_new = std::make_pair(x2, new_y2);
            }else if (y1 == y2) {
                new_x1 = (x1+4)%5;
                new_x2 = (x2+4)%5;
                coord1_new = std::make_pair(new_x1, y1);
                coord2_new = std::make_pair(new_x2, y2);
            } else {
                coord1_new = std::make_pair(x1, y2);
                coord2_new = std::make_pair(x2, y1);    
            }
            break;   
        default:
            break;
        }
        //  - Find the letter associated with the new coords
        auto iter1_new = coords2str_.find(coord1_new);
        auto iter2_new = coords2str_.find(coord2_new);
        processed_input += (*iter1_new).second;
        processed_input += (*iter2_new).second;
    }
    
    // return the text
    return processed_input;
}

