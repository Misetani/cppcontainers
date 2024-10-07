#ifndef S21_ARRAY_H_
#define S21_ARRAY_H_

#include "s21_container.h"
#include "../array_exception.h"

namespace s21 {
template <class T, size_t N>
class Array : public Container {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;
  using array_type = Array<T, N>;

  Array();
  Array(std::initializer_list<T> const &items);
  Array(const array_type &a);
  Array(array_type &&a) noexcept;
  ~Array() {}

  array_type &operator=(const Array &other);
  array_type &operator=(Array &&a) noexcept;

  constexpr reference operator[](size_type pos);
  constexpr const_reference operator[](size_type pos) const;

  constexpr reference at(size_type pos);
  constexpr const_reference at(size_type pos) const;
  constexpr reference front();
  constexpr const_reference front() const;
  constexpr reference back();
  constexpr const_reference back() const;

  constexpr iterator data() noexcept;
  constexpr const_iterator data() const noexcept;

  constexpr iterator begin() noexcept;
  constexpr const_iterator begin() const noexcept;
  constexpr const_iterator cbegin() const noexcept;

  constexpr iterator end() noexcept;
  constexpr const_iterator end() const noexcept;
  constexpr const_iterator cend() const noexcept;

  void swap(Array &other) noexcept;
  void fill(const_reference value);

 private:
  value_type data_[N];
};

template <class T, size_t N>
s21::Array<T, N>::Array() {
  size_ = N;
  // constexpr T object{};
  // for (size_type i = 0; i < size_; ++i) {
  //   data_[i] = object;
  // }
}

template <typename T, size_t N>
s21::Array<T, N>::Array(std::initializer_list<T> const &items) : Array() {
  size_t i = 0;
  for (auto it = items.begin(); it != items.end() && i < N; ++it, ++i) {
    data_[i] = *it;
  }
}

template <class T, size_t N>
s21::Array<T, N>::Array(const array_type &a) : Array() {
  for (size_type i = 0; i < size_; ++i) {
    data_[i] = a.data_[i];
  }
}

template <class T, size_t N>
s21::Array<T, N>::Array(array_type &&a) noexcept : Array() {
  if (this == &a) {
    return;
  }
  
  for (size_type i = 0; i < size_; ++i) {
    data_[i] = a.data_[i];
    a.data_[i] = 0;
  }
}

template <class T, size_t N>
s21::Array<T, N> &s21::Array<T, N>::operator=(const Array &a) {
  if (this != &a) {
    for (size_type i = 0; i < a.size_; ++i) {
      data_[i] = a.data_[i];
    }
  }
  return *this;
}

template <class T, size_t N>
s21::Array<T, N> &s21::Array<T, N>::operator=(Array &&a) noexcept {
  if (this != &a) {
    for (size_type i = 0; i < a.size_; ++i) {
      data_[i] = a.data_[i];
      a.data_[i] = 0;
    }
  }
  return *this;
}

template <class T, size_t N>
constexpr typename s21::Array<T, N>::reference s21::Array<T, N>::operator[](
    size_type pos) {
  return data_[pos];
}

template <class T, size_t N>
constexpr typename s21::Array<T, N>::const_reference
s21::Array<T, N>::operator[](size_type pos) const {
  return data_[pos];
}

template <class T, size_t N>
constexpr typename s21::Array<T, N>::reference s21::Array<T, N>::at(
    size_type pos) {
  if (pos >= size_) throw ArrayException("Index is out of range");
  return data_[pos];
}

template <class T, size_t N>
constexpr typename s21::Array<T, N>::const_reference s21::Array<T, N>::at(
    size_type pos) const {
  if (pos >= size_) throw ArrayException("Index is out of range");
  return data_[pos];
}

template <class T, size_t N>
constexpr typename s21::Array<T, N>::reference s21::Array<T, N>::front() {
  return data_[0];
}

template <class T, size_t N>
constexpr typename s21::Array<T, N>::const_reference s21::Array<T, N>::front()
    const {
  return data_[0];
}

template <class T, size_t N>
constexpr typename s21::Array<T, N>::reference s21::Array<T, N>::back() {
  return data_[size_ - 1];
}

template <class T, size_t N>
constexpr typename s21::Array<T, N>::const_reference s21::Array<T, N>::back()
    const {
  return data_[size_ - 1];
}

template <class T, size_t N>
constexpr typename s21::Array<T, N>::iterator
s21::Array<T, N>::data() noexcept {
  return data_;
}

template <class T, size_t N>
constexpr typename s21::Array<T, N>::const_iterator s21::Array<T, N>::data()
    const noexcept {
  if (size_ == 0) return nullptr;
  return data_;
}

template <class T, size_t N>
constexpr typename s21::Array<T, N>::iterator
s21::Array<T, N>::begin() noexcept {
  return &data_[0];
}

template <class T, size_t N>
constexpr typename s21::Array<T, N>::const_iterator s21::Array<T, N>::begin()
    const noexcept {
  return &data_[0];
}

template <class T, size_t N>
constexpr typename s21::Array<T, N>::const_iterator s21::Array<T, N>::cbegin()
    const noexcept {
  return &data_[0];
}

template <class T, size_t N>
constexpr typename s21::Array<T, N>::iterator s21::Array<T, N>::end() noexcept {
  return &data_[size_];
}

template <class T, size_t N>
constexpr typename s21::Array<T, N>::const_iterator s21::Array<T, N>::end()
    const noexcept {
  return &data_[size_];
}

template <class T, size_t N>
constexpr typename s21::Array<T, N>::const_iterator s21::Array<T, N>::cend()
    const noexcept {
  return &data_[size_];
}

template <class T, size_t N>
void s21::Array<T, N>::swap(Array &other) noexcept {
  if (this != &other) {
    for (size_t i = 0; i < size_; ++i) {
      std::swap(data_[i], other.data_[i]);
    }
  }
}

template <class T, size_t N>
void s21::Array<T, N>::fill(const T &value) {
  for (size_t i = 0; i < size_; ++i) {
    data_[i] = value;
  }
}

}  // namespace s21

#endif