#ifndef S21_MAP_H_
#define S21_MAP_H_

#include <vector>
#include <utility>

#include "s21_container.h"
#include "../array_exception.h"
#include "s21_base_tree.h"

namespace s21 {

// Implementation of a map collections

template <typename Key, typename T>
class Map : public BaseTree<Key, T> {
public:
  // forward declarations for iterators
  class Iterator;
  class ConstIterator;

private:
  // type overrides to make class code easy to understand (really..?)
  using key_type = Key;
  using mapped_type = T;

  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;

  using iterator = Iterator;
  using const_iterator = ConstIterator;

  using Tree = BaseTree<Key, T>;
  using Node = typename Tree::Node;

public:

/* ========================================================================= */
/*                       Constructors and Destructors                        */
/* ========================================================================= */

  /**
   * @brief Default constructor, creates an empty map
   * 
   * @note Does nothing because every variable initial value is
   * already map
  */
  Map() : BaseTree<key_type, mapped_type>() {}

  /**
   * @brief Initializer list constructor, creates the map initizialized using std::initializer_list
   * 
   * @note For now using std pair because initializer_list takes a single template parameter
   * Maybe this constructor should be moved to a derived class. This is for later to decide
  */
  Map(std::initializer_list<value_type> const &items) {
    for (value_type item: items) {
      insert(item);
    }
  }

  /**
   * @brief Copy constructor
   * 
   * @note Performs shallow copy of passed parameter other
  */
  Map(const Map& other) : BaseTree<key_type, mapped_type>(other) {}

  /**
   * @brief Move constructor
  */
  Map(Map&& other) : BaseTree<key_type, mapped_type>(std::move(other)) {}

  /**
   * @brief Destructor
  */
  ~Map() { this->clear(); }

  /**
   * @brief Assignment operator overload for moving an object
  */
  Map& operator=(Map &&other) {
    Tree::operator=(std::move(other));

    return *this;
  }


/* ========================================================================= */
/*                               Main Methods                                */
/* ========================================================================= */

  /**
   * @brief Access a specified element with bounds checking
   * 
   * @throws ArrayException if key is not in the map
  */
  T& at(const Key& key) {
    return Tree::find(key)->value;
  }

  /**
   * @brief Access or insert specified element
   * 
   * @note Accesses a specified elements if it exsits in a map, othersize
   * inserts new element with specified key
  */
  T& operator[](const Key& key) {
    try {
      return at(key);
    } catch (ArrayException &error) {
      return *(insert(key, T()).first);
    }
  }

  /**
   * @brief Inserts a node and returns an iterator to where the element is in 
   * the container and bool denoting whether the insertion took place
  */
  std::pair<iterator, bool> insert(const value_type& value) {
    return insert(value.first, value.second);
  }

  /**
   * @brief Inserts a value by key and returns an iterator to where the element 
   * is in the container and bool denoting whether the insertion took place
  */
  std::pair<iterator, bool> insert(const Key& key, const T& obj) {
    if (!Tree::contains(key)) {
      auto insert_result = Tree::insert(key, obj);
      return std::make_pair(Iterator(*this, insert_result.first), insert_result.second);
    } else {
      return std::make_pair(Iterator(*this, Tree::find(key)), false);
    }
  }

  /**
   * @brief Inserts an element or assigns to the current element if the key already exists
   * 
   * @note Could improve efficiency
   * But my brain is too lazy now
   * 
   * Could this return false?
  */
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
    // could do this in a more efficient way, of course
    (*this)[key] = obj;

    return std::make_pair(Iterator(*this, Tree::find(key)), true);
  }

  /**
   * @brief Erases an element at pos in the map
  */
  bool erase(iterator pos) {
    return Tree::remove(pos.getNode()->key);
  }


/* ========================================================================= */
/*                                Iterators                                  */
/* ========================================================================= */

  class Iterator : public Tree::Iterator {
  public:
    /**
     * @brief Iterator constructor. Sets the current position to the beginning of the tree
    */
    Iterator(const Map<key_type, mapped_type>& map) : Tree::Iterator(map) {}

    /**
     * @brief Iterator constructor. Sets the current position to the given node
    */
    Iterator(const Map<key_type, mapped_type>& map, Node* node) : Tree::Iterator(map, node) {}

    /**
     * @brief Copy constructor
     * 
     * @note Necessary for passing iterators to funcitons and returning them as the result
    */
    Iterator(const iterator& other) : Tree::Iterator(other) {}

    /**
     * @brief Dereferencing operator. Returns a reference to the value pointed by the iterator
     * 
     * @throws ArrayException if current position is not map (at the end)
    */
    mapped_type& operator*() const {
      return Tree::Iterator::operator*()->value;
    }

    /**
     * @brief Increment operator. Moves the iterator to the next element (postfix version)
     * 
     * @throws ArrayException if current position is not map (at the end)
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
     * @throws ArrayException if current position is not map (at the end) list is circular
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
    ConstIterator(const Map<key_type, mapped_type>& map) : Iterator(map) {}

    /**
     * @brief Iterator constructor. Sets the current position to the given node
    */
    ConstIterator(const Map<key_type, mapped_type>& map, Node *node) : Iterator(map, node) {}

    /**
     * @brief Copy constructor
     * 
     * @note Necessary for passing iterators to funcitons and returning them as the result
    */
    ConstIterator(const ConstIterator& other) : Iterator(other) {}

    /**
     * @brief Dereferencing operator. Returns a reference to the value pointed by the iterator
    */
    const mapped_type& operator*() const {
        return this->Iterator::operator*();
    }

    /**
     * @brief Increment operator. Moves the iterator to the next element (postfix version)
     * 
     * @throws ArrayException if current position is not map (at the end)
    */
    ConstIterator& operator++() {
        this->Iterator::operator++();

        return *this;
    }

    /**
     * @brief Decrement operator. Moves the iterator to the previous element (postfix version)
     * 
     * @throws ArrayException if current position is not map (at the end) list is circular
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
        result.push_back(insert(arg.first, arg.second));
    }

    return result;
  }

};

}

#endif // S21_MAP_H_