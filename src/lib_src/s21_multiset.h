#ifndef S21_MULTISET_H_
#define S21_MULTISET_H_

#include <vector>
#include <utility>

#include "s21_container.h"
#include "../array_exception.h"
#include "s21_base_tree.h"

namespace s21 {

// Implementation of a multiset collections

template <typename T>
class Multiset : public BaseTree<T, bool> {
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

  using size_type = Container::size_type; // what the actual $%*@

  using Tree = BaseTree<T, bool>;
  using Node = typename Tree::Node;

public:

/* ========================================================================= */
/*                       Constructors and Destructors                        */
/* ========================================================================= */

  /**
   * @brief Default constructor, creates an empty multiset
   * 
   * @note Does nothing because every variable initial value is
   * already multiset
  */
  Multiset() : BaseTree<T, bool>() {}

  /**
   * @brief Initializer list constructor, creates the multiset initizialized using std::initializer_list
   * 
   * @note For now using std pair because initializer_list takes a single template parameter
   * Maybe this constructor should be moved to a derived class. This is for later to decide
  */
  Multiset(std::initializer_list<value_type> const &items) {
    for (value_type item: items) {
      insert(item);
    }
  }

  /**
   * @brief Copy constructor
   * 
   * @note Performs shallow copy of passed parameter other
  */
  Multiset(const Multiset& other) : BaseTree<T, bool>(other) {}

  /**
   * @brief Move constructor
  */
  Multiset(Multiset&& other) : BaseTree<T, bool>(std::move(other)) {}

  /**
   * @brief Destructor
  */
  ~Multiset() { this->clear(); }

  /**
   * @brief Assignment operator overload for moving an object
  */
  Multiset& operator=(Multiset &&other) {
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
  */
  std::pair<iterator, bool> insert(const value_type& value) {
    // construct a pair of Iterator and bool from pair of Node and bool
    auto insert_result = Tree::insert(value, false);
    return std::make_pair(Iterator(*this, insert_result.first), insert_result.second);
  }

  /**
   * @brief Erases an element at pos in the multiset
  */
  bool erase(iterator pos) {
    return Tree::remove(*pos);
  }

  /**
   * @brief Finds an element with a specific key in the multiset
   * 
   * @note Returned iterator always points to the first occurence of the element
   * with a specified value
   * 
   * @throws ArrayException if element with specified key is not in the multiset or
   * if multiset is empty
  */
  Iterator find(const T& value) {
    return Iterator(*this, Tree::find(value));
  }

  /**
   * @brief Returns the number of elements matching a specific key
   * 
   * @remark Why here it is the key and in other places it is the value. WHY?
  */
  size_type count(const_reference key) {
    return Tree::find(key)->count;
  }

  /**
   * @brief Returns an open range of elements matching a specific key
   * 
   * @throws ArrayException is specified key is not in the multiset
   * 
   * @note Open range is [begin, end)
  */
  std::pair<iterator, iterator> equal_range(const_reference key) {
    iterator start = find(key);
    iterator end = start;

    while (end != this->end() && *end == *start) {
      ++end; // find next element
    }

    return std::make_pair(start, end);
  }

  /**
   * @brief Returns an iterator to the first element not less than the given key
   * 
   * @note Value should be greater than or equal to key
  */
  iterator lower_bound(const_reference key) {
    iterator it = this->begin();

    while (it != this->end() && *it < key) {
      ++it;
    }

    return it;
  }

  /**
   * @brief returns an iterator to the first element greater than the given key
   * 
   * @brief Value should be strictly greater than key
  */
  iterator upper_bound(const_reference key) {
    iterator it = this->begin();

    while (it != this->end() && *it <= key) {
      ++it;
    }

    return it;
  }

/* ========================================================================= */
/*                                Iterators                                  */
/* ========================================================================= */

  class Iterator : Tree::Iterator {
  private:
    int index_ = 1; // index of duplicate elements
    // indexation starts from 1 (i.e. we are at the first duplicate element)

  public:
    /**
     * @brief Iterator constructor. Sets the current position to the beginning of the tree
    */
    Iterator(const Multiset<value_type>& multiset) : Tree::Iterator(multiset) {}

    /**
     * @brief Iterator constructor. Sets the current position to the given node
    */
    Iterator(const Multiset<value_type>& multiset, Node* node) : Tree::Iterator(multiset, node) {}

    /**
     * @brief Copy constructor
     * 
     * @note Necessary for passing iterators to funcitons and returning them as the result
    */
    Iterator(const iterator& other) : Tree::Iterator(other) {}

    /**
     * @brief Dereferencing operator. Returns a reference to the value pointed by the iterator
     * 
     * @throws ArrayException if current position is not multiset (at the end)
    */
    const_reference operator*() const {
      return Tree::Iterator::operator*()->key;
    }

    /**
     * @brief Increment operator. Moves the iterator to the next element (postfix version)
     * 
     * @throws ArrayException if current position is not multiset (at the end)
    */
    Iterator& operator++() {
      if (Tree::Iterator::current_ == nullptr) {
        throw ArrayException("Cannot increment an unset iterator");
      }

      if (index_ < Tree::Iterator::current_->count) {
        ++index_;
      } else { // move only if there are no more duplicates
        index_ = 1;
        Tree::Iterator::current_ = Tree::Iterator::findSuccessor(Tree::Iterator::current_);
      }

      return *this;
    }

    /**
     * @brief Decrement operator. Moves the iterator to the previous element (postfix version)
     * 
     * @throws ArrayException if current position is not multiset (at the end) list is circular
    */
    Iterator& operator--() {
      if (Tree::Iterator::current_ == nullptr) {
        throw ArrayException("Cannot decrement an unset iterator");
      }

      if (index_ > 1) {
        --index_;
      } else {
        Tree::Iterator::current_ = Tree::Iterator::findPredecessor(Tree::Iterator::current_);
        if (Tree::Iterator::current_ != nullptr) {
          index_ = Tree::Iterator::current_->count;
        }
      }

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

  // const iterator shouldn't even exist for this collection
  // because there is no real difference between a normal iterator and this one
  class ConstIterator : public Iterator {
  public:
    /**
     * @brief Iterator constructor. Sets the current position to the beginning of the tree
    */
    ConstIterator(const Multiset<value_type>& multiset) : Iterator(multiset) {}

    /**
     * @brief Iterator constructor. Sets the current position to the given node
    */
    ConstIterator(const Multiset<value_type>& multiset, Node *node) : Iterator(multiset, node) {}

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
     * @throws ArrayException if current position is not multiset (at the end)
    */
    ConstIterator& operator++() {
        this->Iterator::operator++();

        return *this;
    }

    /**
     * @brief Decrement operator. Moves the iterator to the previous element (postfix version)
     * 
     * @throws ArrayException if current position is not multiset (at the end) list is circular
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
  std::vector<std::pair<iterator,bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> result;

    for (auto arg : {args...}) {
        result.push_back(insert(arg));
    }

    return result;
  }
};

}

#endif // S21_MULTISET_H_