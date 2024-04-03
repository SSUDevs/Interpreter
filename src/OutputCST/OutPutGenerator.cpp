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

            cout<<"\\/"<<endl;
            root = root->Left();
            spaces=0;
        } else {
            cout<<" ---> nullptr";
            break;
        }
    }
    output.close();
}


void printATable(SymTblPtr &table){
    cout<<"IDENTIFIER_NAME: "<<table->Name()<<endl;
    cout<<"IDENTIFIER_TYPE: "<< table->idType()<<endl;
    cout<<"DATATYPE: "<<table->dataType()<<endl;
    cout<<"DATATYPE_IS_ARRAY: "<<table->isArray()<<endl;
    cout<<"DATATYPE_ARRAY_SIZE: "<<table->arraySize()<<endl;
    cout<<"Scope: "<<table->scope()<<endl;
};


void printParameterList(SymTblPtr &list){

    cout<<"PARAMETER LIST FOR: "<<endl;
    cout<<"IDENTIFIER_NAME: "<<list->Name()<<endl;
    cout<<"DATATYPE: "<<list->dataType()<<endl;
    cout<<"DATATYPE_IS_ARRAY: "<<list->isArray()<<endl;
    cout<<"DATATYPE_ARRAY_SIZE: "<<list->arraySize()<<endl;
    cout<<"SCOPE: "<<list->scope()<<endl;
}


void OutPutGenerator::PrintSymbolTables(SymTblPtr &root) {

    vector<SymTblPtr> prmLists;

    while(root != nullptr){
        cout<<"--------------------------------------------"<<endl;
        if(root->_idtype != SymbolTable::IDType::parameterList){
            printATable(root);
        }else{
            prmLists.push_back(root);
        }

        root = root->nextTable;

    }

    for(auto & prmList : prmLists){
        cout<<"--------------------------------------------"<<endl;
        printParameterList(prmList);
    }


}
