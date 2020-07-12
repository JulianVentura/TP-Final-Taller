#ifndef FALLACONEXIONEXCEPTION_H
#define FALLACONEXIONEXCEPTION_H
#include <exception>
#define ERROR_MSG_LEN 256

class FallaConexionException : public std::exception {
public:
private:
    char error_msg[ERROR_MSG_LEN];
public:
    explicit FallaConexionException(const char* format, ...) noexcept;
    virtual const char* what() const noexcept;
    virtual ~FallaConexionException() noexcept {}
};

#endif
