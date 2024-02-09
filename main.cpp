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
using namespace std;

int main() {

	// open file
	ifstream codeFile;
	string fileName = "programming_assignment_1-test_file_1.c";
	codeFile.open(fileName);

	// check if file opened
	if (!codeFile.is_open()) {
		cerr << "Couldn't open file: " << fileName << endl;
		exit(0);
	}

	// get char count in file
	codeFile.seekg(0, codeFile.end);
	int charCount = codeFile.tellg();
	codeFile.seekg(0, codeFile.beg);	// go back to beginning of file

	// close file
	codeFile.close();

	return 0;
}
