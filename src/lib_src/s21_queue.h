#ifndef S21_QUEUE_H_
#define S21_QUEUE_H_

#include "s21_deque.h"
#include "../array_exception.h"

namespace s21 {

template <typename T>
class Queue : public Deque<T> {
private:
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
   * @brief Default constructor, creates an empty Queue
  */
  Queue() : Deque<T>() {}

  /**
   * @brief initializer list constructor, creates 
   * Queue initizialized using std::initializer_list
  */
  Queue(std::initializer_list<value_type> const& items) : Deque<T>(items) {}
  /**
   * @brief Copy constructor
   * 
   * @note Performs deep copy of a Queue, result is two identical Queues
  */
  Queue(const Queue &other) : Deque<T>(other) {}

  /**
   * @brief Move constructor
   * 
   * @note Performs a shallow copy of a Queue, result is a single Queue with resources
   * stolen from the given Queue
   * 
   * Using std::move is required here, otherwise container will not be passed as
   * an r-value
  */
  Queue(Queue &&other) : Deque<T>(std::move(other)) {}

  /**
   * @brief Destructor
   * 
   * @note Does not have to do anything because all data will be cleared with
   * a contained class container_ (it's destructor should be called automatically)
  */
  ~Queue() {}

  /**
   * @brief Assignment operator overload for moving an object
   * 
   * @note The same problem as with move constructor, have to create an r-value
   * again
  */
  Queue<value_type>& operator=(Queue<value_type> &&other) {
    this->Deque<T>::operator=(std::move(other));

    return *this;
  }


/* ========================================================================= */
/*                         Methods for modifying a List                      */
/* ========================================================================= */

  /**
   * @brief Accesses the first element of the Queue
   * 
   * @throws ArrayException if Queue is empty
  */
  const_reference front() { return Deque<T>::container_.front(); }

  /**
   * @brief Accesses the last element of the Queue
   * 
   * @throws ArrayException if Queue is empty
  */
  const_reference back() { return Deque<T>::container_.back(); }

  /**
   * @brief Removes the first element from the Queue
   * 
   * @note If container is empty nothing is done
  */
  void pop() {
    Deque<T>::container_.popFront();
  }

  /* ========================================================================= */
  /*                        Bonus Methods (insert_many)                        */
  /* ========================================================================= */

  /**
   * @brief Appends new elements to the end of the Queue
  */
  template <typename... Args>
  void insert_many_back(Args&&... args) {
    Deque<T>::container_.insert_many_back(args...);
  }

  // all other methods are inherited from Deque
};

}

#endif // S21_QUEUE_H_