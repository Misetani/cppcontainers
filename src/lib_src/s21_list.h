#ifndef S21_LIST_H_
#define S21_LIST_H_

#include <cstddef>
#include <iostream>

#include "s21_container.h"
#include "../array_exception.h"

namespace s21 {

// Implementation of a list collections
// with a barrier element (for a simpler implementation of methods)

template <typename T>
class List : public Container {
public:
  // forward declarations for iterators
  class Iterator;
  class ReverseIterator;
  class ConstIterator;

private:
  // type overrides to make class code easy to understand (really..?)
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;

  using iterator = Iterator;
  using const_iterator = ConstIterator;

  struct Node {
    value_type data_;
    Node *next_;
    Node *prev_;

    Node() {}
    Node(const value_type &data, Node *next = nullptr, Node *prev = nullptr) : 
      data_{ data }, next_{ next }, prev_{ prev } {}
  };

  Node nil; // nil node is used to simplify the code (barrier node)
  // we could cycle our list through it and simplify some basic list operations
  // to a major degree without sacrificing much of memory usage or efficiency

public:

/* ========================================================================= */
/*                       Constructors and Destructors                        */
/* ========================================================================= */

  /**
   * @brief Default constructor. Creates an empty list
   * 
   * @note Initializes an empty list, with a barrier element correctly set up
  */
  List() {
    nil.next_ = &nil;
    nil.prev_ = &nil;
  }

  /**
   * @brief Parameterized constructor, creates the list of size n.
   * All elements are initialized to the default value for the type
  */
  List(size_type n);

  /**
   * @brief Initializer list constructor, 
   * creates a list initizialized using std::initializer_list
  */
  List(std::initializer_list<value_type> const& items);

  /**
   * @brief Copy constructor. Creates a copy of the given list
   * 
   * @note Performs deep copy of a list, result is two identical lists
  */
  List(const List<value_type> &other);

  /**
   * @brief Move constructor. Moves resourses from the given list to the current one
   * 
   * @note Performs a shallow copy of a list, result is a single list with resources
   * stolen from the given list
  */
  List(List<value_type> &&other);

  /**
   * @brief Destructor. Clears the list and frees all resources
  */
  ~List() { clear(); }

  /**
   * @brief Assignment operator overload for moving an object
  */
  List<value_type>& operator=(List<value_type> &&other);

/* ========================================================================= */
/*                         Methods for modifying a List                      */
/* ========================================================================= */

  /**
   * @brief Removes all elements from the container
  */
  void clear();

  /**
   * @brief Inserts an element at the given index
   * 
   * @return true if the element was inserted successfully, false otherwise
  */
  bool insert(size_type index, const value_type &value);

  /**
   * @brief Gets the element at the given index
   * 
   * @return Value of the element at the given index
   * @throws ArrayException if the index is out of range
  */
  value_type get(size_type index) const;

  /**
   * @brief Finds position of the given value in the container
   * 
   * @return Index of the given value in the container or -1 if the value is not found
  */
  int indexOf(const_reference value) const;

  /**
   * @brief Cheks if the container contains the given value
   * 
   * @return true if the container contains the given value, false otherwise
  */
  bool contains(const_reference value) const { return indexOf(value) != -1; }

  /**
   * @brief Sets the element at the given index to the given value
   * 
   * @return true if the element was set successfully, false otherwise
  */
  bool set(size_type index, const_reference value);

  /**
   * @brief Removes the element with a given value
   * 
   * @return true if the element was removed successfully, false otherwise
  */
  bool remove(const_reference value);

  /**
   * @brief Removes the element at the given index
   * 
   * @return true if the element was removed successfully, false otherwise
  */
  bool removeAt(size_type index);


  // new stuff...

  /**
   * @brief Access the first element of the list
   * 
   * @throws ArrayException if list is empty
  */
  const_reference front();

  /**
   * @brief Access the last element of the list
   * 
   * @throws ArrayException if list is empty
  */
  const_reference back();

  /**
   * @brief Inserts element into concrete pos and returns 
   * the iterator that points to the new element
  */
  Iterator insert(Iterator pos, const_reference value);

  /**
   * @brief Erases an element at pos in the list. Moves pos to the next element
   * in the list
   * 
   * @note It doesn't return anything in specification. But IMHO this is stupid.
   * After the function call iterator will become useless (it will point to an
   * element that doesn't even exist anymore)
   * 
   * Using your brain is better than following some mystical specification
   * blindly 
  */
  bool erase(Iterator& pos);

  /**
   * @brief Adds an element to the end of the list
  */
  void pushBack(const_reference value);

  /**
   * @brief Removes the last element from the list
   * 
   * @note No checks performed. If list is empty it will do nothing
  */
  void popBack();

  /**
   * @brief Adds an element to the head of the list
  */
  void pushFront(const_reference value);

  /**
   * @brief Removes the first element of the list
   * 
   * @note No checks performed. If list is empty it will do nothing
  */
  void popFront();

  /**
   * @brief Swaps the contents of two lists
   * 
   * @note Simply "moves" data from one list to another, no real data is copied,
   * so operation is very efficient
  */
  void swap(List<value_type> &other);

  /**
   * @brief Merges two sorted lists.
   * 
   * @note We assume that both lists are in sorted order. Result is a
   * sorted list with all elements from both lists. Second list is left
   * empty after the operation
  */
  void merge(List<value_type> &other);

  /**
   * @brief Transfers elements from list other starting from pos
   * 
   * @note Pushes all elements from other to the end of the list. Other
   * list is left empty efter the operation
  */
  void splice(ConstIterator pos, List<value_type>& other);

  /**
   * @brief Reverses the order of the elements
  */
  void reverse();

  /**
   * @brief Removes consecutive duplicate elements
  */
  void unique();

  /**
   * @brief Sorts the elements
   * 
   * @note Uses quicksort algorithm. Complexity is O(n*log(n)).
   * 
   * Quicksort is generally thought of as the most efficient 
   * 'general' sorting algorithm, where nothing is known about 
   * the inputs to the array, and it's more efficient than 
   * insertion sort on large lists
  */
  void sort();

  void quickSort(ConstIterator start, ConstIterator end);

  ConstIterator partition(ConstIterator start, ConstIterator end);


/* ========================================================================= */
/*                                Iterators                                  */
/* ========================================================================= */

  // would like to use a reference insead of a pointer, but have no idea how to properly
  // implement a reference copying without it makinkg a copy of a whole collection
  // something to think about...

  class Iterator {
  protected:
    List<value_type>* list_; // const pointer, cannot change list, can change *list
    Node *current_;

  public:
    /**
     * @brief Iterator constructor. Sets the current position to the beginning of the list
    */
    Iterator(List<value_type>* list) : list_{ list } { 
      current_ = list->nil.next_; // set position to the first element
    }

    /**
     * @brief Iterator constructor. Sets the current position to the given node
    */
    Iterator(List<value_type>* list, Node *node) : list_{ list }, current_{ node } {}

    /**
     * @brief Copy constructor
     * 
     * @note Necessary for passing iterators to funcitons and returning them as the result
    */
    Iterator(const Iterator& other) {
      list_ = other.list_;
      current_ = other.current_;
    }

    Node* getNode() { return current_; }

    /**
     * @brief Comparison operator. Compares two iterators on equality
    */
    bool operator==(const Iterator& other) const {
        return current_ == other.current_;
    }

    /**
     * @brief Comparison operator. Compares two iterators on inequality
    */
    bool operator!=(const Iterator& other) const {
        return current_ != other.current_;
    }

    /**
     * @brief Dereferencing operator. Returns a reference to the value pointed by the iterator
    */
    reference operator*() const {
        if (current_ == &(list_->nil)) {
            throw ArrayException("Iterator is at the end");
        }

        return current_->data_;
    }

    /**
     * @brief Increment operator. Moves the iterator to the next element (postfix version)
     * 
     * @note No check is performed because list is circular
    */
    Iterator& operator++() {
        current_ = current_->next_;
        return *this;
    }

    /**
     * @brief Decrement operator. Moves the iterator to the previous element (postfix version)
     * 
     * @note No check is performed because list is circular
    */
    Iterator& operator--() {
        current_ = current_->prev_;
        return *this;
    }

    /** 
     * @brief Assignment operator. Performs a shallow copy of the given iterator
     * (no data is copied, only the current position and the current list pointers are copied)
     * 
     * @note Would be a nice idea to do it with a reference for a list_, but still
     * no idea how to accomlish this. Doesn't really matter, because this option is not
     * really that worse
    */
    Iterator& operator=(const Iterator &other) {
      list_ = other.list_;
      current_ = other.current_;

      return *this;
    }
  };

  class ConstIterator : public Iterator {
  public:
    /**
     * @brief Iterator constructor. Sets the current position to the beginning of the tree
    */
    ConstIterator(List<value_type>* list) : Iterator(list) {}

    /**
     * @brief Iterator constructor. Sets the current position to the given node
    */
    ConstIterator(List<value_type>* list, Node *node) : Iterator(list, node) {}

    /**
     * @brief Copy constructor
     * 
     * @note Necessary for passing iterators to funcitons and returning them as the result
    */
    ConstIterator(const ConstIterator& other) : Iterator(other) {}

    const Node* getNode() const { return this->current_; }

    /**
     * @brief Dereferencing operator. Returns a reference to the value pointed by the iterator
    */
    const_reference operator*() const {
        return this->Iterator::operator*();
    }

    /**
     * @brief Increment operator. Moves the iterator to the next element (postfix version)
     * 
     * @note No check is performed because list is circular
    */
    ConstIterator& operator++() {
        this->Iterator::operator++();

        return *this;
    }

    /**
     * @brief Decrement operator. Moves the iterator to the previous element (postfix version)
     * 
     * @note No check is performed because list is circular
    */
    ConstIterator& operator--() {
        this->Iterator::operator--();

        return *this;
    }

    /**
     * @brief Assignment operator. Performs a shallow copy of the given iterator
     * 
     * @note Unable to inherit it correctly. Default assignment operator generates automaticall and
     * shadows operator inherited from default class. Trying to call assignment defined for a base
     * gives me an error. No idea how to solve this
    */
    ConstIterator& operator=(const ConstIterator &other) {
      this->Iterator::operator=(other);

      return *this;
    }
  };

  class ReverseIterator {
  private:
    Iterator iterator_;

  public:
    /**
     * @brief Reverse Iterator constructor. Sets the current position to the end of the list
    */
    ReverseIterator(List<value_type>* list) : iterator_(list, list->nil.prev_) {}

    /**
     * @brief Iterator constructor. Sets the current position to the given node
    */
    ReverseIterator(List<value_type>* list, Node *node) : iterator_(list, node) {}

    Node* getNode() { return iterator_.getNode(); }

    /**
     * @brief Comparison operator. Compares two reverse iterators on equality
    */
    bool operator==(const ReverseIterator& other) const {
        return iterator_ == other.iterator_;
    }

    /**
     * @brief Comparison operator. Compares two reverse iterators on inequality
    */
    bool operator!=(const ReverseIterator& other) const {
        return iterator_ != other.iterator_;
    }

    /**
     * @brief Dereferencing operator. Returns a reference to the value pointed by the  reverse iterator
    */
    reference operator*() const {
        return *iterator_;
    }

    /**
     * @brief Increment operator. Moves the reverse iterator to the previous element (postfix version)
    */
    ReverseIterator& operator++() {
        --iterator_;
        return *this;
    }

    /**
     * @brief Decrement operator. Moves the iterator to the next element (postfix version)
    */
    ReverseIterator& operator--() {
        ++iterator_;
        return *this;
    }

    /** 
     * @brief Assignment operator. Just calls the assignment operator of the forward iterator
    */
    ReverseIterator& operator=(const ReverseIterator &other) {
      iterator_ = other.iterator_;

      return *this;
    }
  };

  /**
   * @brief Returns an iterator to the beginning of the container
   * @note Iterator is set to the first element of the container
  */
  Iterator begin() {
    return Iterator(this);
  }

  /**
   * @brief Returns an iterator to the end of the container (barrier element)
   * @note Iterator is set to the element after the last element of the container (barrier element)
  */
  Iterator end() {
    return Iterator(this, &nil);
  }

  /**
   * @brief Returns an iterator to the beginning of the container
   * @note Iterator is set to the first element of the container
  */
  ConstIterator cbegin() {
    return ConstIterator(this);
  }

  /**
   * @brief Returns an iterator to the end of the container (barrier element)
   * @note Iterator is set to the element after the last element of the container (barrier element)
  */
  ConstIterator cend() {
    return ConstIterator(this, &nil);
  }

  /**
   * @brief Returns a reverse iterator to the beginning of the container
   * @note Iterator is set to the last element of the container
  */
  ReverseIterator rbegin() {
    return ReverseIterator(this);
  }

  /**
   * @brief Returns a reverse iterator to the end of the container
   * @note Iterator is set to the element before the first element of the container (barrier element)
  */
  ReverseIterator rend() {
    return ReverseIterator(this, &nil);
  }


/* ========================================================================= */
/*                        Bonus Methods (insert_many)                        */
/* ========================================================================= */

/**
 * @brief Inserts new elements into the container directly before pos
 * 
 * @note Case for non-zero variadic arguments. Calls itself recursively extracting
 * a single argument on each call
*/
template <typename... Args>
Iterator& insert_many(Iterator& pos, const_reference head, const Args&... tail) {
  // insert a single element extracted from the front of the variadic template
  insertNode(pos.getNode(), head);
  // pass the tail of the variadic template to insert_many again
  insert_many(pos, tail...);

  return pos;
}

/**
 * @brief Insert many base case (no arguments in the variadic template)
 * 
 * @note If insert_many is called with no arguments, this version will be called.
 * It also will be called at the end of recursive calls of insert_many
*/
Iterator& insert_many(Iterator& pos) { 
  // like do nothing?

  return pos;
}

/**
 * @brief Appends new elements to the end of the container
*/
template <typename... Args>
void insert_many_back(const_reference head, Args&&... tail) {
  pushBack(head);

  insert_many_back(tail...);
}

void insert_many_back() {
  return;
}

/**
 * @brief Appends new elements to the top of the container
 * 
 * @note Inserts elements in reverse order. The last passed will be the first in the list.
 * Maybe I should fix this, but I don't know how and this is not that important
*/
template <typename... Args>
void insert_many_front(const_reference head, Args&&... tail) {
  pushFront(head);

  insert_many_front(tail...);
}

void insert_many_front() {
  return;
}

/* ========================================================================= */
/*                          Helper Private Methods                           */
/* ========================================================================= */

private:

  /**
   * @brief Finds the node at the given index in the list
   * 
   * @note No checks performed
  */
  Node* findNodeByIndex(size_type index) const;

  /**
   * @brief Finds the node with the given value in the list
  */
  Node* findNodeByValue(const_reference value, int &index) const;

  /**
   * @brief Removes the given node from the list
   * 
   * @note Rewrites pointers, decrements size and clears memory, no checks performed
  */
  void removeNode(Node *node);

  /**
   * @brief Inserts a new node with the given value before the given node
   * 
   * @note No checks performed, all values should be checked beforehand
  */
  void insertNode(Node *p, const_reference value);

  /**
   * @brief Takes resources from the other list and trasnfers it to the current list
   * 
   * @note No checks performed. Used by move constructor and move assignment
  */
  void stealResources(List<value_type> &&other);


/* ========================================================================= */
/*                           Helper Public Methods                           */
/* ========================================================================= */

public:

  void print() const;
};


/* ========================================================================= */
/*                       Constructors Implementation                         */
/* ========================================================================= */

template <typename T>
List<T>::List(size_type n) : List() {
  for (size_type i = 0; i < n; ++i) {
    this->pushBack(T()); // push default value to the list
  }
}

template <typename T>
List<T>::List(std::initializer_list<value_type> const& items) : List() {
  for (const_reference item: items) {
    this->pushBack(item);
  }
}

template <typename T>
List<T>::List(const List<value_type> &other) : List() {
  Node *p = other.nil.next_; // first node of the other list

  while (p != &other.nil) {
    this->pushBack(p->data_);
    p = p->next_;
  }
}

template <typename T>
List<T>::List(List<value_type> &&other) : List() {
  if (this == &other) {
    return;
  }

  stealResources(std::move(other));
}

template <typename T>
List<T>& List<T>::operator=(List<T> &&other) {
  if (this == &other) {
    return *this;
  }

  // clean our list
  clear();

  stealResources(std::move(other));

  return *this;
}



/* ========================================================================= */
/*                         Interface Implementation                          */
/* ========================================================================= */

template <typename T>
void List<T>::clear() {
  if (this->size() == 0) {
    return;
  }

  Node *p = nil.next_;

  while (p != &nil) {
    Node *temp = p;
    p = p->next_;

    delete temp;
  }

  this->size_ = 0;
}

template <typename T>
bool List<T>::insert(size_type index, const_reference value) {
  // this will return false even if the index passed is a negative integer!!! 
  // that's quite fun =)
  if (index > this->size()) {
    return false;
  }

  Node *p = findNodeByIndex(index);

  insertNode(p, value);

  return true;
}

// basically the same thing as insertion only without insertion
// hence no comments needed
template <typename T>
T List<T>::get(size_type index) const {
  if (index >= this->size()) {
    throw ArrayException("Index out of range");
  }

  return findNodeByIndex(index)->data_;
}

template <typename T>
int List<T>::indexOf(const_reference value) const {
  int i = 0;
  Node *p = findNodeByValue(value, i);

  if (p == &nil) { // traversed a list, no match found
      return -1;
  } else {
      return i;
  }
}

// basically the same thing as insertion only without insertion
template <typename T>
bool List<T>::set(size_type index, const_reference value) {
  if (index >= this->size()) {
    return false;
  }

  Node *p = findNodeByIndex(index);

  p->data_ = value;

  return true;
}

template <typename T>
bool List<T>::remove(const_reference value) {
  int i = 0; // we don't need this, but it is the easiest way to go
  Node *p = findNodeByValue(value, i);

  if (p == &nil) { // traversed a list, no match found
      return false;
  } 

  removeNode(p);

  return true;
}

template <typename T>
bool List<T>::removeAt(size_type index) {
  if (index >= this->size()) {
    return false;
  }

  Node *p = findNodeByIndex(index);

  removeNode(p);

  return true;
}

template <typename T>
const T& List<T>::front() {
  if (this->size() == 0) {
    throw ArrayException("List is empty");
  }

  return nil.next_->data_;
}

template <typename T>
const T& List<T>::back() {
  if (this->size() == 0) {
    throw ArrayException("List is empty");
  }

  return nil.prev_->data_;
}

template <typename T>
typename List<T>::Iterator List<T>::insert(List<T>::Iterator pos, const_reference value) {
  // all code is already written! Don't have to do anything

  insertNode(pos.getNode(), value);

  return pos;
}

template <typename T>
bool List<T>::erase(List<T>::Iterator& pos) {
  if (pos.getNode() == &nil) {
    return false;
  }
  
  Iterator next = pos;
  ++next;

  removeNode(pos.getNode());

  pos = next;

  return true;
}

template <typename T>
void List<T>::pushBack(const_reference value) {
  insertNode(&nil, value);
}

template <typename T>
void List<T>::pushFront(const_reference value) {
  insertNode(nil.next_, value);
}

template <typename T>
void List<T>::popBack() {
  if (this->size() == 0) {
    return;
  }

  removeNode(nil.prev_);
}

template <typename T>
void List<T>::popFront() {
  if (this->size() == 0) {
    return;
  }
  
  removeNode(nil.next_);
}

template <typename T>
void List<T>::swap(List<T> &other) {
  if (this == &other) {
    return;
  }
  
  List<T> temp(std::move(*this));

  *this = std::move(other);

  other = std::move(temp);
}

template <typename T>
void List<T>::merge(List<T> &other) {
  // start from the first elements of both lists
  Iterator this_it = this->begin();
  Iterator other_it = other.begin();

  // traverse them while there is something to be inserted
  while (other_it != other.end()) {
    // we traversed through this list, just add all remaining elements
    if (this_it == this->end()) {
      pushBack(*other_it);
      ++other_it;
      other.popFront();
    } else if (*other_it < *this_it) {
      insert(this_it, *other_it);
      ++other_it;
      other.popFront();
    }
    
    // in case we already traversed through this list
    // because our list is circular we will continue moving
    // but all elements will be less then all elements left in the
    // other list, so it's equalent to pushing back
    ++this_it;
  }
}

template <typename T>
void List<T>::splice(ConstIterator pos, List<T>& other) {
  // nothing to check, really. Just this simple is how it's done

  while (pos != other.cend()) {
    pushBack(*pos);
    ++pos;
  }
}

template <typename T>
void List<T>::reverse() {
  if (this->size() == 0) {
    return;
  }

  ConstIterator cit = cbegin();

  for (size_type i = 0; i < this->size() - 1; ++i) {
    // insert before the first element, element from the back of the list
    insert(cit, back());
    popBack();
  }
}

template <typename T>
void List<T>::unique() {
  Iterator it = ++(begin()); // second element

  while (it != end()) {
    if (*it == *(--it)) { // first and second
      erase(it); // erase first
    } else {
      ++(++it); // move to the next element (third, we were at first)
    }
  }
}

template <typename T>
void List<T>::sort() {
  quickSort(cbegin(), --(cend())); // sort in range [cbegin(), cend()]
}

template <typename T>
void List<T>::quickSort(ConstIterator start, ConstIterator end) {
  if (start == end) { // one element in partition left
    return;
  }

  // get iterator, pointing at pivot element
  ConstIterator pivot = partition(start, end);

  // recursively sort parts to the left and to the right of pivot
  quickSort(start, --pivot); // pass part to the left of pivot
  if (++pivot != end) { // return to pivot
    quickSort(++pivot, end); // pass part to the right of pivot
  }
}

template <typename T>
typename List<T>::ConstIterator List<T>::partition(ConstIterator start, ConstIterator end) {  
  ConstIterator pivot = end;
  ++end; // we will insert after end, not before it

  if (start == pivot) {
    return pivot;
  }

  while (start != pivot) {
    if (*pivot < *start) {
      insert(end, *start);
      erase(start);
    } else {
      ++start;
    }
  }

  return pivot;
}


/* ========================================================================= */
/*                    Private Helper Methods Implementation                  */
/* ========================================================================= */

template <typename T>
typename List<T>::Node* List<T>::findNodeByIndex(size_type index) const {
  Node *p = nil.next_;
  
  // some optimization to trawerse list in the direction with the
  // smallest number of nodes to pass through
  if (index <= this->size() / 2) { // insert in the forward direction
    while (p != &nil && index > 0) { // find the insertion place
      p = p->next_;
      --index;
    }
  } else { // insert in the backward direction
    p = nil.prev_;
    while (p != &nil && index < this->size()) { // find the insertion place
      p = p->prev_;
      ++index;
    }
    // because we go backward, we get to the element 
    //one forward of the insertion point
    p = p->next_;
  }

  // at the moment p is pointing to the node after insertion place

  return p;
}

template <typename T>
typename List<T>::Node* List<T>::findNodeByValue(const_reference value, int &index) const {
  Node *p = nil.next_;
  while (p != &nil && p->data_ != value) {
      p = p->next_;
      ++index;
  }

  return p;
}

template <typename T>
void List<T>::removeNode(Node *node) {
  node->prev_->next_ = node->next_;
  node->next_->prev_ = node->prev_;

  delete node;

  --(this->size_);
}

template <typename T>
void List<T>::insertNode(Node *p, const_reference value) {
  // new_node is inerted between p_prev_ and p
  Node *new_node = new Node(value, p, p->prev_);

  p->prev_->next_ = new_node;
  p->prev_ = new_node;

  ++(this->size_);
}

template <typename T>
void List<T>::stealResources(List<T> &&other) {
  // steal resources from the other list
  nil.next_ = other.nil.next_;
  nil.prev_ = other.nil.prev_;

  nil.next_->prev_ = &nil;
  nil.prev_->next_ = &nil;

  this->size_ = other.size_;

  // clear the other list
  other.nil.next_ = &other.nil;
  other.nil.prev_ = &other.nil;

  other.size_ = 0;
}


/* ========================================================================= */
/*                    Public Helper Methods Implementation                   */
/* ========================================================================= */

template <typename T>
void List<T>::print() const {
  std::cout << "List: ";
    Node *p = nil.next_;
    while (p != &nil) {
        std::cout << p->data_ << " ";
        p = p->next_;
    }
    std::cout << std::endl;
}


} // namespace s21


#endif  // S21_LIST_H_