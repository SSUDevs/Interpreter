#include "fileAsArray.h"

fileAsArray::fileAsArray(std::string fileName) {
    inputStream.open(fileName, std::ios::in);
    inputFileName = fileName;
    errorLineNumber = 1;
}

void fileAsArray::readFile() {

    if (!inputStream.is_open()) {
        std::cout
            << "Tokenizer::getToken() called with a stream that is not open."
            << std::endl;
        std::cout << "Make sure that " << inputFileName
                  << " exists and is readable. Terminating.";
        exit(2);
    }

    char c;

    while (inputStream.get(c) && !inputStream.eof()) {
        // std::cout << c;
        file.push_back(c);
    }

    inputStream.close();
    // std::cout << "Done reading File" << std::endl;
}

/*
 Mutates the original vector stored as a private variable 'file'
 by a looping through indices and comparing the states enumerated
 within the class 'fileAsArray'
 */
void fileAsArray::File_w_no_comments() {
    State state =
        START; // Initialize the state to START (Also the accepting state)
    int lineNumber = 1; // Keeps track of line number during parsing

    // Iterate through each character in the file
    for (int i = 0; i < file.size(); i++) {
        if (file[i] == '\n')
            lineNumber++;
        switch (state) {
        case START:
            // If quote is found then all within must remain untouched
            if (file[i] == '\'') {
                errorLineNumber = lineNumber; // Save in case error
                state = SINGLE_QUOTE;
            } else if (file[i] == '"') {
                errorLineNumber = lineNumber; // Save in case error
                state = DOUBLE_QUOTE;
            } else if (file[i] ==
                       '/') { // Check for the beginning of a potential comment
                // First check if division and if true then don't replace with
                // space
                errorLineNumber = lineNumber; // Save in case error
                std::pair<bool, int> result = isDivision(i);
                if (result.first) { // If Division Operation then start index at
                                    // new index
                    i = result.second;
                    state = START; // Move state back to START
                } else {
                    // If not Division then continue in SLASH state and replace
                    // with space
                    errorLineNumber = lineNumber; // Save in case error
                    file[i] = ' '; // Replace the '/' with whitespace
                    state = SLASH; // Update state to reflect comment
                }
            } // Existing code for handling quotes and potential comments...
            else if (file[i] == '*') {
                // Peek next character to check for multiplication
                std::pair<bool, int> multiplicationCheckResult =
                    isMultiplication(i);
                if (multiplicationCheckResult.first) {
                    // It's a multiplication operation; do not modify 'i' as you
                    // want to keep the '*' You might want to skip to the next
                    // significant character, but it's crucial to handle the '*'
                    // correctly in the context of your application
                    i = multiplicationCheckResult.second -
                        1; // Adjust 'i' as needed
                    // No need to change the state or modify the file content
                    // here
                } else {
                    // Handle as previously, including potential error reporting
                    throw std::runtime_error("ERROR: Program contains C-style, "
                                             "Block comment not started " +
                                             std::to_string(lineNumber));
                }
            } 
            break;

        case SLASH:
            // Check if it is a valid comment ('//')
            if (file[i] == '/') {
                state = LINE_COMMENT; // Move to the LINE_COMMENT state if '//'
                                      // is found
                file[i] = ' ';        // Replace the second '/' with whitespace
            } else if (file[i] == '*') {
                state = BLOCK_COMMENT; // Move to the BLOCK_COMMENT state if
                                       // '/*' is found
                file[i] = ' ';         // Replace the first '/' with whitespace
            } else {
                //////// Report error if '/' found not proceeded by another '/'
                //////////
                throw std::runtime_error("ERROR: Program contains C-style, "
                                         "incomplete line comment on line " +
                                         std::to_string(errorLineNumber));
            }
            break;

        case LINE_COMMENT:
            // Replace characters with whitespace until the end of the line
            if (file[i] == '\n') {
                state = START; // Move back to the START state after finding a
                               // newline
            } else {
                file[i] = ' '; // Replace characters within the comment with
                               // whitespace
            }
            break;

        case BLOCK_COMMENT:
            // Replace characters with whitespace until next '*' is found
            if (file[i] == '*') {
                state =
                    ENDING_BLOCK_COMMENT; // Move to the ENDING_BLOCK_COMMENT
                                          // state after finding a star
                file[i] = ' '; // Replace characters within the comment with
                               // whitespace
            } else {
                file[i] = ' '; // Replace characters within the comment with
                               // whitespace
            }
            break;

            // Once in 'BLOCK_COMMENT' state and finding '*', now check for the
            // ending of a BLOCK_COMMENT
        case ENDING_BLOCK_COMMENT:
            // Check if it's been ended by '/', else continue replacing for
            // space
            if (file[i] == '/') {
                state = START; // Move to the START state after finding a slash
                               // during ENDING_BLOCK_COMMENT
                file[i] = ' '; // Replace characters within the comment with
                               // whitespace
            } else if (file[i] != '\n') {
                file[i] = ' '; // Replace characters within the comment with
                               // whitespace
            }
            break;

        case SINGLE_QUOTE:
            // Check if end quote has been found and if so change state back to
            // 'START'
            if (file[i] == '\'') {
                state = START; // Move back to the START state after finding end
                               // quote
            } 
            break;

        case DOUBLE_QUOTE:
            // Check if end quote has been found and if so change state back to
            // 'START'
            if (file[i] == '"') {
                state = START; // Move back to the START state after finding end
                               // quote
            } 
            break;
        }
    }
    // Checks Ending state to ensure its accepted
    if (state != START) {
        //////// Should report error if ending state is not accepting i.e. START
        //////////
        throw std::runtime_error("ERROR: Program contains C-style, incomplete "
                                 "block comment on line " +
                                 std::to_string(errorLineNumber));
    }
}

// Function used to see if the * is acually being used for Multiplication
std::pair<bool, int> fileAsArray::isMultiplication(int index) {
    size_t length = file.size();
    index++;                                         // Move past the asterisk
    while (index < length && isspace(file[index])) { // Skip the whitespac
        index++;
    }
    if (index < length && isdigit(file[index])) { // If next is digit
        return std::make_pair(true, index + 1); // Return true, and must be mult
    }
    return std::make_pair(false, index); // Not a mult thus error
}

// Checks if '/' is division and returns the index of next character found and
// whether is Division or not
std::pair<bool, int> fileAsArray::isDivision(int index) {
    size_t length = file.size();
    // Iterate through each character in the file
    while (index < length) {
        index++;
        // If a space then continue looping
        if (isspace(file[index])) {
            continue;
        }
        if (isdigit(file[index])) {             // check if next is a number
            return std::make_pair(true, index); // Return true if Division Op.
        } else
            return std::make_pair(false, index);
    }
    return std::make_pair(false, index);
}

// Print the vector stored as a private variable within the class 'fileAsArray'
void fileAsArray::printVector() {
    for (char c : file) {
        std::cout << c;
    }
}