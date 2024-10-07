#ifndef S21_CONTAINER_H_
#define S21_CONTAINER_H_

#include <limits>
#include "../s21_containers.h"

namespace s21 {

/**
 * @brief Base class for all containers
 * 
 * @details All implemented container classes should inherit from this class.
 * If any common method is needed, it should be added here.
*/
class Container {
protected:
  using size_type = size_t;

  size_type size_{ 0 };

  Container() {}

public:
  /**
   * @brief Returns the number of elements in the container
  */
  size_type size() const{ return size_; }

  /**
   * @brief Returns true if the container is empty, false otherwise
  */
  bool empty() const { return size_ == 0; }

  /**
   * @brief Returns the maximum number of elements the container is able to hold
  */
  size_type max_size() { return std::numeric_limits<size_type>::max(); }
};

}

#endif  // S21_CONTAINERS_H_