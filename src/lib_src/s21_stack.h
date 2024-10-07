#ifndef S21_STACK_H_
#define S21_STACK_H_

#include "s21_deque.h"
#include "../array_exception.h"

namespace s21 {

template <typename T>
class Stack : public Deque<T> {
private: // could inherit only if base class is not templated, otherwise it goes to shit
  // type overrides to make class code easy to understand (really..?)
  using size_type = size_t;
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;

public:

/* ========================================================================= */
/*                       Constructors and Destructors                        */
/* ========================================================================= */

  /**
   * @brief Default constructor, creates an empty stack
  */
  Stack() : Deque<T>() {}

  /**
   * @brief initializer list constructor, creates 
   * stack initizialized using std::initializer_list
  */
  Stack(std::initializer_list<value_type> const& items) : Deque<T>(items) {}
  /**
   * @brief Copy constructor
   * 
   * @note Performs deep copy of a stack, result is two identical stacks
  */
  Stack(const Stack &other) : Deque<T>(other) {}

  /**
   * @brief Move constructor
   * 
   * @note Performs a shallow copy of a stack, result is a single stack with resources
   * stolen from the given stack
   * 
   * Using std::move is required here, otherwise container will not be passed as
   * an r-value
  */
  Stack(Stack &&other) : Deque<T>(std::move(other)) {}

  /**
   * @brief Destructor
  */
  ~Stack() {}

  /**
   * @brief Assignment operator overload for moving an object
   * 
   * @note The same problem as with move constructor, have to create an r-value
   * again
  */
  Stack<value_type>& operator=(Stack<value_type> &&other) {
    this->Deque<T>::operator=(std::move(other));

    return *this;
  }


/* ========================================================================= */
/*                         Methods for modifying a List                      */
/* ========================================================================= */

  /**
   * @brief Accesses the top element of the stack
   * 
   * @throws ArrayException if stack is empty
  */
  const_reference top() { return Deque<T>::container_.back(); }

  /**
   * @brief Removes the top element from the stack
   * 
   * @note If container is empty nothing is done
  */
  void pop() {
    Deque<T>::container_.popBack();
  }

  /* ========================================================================= */
  /*                        Bonus Methods (insert_many)                        */
  /* ========================================================================= */

  /**
   * @brief Appends new elements to the top of the Stack
   * 
   * @note The same thing as insert_many_bacl but for the stack container
  */
  template <typename... Args>
  void insert_many_front(Args&&... args) {
    Deque<T>::container_.insert_many_back(args...);
  }

  // all other methods are inherited from Deque
};

}

#endif // S21_STACK_H_