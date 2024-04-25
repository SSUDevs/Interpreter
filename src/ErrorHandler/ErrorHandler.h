#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>

// Forward declaration to resolve circular references
class ErrorHandler;

// Globally defined variable
extern ErrorHandler _globalErrorHandler;

class ErrorHandler {
  private:
    std::unordered_map<
        int, std::function<void(int, const std::string &, const std::string &)>>
        errorHandlers;

  public:
    ErrorHandler() { initializeErrorHandlers(); }
    void initializeErrorHandlers();

    void handle(int errorCode, int lineNumber,
                const std::string &additionalMessage1 = "",
                const std::string &additionalMessage2 = "");

    void logError(int line, const std::string &errorCodeDescription,
                  const std::string &msg1, const std::string &msg2);
};

#endif // ERRORHANDLER_H