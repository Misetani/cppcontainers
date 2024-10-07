#ifndef S21_BASE_TREE_H_
#define S21_BASE_TREE_H_

#include <utility>
#include <iostream>
#include <vector>

#include "s21_container.h"
#include "s21_stack.h"
#include "../array_exception.h"

namespace s21 {

// Implementation of a base tree collections
// This collection will be basic for a set, unordered set and a map
// At the moment the underlying value structure is a simple binary search tree
// Later on this should be switched for a balanced version, like red-black tree
// or AVL

template <typename Key, typename Value>
class BaseTree : public Container {
protected:
  // forward declarations for iterators
  class Iterator;
  class ConstIterator;

private:
  // type overrides to make class code easy to understand (really..?)
  using key_type = Key;
  using value_type = Value;

  using reference = Value&;
  using key_reference = Key&;

  using const_reference = const Value&;
  using const_key_reference = const Key&;

  using iterator = Iterator;
  using const_iterator = ConstIterator;

protected:

  struct Node {
    key_type key;
    value_type value;
    int count = 0;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(const key_type& key, const value_type& value, int count) : 
      key(key), value(value), count(count) {}
  };

  Node* root_ = nullptr;


/* ========================================================================= */
/*                       Constructors and Destructors                        */
/* ========================================================================= */

  /**
   * @brief Default constructor, creates an empty tree
   * 
   * @note Does nothing because every variable initial value is
   * already set
   * 
   * @remark DONE
  */
  BaseTree() {}

  /**
   * @brief Initializer list constructor, creates the tree initizialized using std::initializer_list
   * 
   * @note For now using std pair because initializer_list takes a single template parameter
   * Maybe this constructor should be moved to a derived class. This is for later to decide
   * 
   * @remark DONE
  */
  BaseTree(std::initializer_list<std::pair<key_type, value_type> > const &items);

  /**
   * @brief Copy constructor
   * 
   * @note Performs shallow copy of passed parameter other
   * 
   * @remark DONE
  */
  BaseTree(const BaseTree& other);

  /**
   * @brief Move constructor
   * 
   * @remark DONE
  */
  BaseTree(BaseTree&& other);

  /**
   * @brief Destructor
   * 
   * @remark DONE
  */
  ~BaseTree() { clear(); }

  /**
   * @brief Assignment operator overload for moving an object
   * 
   * @remark DONE
  */
  BaseTree& operator=(BaseTree &&other);

/* ========================================================================= */
/*                               Main Methods                                */
/* ========================================================================= */

protected: // methods are used by the derived class
  /**
   * @brief Inserts a node and returns an iterator to where 
   * the element is in the container and bool denoting 
   * whether the insertion took place
   * 
   * @note Dublicates are allowed to accomodate for both set and multiset
   * behaviour
   * 
   * @remark DONE
  */
  std::pair<Node*, bool> insert(const_key_reference key, const_reference value);

  /**
   * @brief Finds an element with a specific key in the tree
   * 
   * @throws ArrayException if element with specified key is not in the tree or
   * if tree is empty
   * 
   * @remark DONE
  */
  Node* find(const_key_reference key) const;


public: // methods are the part of the derived class interface
  /**
   * @brief Clears the contents of a tree
   * 
   * @remark DONE
  */
  void clear();

  /**
   * @brief Removes a value from the tree with the key key passed as parameter
   * 
   * @remark DONE
  */
  bool remove(const_key_reference key);

  /**
   * @brief Swaps the contents of the current tree and the tree
   * passed as the argument
   * 
   * @remark DONE
  */
  void swap(BaseTree& other);

  /**
   * @brief Splices nodes from another container
   * 
   * @remark DONE
  */
  void merge(BaseTree& other);

  /**
   * @brief Checks if the container contains an element with a specific key
   * 
   * @returns true if element with specified key is in the tree, false otherwise
   * 
   * @remark DONE
  */
  bool contains(const_key_reference key);


/* ========================================================================= */
/*                                Iterators                                  */
/* ========================================================================= */

protected:

  class Iterator {
  protected:
    const BaseTree<key_type, value_type>& tree_;
    Node *current_;

    /**
     * @brief Поиск крайнего левого узла дерева (поиск узла с наименьшим ключом)
    */
    Node* findMin(Node *node) const {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->left == nullptr) {
            return node;
        }

        return findMin(node->left);
    }

    /**
     * @brief Поиск крайнего правого узла дерева (поиск узла с наибольшим ключом)
    */
    Node* findMax(Node *node) const {
        if (node == nullptr) {
            return nullptr;
        }

        while (node->right != nullptr) {
            node = node->right;
        }

        return node;
    }

    /**
     * @brief Поиск узла, узел с заданным ключом для которого является его правым потомком
    */
    Node* findRParent(Node *node, const Key& key) const {
        if (node == nullptr || tree_.root_->key == key) {
            return nullptr;
        }

        if (key > node->key) { // искомый предок должен быть в правом поддереве текущего узла
            Node *r_parent = findRParent(node->right, key);
            if (r_parent != nullptr) { // мы нашли искомого предка в правом поддереве
                return r_parent;
            } else { // в правом поддереве нет искомого предка
                return node;
            }
        } else { // искомый предок должен быть в левом поддереве текущего узла
            return findRParent(node->left, key);
        }
    }

    /**
     * @brief Поиск узла, узел с заданным ключом для которого является его левым потомком
    */
    Node *findLParent(Node *node, const Key& key) const {
        if (node == nullptr || tree_.root_->key == key) {
            return nullptr;
        }

        if (key < node->key) { // искомый предок должен быть в левом поддереве текущего узла
            Node *l_parent = findLParent(node->left, key);
            if (l_parent != nullptr) { // мы нашли искомого предка в левом поддереве
                return l_parent;
            } else { // в левом поддереве нет искомого предка
                return node;
            }
        } else { // искомый предок должен быть в правом поддереве текущего узла
            return findLParent(node->right, key);
        }
    }

    /**
     * @brief Поиск предыдущего узла дерева (поиск узла с наибольшим ключом меньше текущего)
    */
    Node* findPredecessor(Node *node) const {
        if (node->left != nullptr) {
            return findMax(node->left); // максимальный ключ в левом поддереве
        } else {
            return findRParent(tree_.root_, node->key); // узел для которого текущий узел является правым потомком
        }
    }

    /**
     * @brief Поиск следующего узла дерева (поиск узла с наименьшим ключом больше текущего)
    */
    Node* findSuccessor(Node *node) const {
        if (node->right != nullptr) {
            return findMin(node->right); // минимальный ключ в правом поддереве
        } else {
            return findLParent(tree_.root_, node->key); // узел для которого текущий узел является левым потомком
        }
    }

  public:
    /**
     * @brief Iterator constructor. Sets the current position to the beginning of the tree
    */
    Iterator(const BaseTree<Key, Value>& tree) : tree_(tree), current_(findMin(tree.root_)) {}

    /**
     * @brief Iterator constructor. Sets the current position to the given node
    */
    Iterator(const BaseTree<Key, Value>& tree, Node* node) : tree_(tree), current_(node) {}

    /**
     * @brief Copy constructor
     * 
     * @note Necessary for passing iterators to funcitons and returning them as the result
    */
    Iterator(const Iterator& other) : tree_(other.tree_), current_(other.current_) {}

    Node* getNode() const { 
      return this->current_; 
    }

    /**
     * @brief Dereferencing operator. Returns a reference to the value pointed by the iterator
     * 
     * @throws ArrayException if current position is not set (at the end)
    */
    Node* operator*() const {
      if (current_ == nullptr) {
          throw ArrayException("Cannot dereference an unset iterator");
      }

      return current_;
    }

    /**
     * @brief Increment operator. Moves the iterator to the next element (postfix version)
     * 
     * @throws ArrayException if current position is not set (at the end)
    */
    Iterator& operator++() {
      if (current_ == nullptr) {
          throw ArrayException("Cannot increment an unset iterator");
      }

      current_ = findSuccessor(current_);

      return *this;
    }

    /**
     * @brief Decrement operator. Moves the iterator to the previous element (postfix version)
     * 
     * @throws ArrayException if current position is not set (at the end) list is circular
    */
    Iterator& operator--() {
      if (current_ == nullptr) {
          throw ArrayException("Cannot decrement an unset iterator");
      }

      current_ = findPredecessor(current_);

      return *this;
    }

    /**
     * @brief Operator for comapring two iterators on equality. Returns true
     * if both iterators point to the same element, false otherwise
    */
    bool operator==(const Iterator& other) const {
        return current_ == other.current_;
    }

    /**
     * @brief Operator for comapring two iterators on unequality. Returns true
     * if iterators point to different elements, false otherwise
    */
    bool operator!=(const Iterator& other) const {
        return current_ != other.current_;
    }

    /**
     * @brief Assignment operator. Performs a shallow copy of the given iterator
    */
    Iterator& operator=(const Iterator& other) {
      current_ = other.current_;

      return *this;
    }
  };

  // not really used anywhere, but whatever
  class ConstIterator : public Iterator {
  public:
    /**
     * @brief Iterator constructor. Sets the current position to the beginning of the tree
    */
    ConstIterator(const BaseTree<Key, Value>& tree) : Iterator(tree) {}

    /**
     * @brief Iterator constructor. Sets the current position to the given node
    */
    ConstIterator(const BaseTree<Key, Value>& tree, Node *node) : Iterator(tree, node) {}

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
/*                          Helper Private Methods                           */
/* ========================================================================= */

private:

  /**
   * @brief Takes resources from the other list and trasnfers it to the current list
   * 
   * @note No checks performed. Used by move constructor and move assignment.
   * No memory is freed. This should be taken care of outside of this method
  */
  void stealResources(BaseTree &&other);

  /**
   * @brief Removes the given node from the tree
   * 
   * @note Rewrites pointers, decrements size and clears memory, no checks performed
  */
  bool removeNode(Node *current, Node *parent);

  /**
   * @brief Finds and returns note in the tree with a given key
  */
  Node* findNode(const_key_reference key) const;

  /**
   * @brief Recursively outputs tree structure to the console
  */
  void show(Node* current, int level) const;

  /**
   * @brief Deletes a node if it does not have duplicates, otherwise
   * decrements the count field
  */
  void deleteNode(Node *node) {
    if (!(--(node->count))) {
      --size_;
      delete node;
    }
  }


/* ========================================================================= */
/*                           Helper Public Methods                           */
/* ========================================================================= */

public:
  
  /**
   * @brief Outputs a tree structure to the terminal in a human readable format
   * Ignores values and prints only the keys
  */
  void print() const;

};


/* ========================================================================= */
/*                       Constructors Implementation                         */
/* ========================================================================= */

template <typename Key, typename Value>
BaseTree<Key, Value>::BaseTree(std::initializer_list<std::pair<key_type, value_type> > const &items) {
  for (auto item: items) {
    insert(item.first, item.second);
  }
}

template <typename Key, typename Value>
BaseTree<Key, Value>::BaseTree(const BaseTree<Key, Value>& other) {
  if (other.root_ == nullptr) {
      return;
  }

  // стек с парами (узел, родитель)
  Stack<std::pair<Node*, Node*>> nodes_stack;
  nodes_stack.push(std::make_pair(other.root_, nullptr));

  while (!nodes_stack.empty()) {
    Node* current = nodes_stack.top().first;
    Node* parent = nodes_stack.top().second;
    nodes_stack.pop();

    Node *new_node = new Node(current->key, current->value, current->count);
    new_node->left = current->left;
    new_node->right = current->right;

    if (parent == nullptr) { // мы на корне второго дерева
        root_ = new_node;
    } else if (current == parent->left) { // мы в левом поддереве
        parent->left = new_node;
    } else { // мы в правом поддереве
        parent->right = new_node;
    }

    if (current->left != nullptr) {
        nodes_stack.push(std::make_pair(current->left, new_node));
    }

    if (current->right != nullptr) {
        nodes_stack.push(std::make_pair(current->right, new_node));
    }
  }

  this->size_ = other.size_;
}

template <typename Key, typename Value>
BaseTree<Key, Value>::BaseTree(BaseTree<Key, Value>&& other) {
  if (this == &other) {
    return;
  }

  stealResources(std::move(other));
}

template <typename Key, typename Value>
BaseTree<Key, Value>& BaseTree<Key, Value>::operator=(BaseTree<Key, Value> &&other) {
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

template <typename Key, typename Value>
void BaseTree<Key, Value>::clear() {
  if (root_ == nullptr) {
    return;
  }

  Stack<Node*> node_stack;
  node_stack.push(root_);

  while (!node_stack.empty()) {
      Node* current = node_stack.top();
      node_stack.pop();

      if (current->left != nullptr) {
          node_stack.push(current->left);
      }
      if (current->right != nullptr) {
          node_stack.push(current->right);
      }

      delete current;
  }

  size_ = 0;
  root_ = nullptr;
}

template <typename Key, typename Value>
std::pair<typename BaseTree<Key, Value>::Node*, bool> 
  BaseTree<Key, Value>::insert(const key_type& key, const value_type& value) {
      
  if (root_ == nullptr) { // дерево пустое
    root_ = new Node(key, value, 1);
    ++size_;
    return std::make_pair(root_, true);
  }

  Node* current = root_;
  Node* parent = nullptr;
  while (current != nullptr) { // ищем место вставки
    parent = current;
    if (key == current->key) { // code to implement multiple insertions
      current->count += 1;
      ++size_;
      return std::make_pair(current, true);
    } else 
    if (key < current->key) {
      current = current->left;
    } else {
      current = current->right;
    }
  }

  // if we are here this is the first node with the specified value
  Node* new_node = new Node(key, value, 1);

  if (key < parent->key) { // создаем необходимые связи в дереве с новым узлом
    parent->left = new_node;
  } else {
    parent->right = new_node;
  }

  ++size_;

  return std::make_pair(new_node, true);
}

// template <typename Key, typename Value>
// bool BaseTree<Key, Value>::erase(Iterator pos) {
//   if (pos == end()) {
//     return false;
//   }

//   if (pos == begin()) {
//     return removeNode(pos.getNode(), nullptr);
//   } else {
//     // because we cannot guarantee in which order arguments will be
//     // passed we have to determine the parent position beforehand
//     iterator parent = --pos;
//     ++pos;
//     return removeNode(pos.getNode(), parent.getNode());
//   }
// }

template <typename Key, typename Value>
bool BaseTree<Key, Value>::remove(const_key_reference key) {
  Node *current = root_;
  Node *parent = nullptr;

  // Поиск удаляемого узла
  while (current != nullptr && current->key != key) {
      parent = current;

      if (key < current->key) {
          current = current->left;
      } else {
          current = current->right;
      }
  }

  return removeNode(current, parent);
}

template <typename Key, typename Value>
typename BaseTree<Key, Value>::Node* BaseTree<Key, Value>::find(const_key_reference key) const {
  Node* node = findNode(key);

  if (node == nullptr) {
    throw ArrayException("Element with specified key was not found");
  }
  
  return node;
}

template <typename Key, typename Value>
bool BaseTree<Key, Value>::contains(const_key_reference key) {
  return findNode(key) != nullptr;
}

template <typename Key, typename Value>
void BaseTree<Key, Value>::swap(BaseTree& other) {
  if (this == &other) {
    return;
  }

  BaseTree<Key, Value> temp{ std::move(*this) };

  *this = std::move(other);

  other = std::move(temp);
}

template <typename Key, typename Value>
void BaseTree<Key, Value>::merge(BaseTree& other) {
  Iterator it = other.begin();

  while (it != other.end()) {
    Node* node = it.getNode();
    insert(node->key, node->value);
    ++it;
  }
}

/* ========================================================================= */
/*                    Private Helper Methods Implementation                  */
/* ========================================================================= */

template <typename Key, typename Value>
void BaseTree<Key, Value>::stealResources(BaseTree<Key, Value> &&other) {
  // steal resources from the other tree

  root_ = other.root_;

  this->size_ = other.size();

  other.root_ = nullptr;

  other.size_ = 0;
}

template <typename Key, typename Value>
bool BaseTree<Key, Value>::removeNode(Node *current, Node *parent) {
  if (current == nullptr) { // элемента с заданным ключом не существует
      return false;
  }

  // У удаляемого узла нет детей (это лист дерева)
  if (current->left == nullptr && current->right == nullptr) {
      if (current == root_) {
          root_ = nullptr;
      } else if (current == parent->left) {
          parent->left = nullptr;
      } else {
          parent->right = nullptr;
      }

      deleteNode(current);
  }

  // У удаляемого узла есть один дочерний узел
  else if (current->left == nullptr) { // левый дочерний узел
      if (current == root_) {
          root_ = current->right;
      } else if (current == parent->left) {
          parent->left = current->right;
      } else {
          parent->right = current->right;
      }

      deleteNode(current);
  }

  else if (current->right == nullptr) { // правый дочерний узел
      if (current == root_) {
          root_ = current->left;
      } else if (current == parent->left) {
          parent->left = current->left;
      } else {
          parent->right = current->left;
      }

      deleteNode(current);
  }

  // У удаляемого узла два дочерних узла
  else {
      Node *successor = current->right;
      Node *successor_parent = current;

      // Ищем приемника узла (это узел с минимальным ключом в правом поддереве)
      while (successor->left != nullptr) {
          successor_parent = successor;
          successor = successor->left;
      }

      // Копируем приемника в удаляемый узел
      current->key = successor->key;
      current->value = successor->value;

      // Удаляем приемника
      if (successor == successor_parent->left) {
          // Если у приемника был правый ребенок, то его нужно
          // сохранить как левого ребенка родителя приемника
          successor_parent->left = successor->right;
      } else {
          // Если у приемника был правый ребенок, то его нужно
          // сохранить как правого ребенка родителя приемника
          successor_parent->right = successor->right;
      }

      deleteNode(successor);
  }

  return true;
}

template <typename Key, typename Value>
typename BaseTree<Key, Value>::Node* BaseTree<Key, Value>::findNode(const_key_reference key) const {
    if (root_ == nullptr) {
      return nullptr;
    }

    Node* current = root_;

    while (current != nullptr) { // Поиск узла с заданным ключом
        if (current->key == key) {
            return current;
        } else if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
            current = current->right;
        }
    }

    return nullptr;
}

template <typename Key, typename Value>
void BaseTree<Key, Value>::show(Node* current, int level) const {
  if (current == nullptr) {
      return;
  }

  show(current->right, level + 1);

  for (int i = 0; i < level; ++i) {
      std::cout << "  ";
  }

  std::cout << current->key << ":" << current->value << std::endl;

  show(current->left, level + 1);
}


/* ========================================================================= */
/*                    Public Helper Methods Implementation                   */
/* ========================================================================= */

template <typename Key, typename Value>
void BaseTree<Key, Value>::print() const {
  if (root_ == nullptr) {
    std::cout << "Tree is empty" << std::endl;
  }

  show(root_, 0);
}

}

#endif // S21_BASE_TREE_H_