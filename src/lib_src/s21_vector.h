#ifndef S21_VECTOR_H_
#define S21_VECTOR_H_

#include <cstddef>
#include <iostream>

#include "../array_exception.h"
#include "s21_container.h"

namespace s21 {

template <typename T>
class Vector : public Container {
 private:
  template <bool IsConst>
  class BaseVectorIterator;

 private:
  size_t capacity_;
  T *arr_;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using pointer = T *;

  using iterator = BaseVectorIterator<false>;
  using const_iterator = BaseVectorIterator<true>;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  Vector() : capacity_(0U), arr_(nullptr){};

  Vector(size_type n);
  Vector(std::initializer_list<value_type> const &items);
  Vector(const Vector &v);
  Vector(Vector &&v);

  ~Vector() { deleteVector(); };

  Vector<value_type> &operator=(Vector &&v);

  reference at(size_type pos) {
    if (pos > size_) {
      throw ArrayException("Index is not within the range of the container");
    }

    return arr_[pos];
  };

  const_reference at(size_type pos) const {
    if (pos > size_) {
      throw ArrayException("Index is not within the range of the container");
    }

    return arr_[pos];
  };

  reference operator[](size_type pos) { return arr_[pos]; };

  const_reference operator[](size_type pos) const { return arr_[pos]; };

  const_reference front() const {
    if (this->size() == 0) {
      throw ArrayException("Vector is empty");
    }

    return arr_[0];
  };

  const_reference back() const {
    if (this->size() == 0) {
      throw ArrayException("Vector is empty");
    }

    return arr_[size_ - 1];
  };

  pointer data() { return arr_; }

  iterator begin() { return iterator{arr_}; }
  iterator end() { return iterator{arr_ + size_}; }

  const_iterator begin() const { return const_iterator{arr_}; }
  const_iterator end() const { return const_iterator{arr_ + size_}; }

  const_iterator cbegin() const { return const_iterator(arr_); }
  const_iterator cend() const { return const_iterator(arr_ + size_); }

  reverse_iterator rbegin() { return reverse_iterator{arr_}; }
  reverse_iterator rend() { return reverse_iterator{arr_ + size_}; }

  void reserve(size_type size);

  size_type capacity() const { return capacity_; };

  void shrink_to_fit();

  void clear() {
    for (size_type i = 0; i < size_; ++i) {
      arr_[i].~value_type();
    }

    size_ = 0;
  };

  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(Vector &other);

  template <typename... Args>
  iterator insert_many(iterator pos, Args &&...args);

  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  template <bool IsConst>
  class BaseVectorIterator {
   public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;

    using pointer = std::conditional_t<IsConst, const T *, T *>;
    using reference = std::conditional_t<IsConst, const T &, T &>;
    using value_type = T;

   private:
    pointer ptr_;

   public:
    BaseVectorIterator(pointer ptr) { ptr_ = ptr; }
    BaseVectorIterator(const iterator &other) { ptr_ = other.ptr_; };

    BaseVectorIterator &operator=(const BaseVectorIterator &other) {
      ptr_ = other.ptr_;

      return *this;
    };

    reference operator*() const { return *ptr_; }

    pointer operator->() const { return ptr_; }

    BaseVectorIterator &operator++() {
      ++ptr_;

      return *this;
    };

    BaseVectorIterator operator++(int) {
      BaseVectorIterator copy = *this;
      ++ptr_;
      return copy;
    }

    BaseVectorIterator &operator--() {
      --ptr_;

      return *this;
    };

    BaseVectorIterator operator--(int) {
      BaseVectorIterator copy = *this;
      --ptr_;
      return copy;
    }

    bool operator==(const BaseVectorIterator &other) const {
      return ptr_ == other.ptr_;
    }

    bool operator!=(const BaseVectorIterator &other) const {
      return ptr_ != other.ptr_;
    }
  };

 private:
  void deleteVector() {
    delete[] arr_;

    size_ = 0;
    capacity_ = 0;
    arr_ = nullptr;
  }

  void stealResources(Vector<value_type> &&other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    arr_ = other.arr_;

    other.size_ = 0;
    other.capacity_ = 0;
    other.arr_ = nullptr;
  }

  size_t distance(iterator pos) {
    iterator iter = end();
    int flag = 1;

    size_t i = 0;

    for (; i <= size_ && flag; i++) {
      if (iter == pos) {
        flag = 0;
        break;
      }

      --iter;
    }

    if (flag) {
      throw ArrayException("Incorrect position");
    }

    return i;
  }
};

template <typename value_type>
Vector<value_type>::Vector(size_type n) {
  if (n > max_size()) {
    throw ArrayException("Size larger max_size");
  }

  size_ = n;
  capacity_ = n;
  arr_ = new value_type[n];
}

template <typename value_type>
Vector<value_type>::Vector(std::initializer_list<value_type> const &items) {
  size_ = items.size();
  capacity_ = items.size();

  arr_ = new value_type[items.size()];

  size_t count = 0;
  for (auto item : items) {
    arr_[count] = item;
    ++count;
  }
}

template <typename value_type>
Vector<value_type>::Vector(const Vector &v) {
  size_ = v.size_;
  capacity_ = v.capacity_;

  arr_ = new value_type[capacity_];

  for (size_type i = 0; i < size_; ++i) {
    arr_[i] = v.arr_[i];
  }
}

template <typename value_type>
Vector<value_type>::Vector(Vector &&v) {
  if (this == &v) {
    return;
  }

  stealResources(std::move(v));
}

template <typename value_type>
typename s21::Vector<value_type> &Vector<value_type>::operator=(Vector &&v) {
  if (this == &v) {
    return *this;
  }

  deleteVector();

  stealResources(std::move(v));

  return *this;
}

template <typename value_type>
void Vector<value_type>::reserve(size_type size) {
  if (size <= capacity_) {
    return;
  }

  value_type *newarr = new value_type[size];

  for (size_t i = 0; i < size_; ++i) {
    newarr[i] = arr_[i];
  }

  delete[] arr_;

  arr_ = newarr;
  capacity_ = size;
}

template <typename value_type>
void Vector<value_type>::shrink_to_fit() {
  if (size_ < capacity_) {
    value_type *newarr = new value_type[size_];

    for (size_t i = 0; i < size_; ++i) {
      newarr[i] = arr_[i];
    }

    delete[] arr_;

    arr_ = newarr;
    capacity_ = size_;
  }
}

template <typename value_type>
typename s21::Vector<value_type>::iterator Vector<value_type>::insert(
    iterator pos, const_reference value) {
  size_t dist = distance(pos);

  if (size_ == capacity_) {
    if (capacity_ != 0)
      reserve(2 * size_);
    else
      reserve(1);
  }

  for (size_t i = 0; i < dist; ++i) {
    arr_[size_ - i] = arr_[size_ - i - 1];
    pos++;
  }

  arr_[size_ - dist] = value;
  ++size_;

  return pos;
}

template <typename value_type>
void Vector<value_type>::erase(iterator pos) {
  size_t dist = distance(pos);

  for (size_t i = 0; i < dist; ++i) {
    arr_[size_ - dist + i] = arr_[size_ - dist + i + 1];
  }

  arr_[size_ - 1].~value_type();
  --size_;
}

template <typename value_type>
void Vector<value_type>::push_back(const_reference value) {
  if (capacity_ == size_) {
    if (capacity_ != 0)
      reserve(2 * size_);
    else
      reserve(1);
  }

  arr_[size_] = value;
  ++size_;
}

template <typename value_type>
void Vector<value_type>::pop_back() {
  if (size_ > 0) {
    arr_[size_ - 1].~value_type();
    --size_;
  }
}

template <typename value_type>
void Vector<value_type>::swap(Vector &other) {
  if (this == &other) {
    return;
  }

  Vector<value_type> temp(std::move(*this));

  *this = std::move(other);
  other = std::move(temp);
}

template <typename value_type>
template <typename... Args>
void Vector<value_type>::insert_many_back(Args &&...args) {
  for (auto arg : {args...}) {
    push_back(arg);
  }
}

template <typename value_type>
template <typename... Args>
typename s21::Vector<value_type>::iterator Vector<value_type>::insert_many(
    iterator pos, Args &&...args) {

  size_t dist = distance(pos);

  Vector<value_type> tmp;

  for (auto arg : {args...}) {
    tmp.push_back(arg);
  }

  size_t countNewElem = tmp.size();
  size_t oldSize = size_;

  iterator iter = end();

  if (size_ + countNewElem > capacity_) {
    reserve(size_ + countNewElem + 1);
  }

  size_ += countNewElem;

  for (size_t i = 0; i < dist; ++i) {
    arr_[oldSize + countNewElem - i - 1] = arr_[oldSize - i - 1];

    --iter;
  }

  for (size_t i = 0; i < countNewElem; ++i) {
    arr_[oldSize - dist + i] = tmp[i];
    --iter;
  }

  return iter;
}

}  // namespace s21

#endif  // S21_VECTOR_H_