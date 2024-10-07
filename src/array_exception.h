#ifndef ARRAY_EXCEPTION_H_
#define ARRAY_EXCEPTION_H_

namespace s21 {

#include <string>
#include <exception>

class ArrayException : public std::exception {
 private:
  std::string error_;

 public:
  ArrayException(std::string error) : error_{ error } {}

  const char* what() const noexcept override { return error_.c_str(); }
};

}

#endif // ARRAY_EXCEPTION_H_