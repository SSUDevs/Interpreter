#ifndef INTERPRETER_FILEASARRAY_H
#define INTERPRETER_FILEASARRAY_H

#include <string>
#include<fstream>
#include<vector>
#include <iostream>

/// Preliminary for removing comments and storing into vector of chars
class fileAsArray {
public:

    // Using an Enum to represent the states of the finite state automaton
    enum State {
        START,                // Initial state (Also accepting state)
        SLASH,                // State after finding '/'
        LINE_COMMENT,         // State after finding '//'
        BLOCK_COMMENT,        // State after finding '/*'
        ENDING_BLOCK_COMMENT, // State after finding '*/'
        SINGLE_QUOTE,         // Ensures whats in quotes remains untouched
        DOUBLE_QUOTE,         // Ensures whats in quotes remains untouched
    };

    fileAsArray(std::string fileName);

    void readFile();

    void File_w_no_comments(); // Parses the vector of chars to remove comments

    // Returns the index following the Division Op. and if it was div.
    std::pair<bool, int> isDivision(int index);

    // Method to get a reference to the vector in the main
    const std::vector<char>& getFileContent() const {
        return file;
    }

    void printVector();

private:
    std::vector<char> file;
    int errorLineNumber; // Keeps track of line number during parsing when error found
    std::ifstream inputStream;
    std::string inputFileName;
};


#endif //INTERPRETER_FILEASARRAY_H