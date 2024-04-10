# ERROR CODES:

### 1. **Stream not open for reading**
- **Description:** Fails to open the file stream for reading, indicating that the file does not exist or is not readable.
- Line Number: 17
- **File:**  `fileAsArray.h` in the `fileAsArray` constructor or `readFile` method.

### 2. **Syntax error due to invalid or unexpected token used in in global scope**
- **Description:** Invalid syntax in global scope 
- Line Number: 28
- **File:** `Parser.cpp` 

### 3. **Declaration with reserved name**
- **Description:** Attempts to declare a variable that is a reserved word.
- Line Number: 88, 113, 127, 175, 235, 298, 358, 520
- **File:** `Parser.cpp`

### 4. **Invalid array declaration**
- **Description:** Incorrect syntax for array declaration, such as a negative array size or an invalid character in the declaration.
- Line Number: 135
- **File:** `Parser.cpp`

### 5. **Missing '[' or ']' in definition**
- **Description:** Forgetting to correctly use the `[` or `]` character in array declarations.
- **Line Number:** 145, 385, 456
- **File:** `Parser.cpp`

### 6. **Missing '{' or '}' in block definitions**
- **Description:** Fails to include opening or closing braces for blocks where needed
- Line Number: 202
- **File:** `Parser.cpp`

### 7. **Procedure or Function declared without identifier**
- **Description:** Errors related to the incorrect declaration of procedures or functions, including missing names or invalid syntax.
- Line Number: 228, 291
- **File:** `Parser.cpp`

### 8. **Function without specified return type**
- **Description:** Specifying an invalid return type for a function.
- **Line Number:** 280
- **File:** `Parser.cpp`

### 9. **Parameter declared without data type**
- **Description:** An error related to specifying incorrect data types for parameters in a function or procedure.
- **Line Number:** 341
- **File:** `Parser.cpp`

### 10. **Parameter declared without identifier**
- **Description:** Utilizing an invalid identifier within a function or procedure's parameter list.
- **Line Number:** During the parsing of identifiers within a parameter list.
- **File:** `Parser.cpp`

### 11. **Incorrect array size specifier**
- **Description:** Specifying an incorrect or invalid size for an array, possibly due to syntax errors or non-integer values.
- **Line Number:** 375
- **File:** `Parser.cpp`

### 12. **Missing '(' or ')'**
- **Description:** Fails to include opening or closing parenthesis where needed
- **Line Number:** 406
- **File:** `Parser.cpp`

### 13. **Invalid statement declaration**
- **Description:** Encountering a syntax error by when declaring a statement
- **Line Number:** 481, 499
- **File:** `Parser.cpp`

### 14. **Invalid if declarations**
- **Description:** This error occurs when an invalid if statement is made
- **Line Number:** 542
- **File:** `Parser.cpp`

### 15. **Invalid expression**
- **Description:** This error signifies a general syntax error within an expression
- **Line Number:** 669
- **File:** `Parser.cpp`

### 16. **Invalid assignment statement**
- **Description:** Encountered sytax error in a assignment expression
- **Line Number:** 681
- **File:** `Parser.cpp`

### 17. **Invalid array index**
- **Description:** Encountered sytax error in array index provided
- **Line Number:** 698
- **File:** `Parser.cpp`

### 18. **Missing semicolon**
- **Description:** Occurs when a semicolon (;) that should terminate a statement is missing.
- **Line Number:** 747
- **File:** `Parser.cpp`

### 19. **Unexpected token in inline statement**
- **Description:** This error indicates that an unexpected token was encountered during the parsing of an inline statement. 
- **Line Number:** 758
- **File:** `Parser.cpp`

### 20. **Unexpected token in iterator**
- **Description:** This error is raised when an unexpected token is encountered in the context of an iteration statement, such as a for or while loop.
- **Line Number:** 782
- **File:** `Parser.cpp`

### 21. **Expected a quoted string after 'printf'**
- **Description:** Triggered when the `printf` function is called without a proper string literal as the first argument.
- **Line Number:** 851
- **File:** `Parser.cpp`

### 22. **'return' statement syntax error**
- **Description:** This error occurs when there is a syntax issue with a `return` statement, such as missing or invalid return value.
- **Line Number:** 882
- **File:** `Parser.cpp`

### 23. **Invalid signed integer**
- **Description:** This error is raised when an attempt to define a signed integer is made in an incorrect format, such as missing digits following the sign.
- **Line Number:** 262
- **File:** `Tokenizer.cpp` 

### 24. **Invalid Integer operation**
- **Description:** Indicates an issue with the formatting of an integer literal, such as containing invalid characters or invalid integer operations.
- **Line Number:** 273
- **File:** `Tokenizer.cpp`

### 25. **Unterminated string quote**
- **Description:** Triggered when a string literal is not properly closed with a matching quote, leading to a syntax error.
- **Line Number:** 301
- **File:** `Tokenizer.cpp` 

### 26. **Stream not open for writing**
- **Description:** Fails to open the file stream for writing, indicating that the file does not exist or is not writable.
- Line Number: 13
- **File:**  `OutPutGenerator.h` 

### 27. **Unexpected end of CST**
- **Description:** This error is raised when the end of the CST is reached unexpectedly.
- **Line Number:** 18
- **File:** `SymbolTablesLinkedList.cpp` 

### 28. **Accessing null pointer in CST**
- **Description:** This error is raised when a node is accessed for its value when its null.
- **Line Number:** 38
- **File:** `SymbolTablesLinkedList.cpp` 

### 29. **Local declaration of globally defined variable**
- **Description:** This error is raised when a variable is declared locally with the same name as one already declared globally.
- **Line Number:** 70
- **File:** `SymbolTablesLinkedList.cpp` 

### 30. **Redeclaration of Locally defined variable**
- **Description:** This error is raised when a variable is declared with the same name as one declared in it's same scope.
- **Line Number:** 78
- **File:** `SymbolTablesLinkedList.cpp` 

### 31. **Global declaration of globally defined variable, function or procedure**
- **Description:** This error is raised when a variable, function, or procedure is declared globally with the same name as one already declared globally.
- **Line Number:** 87, 205, 250, 376, 402
- **File:** `SymbolTablesLinkedList.cpp` 

### 100. **General expected token error while parsing**
- **Description:** General error occured when expecting a certain token
- **File:** `Parser.cpp`

### 101. **General Error when creating CST**
- **Description:** General error occured when constructing the CST
- **File:** `Parser.cpp`
