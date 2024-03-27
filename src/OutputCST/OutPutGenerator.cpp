
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
        cout << root->Value().value();
        spaces+= root->Value().value().length();
        if (root->Right() != nullptr) {
            cout << " --> ";
            spaces +=5;
            root = root->Right();
        } else if (root->Left() != nullptr) {

            cout << " --> nullptr" << endl;
            for(int i=0;i<spaces-1;i++){
                cout<<" ";
            }
            cout<<'|'<<endl;
            if(spaces>1){
            for(int i=0;i<spaces;i++){
                cout<<"-";
            }
            cout<<endl;
            }
            
            cout<<"↓"<<endl;
            root = root->Left();
            spaces=0;
        } else {
            break;
        }
    }
    output.close();
}


