#ifndef ERRORGRAFICO_H
#define ERRORGRAFICO_H
#include <exception>
#define ERROR_MSG_LEN 256

class ErrorGrafico: public std::exception {
private:
    char error_msg[ERROR_MSG_LEN];
public:
    explicit ErrorGrafico(const char* format, ...) noexcept;
    virtual const char* what() const noexcept;
    virtual ~ErrorGrafico() noexcept {}
};
#endif
