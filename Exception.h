#include <exception>
#include <string>

class Exception : public std::exception {
public:
  Exception(std::string message);
  const char *what() const noexcept override;

private:
  std::string message;
  int line;
};
