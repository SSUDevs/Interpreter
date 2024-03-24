//
// Created by Luis carmona on 3/22/24.
//

#include "OutPutGenerator.h"

void OutPutGenerator::Conc_Syn_Tree_Output(NodePtr& root) {

    while (root->Left()!= nullptr && root->Right()!= nullptr){
        cout<<root->Value().value();
        if(root->Right()!= nullptr){
            cout<<" --> ";
            root= root->Right();
        }
        else{
            cout<<" --> Nullptr"<<endl;
            root=root->Left();
        }
    }

}
