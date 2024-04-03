//
// Created by Luis carmona on 3/22/24.
//


#include "OutPutGenerator.h"

void printFormattedLine(const std::string& label, const std::string& value) {
    std::cout << std::setw(20) << std::left << label << ": " << value << std::endl;
}

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
    printFormattedLine("IDENTIFIER_NAME", table->Name());
    printFormattedLine("IDENTIFIER_TYPE", table->idType());
    printFormattedLine("DATATYPE", table->dataType());
    printFormattedLine("DATATYPE_IS_ARRAY", table->isArray());
    printFormattedLine("DATATYPE_ARRAY_SIZE", std::to_string(table->arraySize()));
    printFormattedLine("SCOPE", std::to_string(table->scope()));
    std::cout << std::endl; 
};


void printParameterList(SymTblPtr &list){
    std::cout << std::endl << "   PARAMETER LIST FOR: " << list->Name() << std::endl;
    printFormattedLine("IDENTIFIER_NAME", list->Name());
    printFormattedLine("DATATYPE", list->dataType());
    printFormattedLine("DATATYPE_IS_ARRAY", list->isArray());
    printFormattedLine("DATATYPE_ARRAY_SIZE", std::to_string(list->arraySize()));
    printFormattedLine("SCOPE", std::to_string(list->scope()));
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
