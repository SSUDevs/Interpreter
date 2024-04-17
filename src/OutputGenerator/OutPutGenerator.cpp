#include "OutPutGenerator.h"
#include "../ErrorHandler/ErrorHandler.h"

#include <iomanip>

void printFormattedLine(const std::string &label, const std::string &value) {
    std::cout << std::setw(20) << std::left << label << ": " << value
              << std::endl;
}

void OutPutGenerator::PrintAST(NodePtr &root) {
    if (root == nullptr) {
        cout << "Tree is empty." << endl;
        return;
    }
    int spaces = 0;

    while (root != nullptr) {
        if(root->getSemanticType()==Node::Type::OTHER){
            cout<<root->value.value();
            spaces+= root->value.value().length();
        }
        cout << Node::semanticTypeToString(root->getSemanticType());
        spaces += Node::semanticTypeToString(root->getSemanticType()).length();
        if (root->Right() != nullptr) {

            cout << " --> ";
            spaces += 5;
            root = root->Right();
        } else if (root->Left() != nullptr) {

            cout << " --> nullptr" << endl;
            for (int i = 0; i < spaces - 1; i++) {
                cout << " ";
            }
            cout << '|' << endl;
            if (spaces > 1) {
                for (int i = 0; i < spaces; i++) {
                    cout << "-";
                }
                cout << endl;
            }

            cout << "\\/" << endl;
            root = root->Left();
            spaces = 0;

        } else {
            cout << " ---> nullptr";
            break;
        }
    }
}

void OutPutGenerator::PrintCST(NodePtr &root) {
    ofstream output("Concrete_SyntaxTree_Output.txt");
    if (!output.is_open()) {
                _globalErrorHandler.handle(26, 0);

    }
    if (root == nullptr) {
        cout << "Tree is empty." << endl;
        return;
    }
    int spaces = 0;

    while (root != nullptr) {
        cout << root->Value().value();
        spaces += root->Value().value().length();
        if (root->Right() != nullptr) {
            cout << " --> ";
            spaces += 5;
            root = root->Right();
        } else if (root->Left() != nullptr) {

            cout << " --> nullptr" << endl;
            for (int i = 0; i < spaces - 1; i++) {
                cout << " ";
            }
            cout << '|' << endl;
            if (spaces > 1) {
                for (int i = 0; i < spaces; i++) {
                    cout << "-";
                }
                cout << endl;
            }

            cout << "\\/" << endl;
            root = root->Left();
            spaces = 0;
        } else {
            cout << " ---> nullptr";
            break;
        }
    }
    output.close();
}

void printATable(SymTblPtr &table) {
    printFormattedLine("IDENTIFIER_NAME", table->GetName());
    printFormattedLine("IDENTIFIER_TYPE", table->GetStringIdType());
    printFormattedLine("DATATYPE", table->GetDataType());
    printFormattedLine("DATATYPE_IS_ARRAY", table->GetIsArray());
    printFormattedLine("DATATYPE_ARRAY_SIZE",
                       std::to_string(table->GetArraySize()));
    printFormattedLine("SCOPE", std::to_string(table->GetScope()));
    cout << endl;
};

void printParameterList(SymTblPtr &list) {

    printFormattedLine("IDENTIFIER_NAME", list->GetName());
    printFormattedLine("DATATYPE", list->GetDataType());
    printFormattedLine("DATATYPE_IS_ARRAY", list->GetIsArray());
    printFormattedLine("DATATYPE_ARRAY_SIZE",
                       std::to_string(list->GetArraySize()));
    printFormattedLine("SCOPE", std::to_string(list->GetScope()));
}

void OutPutGenerator::PrintSymbolTables(SymTblPtr &root) {

    vector<SymTblPtr> prmLists;

    while (root != nullptr) {
        if (root->GetIdType() != SymbolTable::IDType::parameterList) {
            cout << "--------------------------------------------" << endl;
            printATable(root);
        } else {
            prmLists.push_back(root);
        }

        root = root->GetNextTable();
    }
    string last = "";
    for (int i = 0; i < prmLists.size(); i++) {
        cout << "--------------------------------------------" << endl;
        if (last != prmLists.at(i)->procOrFuncName())
            cout << endl
                 << "PARAMETER LIST FOR: " << prmLists.at(i)->procOrFuncName()
                 << endl;
        cout << "--------------------------------------------" << endl;
        last = prmLists.at(i)->procOrFuncName();
        printParameterList(prmLists.at(i));
    }
}
