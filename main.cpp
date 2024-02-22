/* 
 * Assignment: CS460 Interpreter
 * Authors: Evan Walters, Luis carmona, Ben Harris, Hanpei Zhang
 * Date: 2/8/24
 * Description:
 * 
 */

#include <iostream>
#include <string>
#include <fstream>
#include "fileAsArray.h"
#include "Tokenizer.h"

using namespace std;

int main(int argc, char *argv[]) {

    fileAsArray fileArray(argv[1]);
    fileArray.readFile();

    // Try-catch for parsing out comments
    try {
        fileArray.File_w_no_comments();
    } catch (const std::exception& error) {
        // Catch and handle the exception
        std::cerr << "Exception caught: " << error.what() << std::endl;
    }

    // Print the modified content without comments
    // fileArray.printVector();


	// 

    return 0;
}
 