//
// Created by Luis carmona on 2/8/24.
//

#include "fileAsArray.h"


fileAsArray::fileAsArray(std::string fileName) {
    inputStream.open(fileName, std::ios::in);
    inputFileName= fileName;

}

void fileAsArray::readFile(){

    if( ! inputStream.is_open()) {
        std::cout<< "Tokenizer::getToken() called with a stream that is not open." << std::endl;
        std::cout<< "Make sure that " << inputFileName << " exists and is readable. Terminating.";
        exit(2);
    }
    
    char c;
    
    while (inputStream.get(c) && !inputStream.eof()){
        std::cout<<c;
        file.push_back(c);
    }

    inputStream.close();
    std::cout<<"Done reading File"<<std::endl;
}

/*
 Mutates the original vector stored as a private variable 'file'
 by a looping through indices and comparing the states enumerated
 within the class 'fileAsArray'
 */
void fileAsArray::File_w_no_comments() {
    State state = START; // Initialize the state to START (Also the accepting state)

    // Iterate through each character in the file
    for (int i = 0; i < file.size(); i++) {
        switch (state) {
            case START:
                // If quote is found then all within must remain untouched
                if (file[i] == '"') {
                    state = QUOTE;
                } else if (file[i] == '/') { // Check for the beginning of a potential comment
                    // First check if division and if true then don't replace with space
                    std::pair<bool, int> result = isDivision(i);
                    if (result.first) { // If Division Operation then start index at new index
                        i = result.second;
                        state = START; // Move state back to START
                    } else {
                        // If not Division then continue in SLASH state and replace with space
                        file[i] = ' ';         // Replace the '/' with whitespace
                        state = SLASH; // Update state to reflect comment
                    }
                } else if (file[i] == '*') { // Error if not started with slash
                    //////// Should report error if '*' found not proceeded by '/' ///////
                    throw std::runtime_error("Error found through extraneous '*'");
                }
                break;

            case SLASH:
                // Check if it is a valid comment ('//')
                if (file[i] == '/') {
                    state = LINE_COMMENT;  // Move to the LINE_COMMENT state if '//' is found
                    file[i] = ' ';         // Replace the second '/' with whitespace
                } else if (file[i] == '*') {
                    state = BLOCK_COMMENT; // Move to the BLOCK_COMMENT state if '/*' is found
                    file[i] = ' ';         // Replace the first '/' with whitespace
                } else {
                    //////// Should report error if '/' found not proceeded by '/' '*' or division ///////
                    throw std::runtime_error("Error found through extraneous '/'");
                }
                break;

            case LINE_COMMENT:
                // Replace characters with whitespace until the end of the line
                if (file[i] == '\n') {
                    state = START; // Move back to the START state after finding a newline
                } else {
                    file[i] = ' ';  // Replace characters within the comment with whitespace
                }
                break;

            case BLOCK_COMMENT:
                // Replace characters with whitespace until next '*' is found
                if (file[i] == '*' ) {
                    state = ENDING_BLOCK_COMMENT; // Move to the ENDING_BLOCK_COMMENT state after finding a star
                    file[i] = ' ';  // Replace characters within the comment with whitespace
                } else {
                    file[i] = ' ';  // Replace characters within the comment with whitespace
                }
                break;

            // Once in 'BLOCK_COMMENT' state and finding '*', now check for the ending of a BLOCK_COMMENT
            case ENDING_BLOCK_COMMENT:
                // Check if it's been ended by '/', else continue replacing for space
                if (file[i] == '/' ) {
                    state = START; // Move to the START state after finding a slash during ENDING_BLOCK_COMMENT
                    file[i] = ' ';  // Replace characters within the comment with whitespace
                } else {
                    file[i] = ' ';  // Replace characters within the comment with whitespace
                }
                break;

            case QUOTE:
                // Check if end quote has been found and if so change state back to 'START'
                if (file[i] == '"') {
                    state = START; // Move back to the START state after finding end quote
                }
                break;
        }
    }
    // Checks Ending state to ensure its accepted
    if(state != START) {
        //////// Should report error if ending state is not accepting i.e. START ///////
        throw std::runtime_error("The ending state is " + std::to_string(state) + " not accepting!");
    }
}

// Print the vector stored as a private variable within the class 'fileAsArray'
std::pair<bool, int> fileAsArray::isDivision(int index) {
    size_t length = file.size();
    // Iterate through each character in the file
    while(index < length) {
        index++;
        //If a space then continue looping
        if (isspace(file[index])) {
            continue;
        }
        if (isdigit(file[index])) { // check if next is a number
            return std::make_pair(true, index);     // Return true if Division Op.
        } else return std::make_pair(false, index); // false otherwise
    }
}

// Print the vector stored as a private variable within the class 'fileAsArray'
void fileAsArray::printVector() {
    for (char c : file) {
        std::cout << c;
    }
}

