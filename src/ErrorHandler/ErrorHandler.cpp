#include "ErrorHandler.h"
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>

// Globally defined
ErrorHandler _globalErrorHandler;

// Maps the error code to those initialized
void ErrorHandler::handle(int errorCode, int lineNumber, const std::string& message1, const std::string& message2) {
    if (errorHandlers.find(errorCode) != errorHandlers.end()) {
        errorHandlers[errorCode](lineNumber, message1, message2);
    } else {
        std::cerr << "Unhandled error code: " << errorCode << " at line " << lineNumber;
        if (!message1.empty() || !message2.empty()) {
            std::cerr << " (" << message1 << " " << message2 << ")";
        }
        std::cerr << std::endl;
    }
}

// Helper function to log errors
void ErrorHandler::logError(int line, const std::string &errorCodeDescription,
                const std::string &msg1, const std::string &msg2) {
    std::cerr << errorCodeDescription << " on line " << line;
    if (!msg1.empty() || !msg2.empty()) {
        std::cerr << " (" << msg1 << " " << msg2 << ")";
    }
    std::cerr << std::endl;
}
    
void ErrorHandler::initializeErrorHandlers() {
    errorHandlers[1] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 1: Stream not open for reading - Check if file exists and is readable", msg1, msg2);
        exit(1);
    };
    errorHandlers[2] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 2: Syntax error due to invalid or unexpected token used in global scope", msg1, msg2);
        exit(2);
    };
    errorHandlers[3] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 3: Declaration with reserved name", msg1, msg2);
        exit(3);
    };
    errorHandlers[4] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 4: Invalid array declaration", msg1, msg2);
        exit(4);
    };
    errorHandlers[5] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 5: Missing '[' or ']' in definition", msg1, msg2);
        exit(5);
    };
    errorHandlers[6] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 6: Missing '{' or '}' in block definitions", msg1, msg2);
        exit(6);
    };
    errorHandlers[7] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 7: Procedure or Function declared without identifier", msg1, msg2);
        exit(7);
    };
    errorHandlers[8] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 8: Function without specified return type", msg1, msg2);
        exit(8);
    };
    errorHandlers[9] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 9: Parameter declared without data type", msg1, msg2);
        exit(9);
    };
    errorHandlers[10] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 10: Parameter declared without identifier", msg1, msg2);
        exit(10);
    };
    errorHandlers[11] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 11: Incorrect array size specifier", msg1, msg2);
        exit(11);
    };
    errorHandlers[12] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 12: Missing '(' or ')'", msg1, msg2);
        exit(12);
    };
    errorHandlers[13] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 13: Invalid statement declaration", msg1, msg2);
        exit(13);
    };
    errorHandlers[14] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 14: Invalid if declarations", msg1, msg2);
        exit(14);
    };
    errorHandlers[15] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 15: Invalid expression", msg1, msg2);
        exit(15);
    };
    errorHandlers[16] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 16: Invalid assignment statement", msg1, msg2);
        exit(16);
    };
    errorHandlers[17] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 17: Invalid array index", msg1, msg2);
        exit(17);
    };
    errorHandlers[18] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 18: Missing semicolon", msg1, msg2);
        exit(18);
    };
    errorHandlers[19] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 19: Unexpected token in inline statement", msg1, msg2);
        exit(19);
    };
    errorHandlers[20] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 20: Unexpected token in iterator", msg1, msg2);
        exit(20);
    };
    errorHandlers[21] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 21: Expected a quoted string after 'printf'", msg1, msg2);
        exit(21);
    };
    errorHandlers[22] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 22: 'return' statement syntax error", msg1, msg2);
        exit(22);
    };
    errorHandlers[23] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 23: Invalid signed integer", msg1, msg2);
        exit(23);
    };
    errorHandlers[24] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 24: Invalid integer operation", msg1, msg2);
        exit(24);
    };
    errorHandlers[25] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 25: Unterminated string quote", msg1, msg2);
        exit(25);
    };
    errorHandlers[26] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 26: Stream not open for writing", msg1, msg2);
        exit(26);
    };
    errorHandlers[27] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 27: Unexpected end of CST", msg1, msg2);
        exit(27);
    };
    errorHandlers[28] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 28: Accessing null pointer in CST", msg1, msg2);
        exit(28);
    };
    errorHandlers[29] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 29: Local declaration of globally defined variable", msg1, msg2);
        exit(29);
    };
    errorHandlers[30] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 30: Redeclaration of locally defined variable", msg1, msg2);
        exit(30);
    };
    errorHandlers[31] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 31: Global declaration of globally defined variable, function or procedure", msg1, msg2);
        exit(31);
    };
    errorHandlers[32] = [this](int line, const std::string& msg1, const std::string& msg2) {
        logError(line, "Error 32: Expected semicolon or comma", msg1, msg2);
        exit(31);
    };
}
