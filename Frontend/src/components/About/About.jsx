import React from "react";
import styles from "./About.module.css";
import UserPics from "../Contributors/UserPics";

export default function About() {
  return (
    <div className={styles.container}>
      <UserPics />
      <h1>C-like Language Interpreter Project</h1>
      <h2>Overview</h2>
      <p>
        The goal of this project is to build an interpreter for a C-like
        language by following a comprehensive development process. This process
        includes several critical stages, each contributing to the interpreter's
        capability to parse and execute C-like code efficiently.
      </p>
      <p>The development stages are:</p>
      <ul>
        <li>
          <strong>Ignoring Comments</strong>
        </li>
        <li>
          <strong>Tokenizing</strong>
        </li>
        <li>
          <strong>Recursive Decent Parsing</strong>
        </li>
        <li>
          <strong>Symbol Table Implementation</strong>
        </li>
        <li>
          <strong>Abstract Syntax Tree Construction</strong>
        </li>
      </ul>
      <p>
        Each stage is designed to address a specific aspect of language
        interpretation, from preprocessing the source code to executing it.
      </p>
      <h2>Implemented Features</h2>
      <h3>✅ Comment Removal for a C-like Programming Language</h3>
      <p>
        This initial step aims to prepare the source code for further processing
        by removing comments. It's essential for simplifying the code analysis
        in subsequent stages. The program uses a deterministic finite state
        automaton (DFA) to identify and eliminate both line and block comments
        from the source code. The cleaned code is then outputted, ready for
        tokenization.
      </p>
      <ul>
        <li>
          <code>main.cpp</code>: Initiates the comment removal process.
        </li>
        <li>
          <code>fileAsArray.h</code> and <code>fileAsArray.cpp</code>:
          Implements the <code>fileAsArray</code> class for reading and
          processing the file according to DFA rules.
        </li>
      </ul>
      <h3>✅ Tokenizing</h3>
      <p>
        The tokenizing stage is designed to convert the cleaned source code into
        a series of tokens. These tokens are used by the parser to understand
        the code's structure and semantics.
      </p>
      <ul>
        <li>
          <code>Token.h</code> and <code>Token.cpp</code>: Defines all
          recognizable tokens used for tokenizing
        </li>
        <li>
          <code>Tokenizer.h</code> and <code>Tokenizer.cpp</code>: Creates
          tokens using a DFA to represent the codes structure and semantics
        </li>
      </ul>
      <h3>✅ Recursive Decent Parser</h3>
      <p>
        Creates a concrete syntax tree (CST) based upon the Backus-Naur Form
        (BNF) language definition using a procedurally-driven DFA. Utilizes an
        LCRS binary tree (Left-Child, Right-Sibling) to store the CST. The
        program may also display the resulting CST in breadth-first order, if
        desired.
      </p>
      <ul>
        <li>
          <code>Node.h</code> and <code>Node.cpp</code>: Used for the parser's
          internal representation. Each Node instance represents a part of the
          source code, such as a token or a syntax rule, and can link to child
          nodes and sibling nodes to form a tree structure.
        </li>
        <li>
          <code>Parser.h</code> and <code>Parser.cpp</code>: Implement the
          Parser class which takes a sequence of tokens as input and constructs
          the CST by recursively applying grammar rules defined in the BNF. The
          parser checks the source code's syntax and generates a parse tree that
          reflects the code's hierarchical structure.
        </li>
        <li>
          <code>ConcreteSyntaxTree.h</code> and{" "}
          <code>ConcreteSyntaxTree.cpp</code>: Provide functionalities to manage
          the Concrete Syntax Tree, allowing for the insertion and navigation of
          nodes within the tree. Used to represent the parsed source code in a
          hierarchical manner, allowing for further analysis or interpretation.
        </li>
        <li>
          <code>OutPutGenerator.h</code> and <code>OutPutGenerator.cpp</code>:
          Generate output based on the constructed syntax tree. Includes
          printing the tree structure in a breadth-first order for debugging or
          visualization purposes, as well as generating intermediate code or
          direct interpretation for execution.
        </li>
      </ul>
      <h3>✅ Symbol Table</h3>
      <p>
        Creates symbol tables for all the defined variables (including their
        type and scope) and the names of all functions and procedures to be used
        for semantic analysis, scope management, and identifier resolution in
        the parsing process.
      </p>
      <p>- This includes:</p>
      <ul>
        <li>
          Ensuring that variables and functions are declared and accessed within
          their respective scopes.
        </li>
        <li>
          Associating identifiers with their data types and values, as well as
          checking for type consistency across operations.
        </li>
        <li>
          Handling the declaration and invocation of functions and procedures,
          including parameter passing mechanisms.
        </li>
        <li>
          Identifying undeclared identifiers, type mismatches, and scope
          violations.
        </li>
      </ul>
      <ul>
        <li>
          <code>SymbolTable.h</code> and <code>SymbolTable.cpp</code>: Define
          and implement the SymbolTable class, which represents individual
          entries in the symbol table. Each entry can denote a variable,
          function, procedure, or a parameter list, with attributes such as
          name, data type, identifier type, scope level, and array-related
          properties. The symbol table entries are used for checking variable
          declarations, resolving identifier references, and performing type
          checking during the interpretation process.
        </li>
        <li>
          <code>SymbolTablesLinkedList.h</code> and{" "}
          <code>SymbolTablesLinkedList.cpp</code>: Responsible for managing a
          linked list of SymbolTable entries, facilitating the construction and
          manipulation of the entire symbol table. This structure supports the
          nesting of scopes and the hierarchical nature defined in the BNF.
        </li>
      </ul>
      <h3>🚧 Abstract Syntax Tree (In Progress)</h3>
      <p>
        Creates an Abstract Syntax Tree (AST) based on the Concrete Syntax Tree
        (CST). An Abstract Syntax Tree is not a clone of a Concrete Syntax Tree.
        Utilizes an LCRS binary tree (Left-Child, Right-Sibling) to store the
        AST. Allows for the display of the resulting AST in breadth-first order.
      </p>
      <p>
        <em>Not yet implemented.</em>
      </p>
    </div>
  );
}
