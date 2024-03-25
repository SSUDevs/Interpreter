
//
// Created by Luis carmona on 3/22/24.
//

#include "OutPutGenerator.h"

void OutPutGenerator::PrintCST(NodePtr& root) {

    ofstream output("Concrete_SyntaxTree_Output.txt");
    if(!output.is_open()){
        cerr << "Cant open Concrete Output File "<<endl;
        exit(90); // Exit if there's an error
    }
    if (root == nullptr) {
        cout << "Tree is empty." << endl;
        return;
    }
    int spaces=0;

    while (root != nullptr) {
        output << root->Value().value();
        spaces+= root->Value().value().length();
        if (root->Right() != nullptr) {
            output << " --> ";
            spaces +=5;
            root = root->Right();
        } else if (root->Left() != nullptr) {

            output << " --> nullptr" << endl;
            for(int i=0;i<spaces;i++){
                output<<"-";
            }
            output<<endl;
            output<<"↓"<<endl;
            root = root->Left();
            spaces=0;
        } else {
            break;
        }
    }

}


