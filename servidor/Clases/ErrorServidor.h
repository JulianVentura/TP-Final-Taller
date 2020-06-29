#ifndef __ERRORSERVIDOR__
#define __ERRORSERVIDOR__
#include <exception>
#define ERROR_MSG_LEN 256

class ErrorServidor: public std::exception {
private:
    char error_msg[ERROR_MSG_LEN];
public:
    explicit ErrorServidor(const char* format, ...) noexcept;
    virtual const char* what() const noexcept;
    virtual ~ErrorServidor() noexcept {}
};
#endif
