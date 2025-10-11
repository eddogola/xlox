#include "Exception.h"
#include <string>

Exception::Exception(std::string message) : message(message) {}

const char *Exception::what() const noexcept { return message.c_str(); }
