#ifndef S21_SET_H_
#define S21_SET_H_

#include <vector>
#include <utility>

#include "s21_container.h"
#include "../array_exception.h"
#include "s21_base_tree.h"

namespace s21 {

// Implementation of a set collections

template <typename T>
class Set : public BaseTree<T, bool> {
public:
  // forward declarations for iterators
  class Iterator;
  class ConstIterator;

private:
  // type overrides to make class code easy to understand (really..?)
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;

  using iterator = Iterator;
  using const_iterator = ConstIterator;

  using Tree = BaseTree<T, bool>;
  using Node = typename Tree::Node;

public:

/* ========================================================================= */
/*                       Constructors and Destructors                        */
/* ========================================================================= */

  /**
   * @brief Default constructor, creates an empty set
   * 
   * @note Does nothing because every variable initial value is
   * already set
  */
  Set() : BaseTree<T, bool>() {}

  /**
   * @brief Initializer list constructor, creates the set initizialized using std::initializer_list
   * 
   * @note For now using std pair because initializer_list takes a single template parameter
   * Maybe this constructor should be moved to a derived class. This is for later to decide
  */
  Set(std::initializer_list<value_type> const &items) {
    for (value_type item: items) {
      insert(item);
    }
  }

  /**
   * @brief Copy constructor
   * 
   * @note Performs shallow copy of passed parameter other
  */
  Set(const Set& other) : BaseTree<T, bool>(other) {}

  /**
   * @brief Move constructor
  */
  Set(Set&& other) : BaseTree<T, bool>(std::move(other)) {}

  /**
   * @brief Destructor
  */
  ~Set() { this->clear(); }

  /**
   * @brief Assignment operator overload for moving an object
  */
  Set& operator=(Set &&other) {
    Tree::operator=(std::move(other));

    return *this;
  }


/* ========================================================================= */
/*                               Main Methods                                */
/* ========================================================================= */

  /**
   * @brief Inserts a node and returns an iterator to where 
   * the element is in the container and bool denoting 
   * whether the insertion took place
   * 
   * @note Because set cannot contain duplicates we either
   * call insert from the base class or return a pair with iterator
   * set to the existing element with passed value and a false denoting that insertion
   * did not took place
  */
  std::pair<iterator, bool> insert(const value_type& value) {
    if (!Tree::contains(value)) {
      // construct a pair of Iterator and bool from pair of Node and bool
      auto insert_result = Tree::insert(value, false);
      return std::make_pair(Iterator(*this, insert_result.first), insert_result.second);
    } else {
      return std::make_pair(Iterator(*this, Tree::find(value)), false);
    }
  }

  /**
   * @brief Erases an element at pos in the set
  */
  bool erase(iterator pos) {
    return Tree::remove(*pos);
  }

  /**
   * @brief Finds an element with a specific key in the tset
   * 
   * @throws ArrayException if element with specified key is not in the set or
   * if set is empty
  */
  Iterator find(const T& value) {
    return Iterator(*this, Tree::find(value));
  }

/* ========================================================================= */
/*                                Iterators                                  */
/* ========================================================================= */

  class Iterator : Tree::Iterator {
  public:
    /**
     * @brief Iterator constructor. Sets the current position to the beginning of the tree
    */
    Iterator(const Set<value_type>& set) : Tree::Iterator(set) {}

    /**
     * @brief Iterator constructor. Sets the current position to the given node
    */
    Iterator(const Set<value_type>& set, Node* node) : Tree::Iterator(set, node) {}

    /**
     * @brief Copy constructor
     * 
     * @note Necessary for passing iterators to funcitons and returning them as the result
    */
    Iterator(const iterator& other) : Tree::Iterator(other) {}

    /**
     * @brief Dereferencing operator. Returns a reference to the value pointed by the iterator
     * 
     * @throws ArrayException if current position is not set (at the end)
    */
    const_reference operator*() const {
      return Tree::Iterator::operator*()->key;
    }

    /**
     * @brief Increment operator. Moves the iterator to the next element (postfix version)
     * 
     * @throws ArrayException if current position is not set (at the end)
    */
    Iterator& operator++() {
      if (Tree::Iterator::current_ == nullptr) {
          throw ArrayException("Cannot increment an unset iterator");
      }

      Tree::Iterator::current_ = Tree::Iterator::findSuccessor(Tree::Iterator::current_);

      return *this;
    }

    /**
     * @brief Decrement operator. Moves the iterator to the previous element (postfix version)
     * 
     * @throws ArrayException if current position is not set (at the end) list is circular
    */
    Iterator& operator--() {
      if (Tree::Iterator::current_ == nullptr) {
          throw ArrayException("Cannot decrement an unset iterator");
      }

      Tree::Iterator::current_ = Tree::Iterator::findPredecessor(Tree::Iterator::current_);

      return *this;
    }

    /**
     * @brief Operator for comapring two iterators on equality. Returns true
     * if both iterators point to the same element, false otherwise
    */
    bool operator==(const Iterator& other) const {
      return this->Tree::Iterator::operator==(other);
    }

    /**
     * @brief Operator for comapring two iterators on unequality. Returns true
     * if iterators point to different elements, false otherwise
    */
    bool operator!=(const Iterator& other) const {
      return this->Tree::Iterator::operator!=(other);
    }

    /**
     * @brief Assignment operator. Performs a shallow copy of the given iterator
    */
    Iterator& operator=(const Iterator& other) {
      Tree::Iterator::current_ = other.current_;

      return *this;
    }
  };

  class ConstIterator : public Iterator {
  public:
    /**
     * @brief Iterator constructor. Sets the current position to the beginning of the tree
    */
    ConstIterator(const Set<value_type>& set) : Iterator(set) {}

    /**
     * @brief Iterator constructor. Sets the current position to the given node
    */
    ConstIterator(const Set<value_type>& set, Node *node) : Iterator(set, node) {}

    /**
     * @brief Copy constructor
     * 
     * @note Necessary for passing iterators to funcitons and returning them as the result
    */
    ConstIterator(const ConstIterator& other) : Iterator(other) {}

    /**
     * @brief Dereferencing operator. Returns a reference to the value pointed by the iterator
    */
    const_reference operator*() const {
        return this->Iterator::operator*();
    }

    /**
     * @brief Increment operator. Moves the iterator to the next element (postfix version)
     * 
     * @throws ArrayException if current position is not set (at the end)
    */
    ConstIterator& operator++() {
        this->Iterator::operator++();

        return *this;
    }

    /**
     * @brief Decrement operator. Moves the iterator to the previous element (postfix version)
     * 
     * @throws ArrayException if current position is not set (at the end) list is circular
    */
    ConstIterator& operator--() {
        this->Iterator::operator--();

        return *this;
    }

    /**
     * @brief Assignment operator. Performs a shallow copy of the given iterator
    */
    ConstIterator& operator=(const ConstIterator &other) {
      this->Iterator::operator=(other);

      return *this;
    }
  };

  iterator begin() {
    return Iterator(*this);
  }

  iterator end() {
    return Iterator(*this, nullptr);
  }

  const_iterator cbegin() {
    return ConstIterator(*this);
  }

  const_iterator cend() {
    return ConstIterator(*this, nullptr);
  }


  /* ========================================================================= */
  /*                        Bonus Methods (insert_many)                        */
  /* ========================================================================= */

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> result;

    for (auto arg : {args...}) {
        result.push_back(insert(arg));
    }

    return result;
  }

};

}

#endif // S21_SET_H_