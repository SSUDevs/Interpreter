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
    fileAsArray(std::string fileName);
    void readFile();
    std::vector<char> File_w_no_comments();

private:
    std::vector<char> file;
    std::ifstream inputStream;
    std::string inputFileName;




};


#endif //ASSIGNMENT1_460_FILEASARRAY_H
