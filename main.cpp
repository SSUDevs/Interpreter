/* 
 * Assignment: CS460 Interpreter
 * Authors: Evan Walters
 * Date: 2/8/24
 * Description:
 * 
 */

#include <iostream>
#include <string>
#include <fstream>
#include "fileAsArray.h"
using namespace std;

int main(int argc, char *argv[]) {

	// open file
	ifstream codeFile;
	//string fileName = "programming_assignment_1-test_file_1.c";
	codeFile.open(argv[1]);

	// check if file opened
	if (!codeFile.is_open()) {
		cerr << "Couldn't open file: " << argv[1] << endl;
		exit(0);
	}

	// get char count in file
	codeFile.seekg(0, codeFile.end);
	int charCount = codeFile.tellg();
	codeFile.seekg(0, codeFile.beg);	// go back to beginning of file

	// close file
	codeFile.close();

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
    fileArray.printVector();

    return 0;
}
