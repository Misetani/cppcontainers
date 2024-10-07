#ifndef S21_DEQUE_H_
#define S21_DEQUE_H_

#include <cstddef>
#include <iostream>

#include "s21_list.h"
#include "../array_exception.h"

namespace s21 {

/**
 * @note Our deque will use a list as an underlying collection.
 * this will not be very efficient, but is enough for our purposes
 * 
 * If desired list could be switched for a verctor or a deque later on.
*/
template <typename T>
class Deque { // deque does not inherit from Container, because it contains container (list)
protected: // constructors are protected too
  // type overrides to make class code easy to understand (really..?)
  using size_type = size_t;
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;

  List<T> container_; // for now it is a list, will change it to vector, maybe

/* ========================================================================= */
/*                       Constructors and Destructors                        */
/* ========================================================================= */

  /**
   * @brief Default constructor, creates an empty deque
   * 
   * @note Because deque itself does not hold any deque specific data, default
   * construcotr has to initialize only its contained container
  */
  Deque() : container_() {}

  /**
   * @brief initializer list constructor, creates 
   * deque initizialized using std::initializer_list
  */
  Deque(std::initializer_list<value_type> const& items) : container_(items) {}
  /**
   * @brief Copy constructor
   * 
   * @note Performs deep copy of a deque, result is two identical deques
  */
  Deque(const Deque &other) : container_(other.container_) {}

  /**
   * @brief Move constructor
   * 
   * @note Performs a shallow copy of a deque, result is a single deque with resources
   * stolen from the given deque
   * 
   * Using std::move is required here, otherwise container will not be passed as
   * an r-value
  */
  Deque(Deque &&other) : container_(std::move(other.container_)) {}

  /**
   * @brief Destructor
   * 
   * @note Does not have to do anything because all data will be cleared with
   * a contained class container_ (it's destructor should be called automatically)
  */
  ~Deque() {}

  /**
   * @brief Assignment operator overload for moving an object
   * 
   * @note The same problem as with move constructor, have to create an r-value
   * again
  */
  Deque<value_type>& operator=(Deque<value_type> &&other) {
    container_ = std::move(other.container_);

    return *this;
  }

// no difference between protected and public here because all constructors are
//  protected (no instance of class could be created)
public: 

/* ========================================================================= */
/*                         Methods for modifying Deque                       */
/* ========================================================================= */

  /**
   * @brief Returns the number of elements in deque
  */
  size_type size() const{ return container_.size(); }

  /**
   * @brief Returns true if deque is empty, false otherwise
  */
  bool empty() const { return container_.empty(); }

  /**
   * @brief Inserts an element at the top of the stack
   * 
   * @note Both queue and stack push to the back
  */
  void push(const_reference value) {
    container_.pushBack(value);
  }

  /**
   * @brief Swaps the contents of two deques
  */
  void swap(Deque& other) {
    container_.swap(other.container_);
  }
};

}

#endif // S21_DEQUE_H_