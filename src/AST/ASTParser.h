#ifndef ASTPARSER_H
#define ASTPARSER_H

#include "../Node/Node.h"
#include "../Token/Token.h"
#include <memory>
#include <vector>

using NodePtr = std::shared_ptr<Node>;

class ASTParser {
  public:
    explicit ASTParser(const NodePtr &cstRoot);

    enum InsertionMode { LeftChild, RightSibling };

    NodePtr parse();
    // std::vector<Node> inToPostFix(const std::vector<Node> &infix);

  private:
    NodePtr root;        // Root of the AST
    NodePtr currCstNode; // Current node in the CST being processed
    NodePtr lastASTNode; // Last node added to the AST

    // The actual string value of the node
    std::string value;

    bool isDataType(std::string value);

    // maps the semantics identifiers to the type defined in Node class
    Node::Type determineSemanticNodeType(const std::string &value);
    NodePtr parseAssignment(NodePtr &startOfAssignmentNode);
    NodePtr parseIFsORWhiles(NodePtr &currCstNode);
    NodePtr parseFor(NodePtr &currCstNode);
    NodePtr parsePrintF(NodePtr &currCstNode);
    std::vector<NodePtr> inToPostFix(const std::vector<NodePtr> &infix);
    NodePtr parseTypeDec(NodePtr &currCstNode);
    void addToAST(NodePtr node, InsertionMode);
};

#endif // ASTPARSER_H
