//
// Created by Luis carmona on 2/8/24.
//

#ifndef ASSIGNMENT1_460_FILEASARRAY_H
#define ASSIGNMENT1_460_FILEASARRAY_H
#include <string>
#include<fstream>
#include<vector>
#include <iostream>


class fileAsArray {
public:
    /// May be moved to Tokenizer, However since we are just using this as a preliminary
    /// for removing comments it's probably fine ///
    // Using an Enum to represent the states of the finite state automaton
    enum State {
        START,                // Initial state (Also accepting state)
        SLASH,                // State after finding '/'
        LINE_COMMENT,         // State after finding '//'
        BLOCK_COMMENT,        // State after finding '/*'
        ENDING_BLOCK_COMMENT, // State after finding '*/'
        DIVISION,             // State after finding '/' and making sure it's not Division Op.
        QUOTE,                // Ensures whats in quotes remains untouched
    };

    fileAsArray(std::string fileName);
    void readFile();

    void File_w_no_comments(); // Parses the vector of chars to remove comments

    // Returns the index following the Division Op. and if it was div.
    std::pair<bool, int> isDivision(int index);
    void printVector();

private:
    std::vector<char> file;
    std::ifstream inputStream;
    std::string inputFileName;
};


#endif //ASSIGNMENT1_460_FILEASARRAY_H
