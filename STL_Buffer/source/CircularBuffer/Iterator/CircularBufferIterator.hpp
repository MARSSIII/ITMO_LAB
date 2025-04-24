#pragma once

#include <iterator>
#include <type_traits>

template <typename T, bool IsConst> class CircularBufferIterator {
public:
  using value_type = T;
  using pointer = std::conditional_t<IsConst, const T *, T *>;
  using reference = std::conditional_t<IsConst, const T &, T &>;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::random_access_iterator_tag;

  CircularBufferIterator(const CircularBufferIterator &other);
  CircularBufferIterator &operator=(const CircularBufferIterator &other);
  CircularBufferIterator(CircularBufferIterator &&other) = default;
  CircularBufferIterator &operator=(CircularBufferIterator &&other) = default;

  operator CircularBufferIterator<T, true>() const;

  reference operator*() const;
  pointer operator->() const;

  bool operator<(const CircularBufferIterator &other) const;
  bool operator>(const CircularBufferIterator &other) const;
  bool operator>=(const CircularBufferIterator &other) const;
  bool operator<=(const CircularBufferIterator &other) const;
  bool operator==(const CircularBufferIterator &other) const;
  bool operator!=(const CircularBufferIterator &other) const;

  CircularBufferIterator &operator+(size_t value);
  CircularBufferIterator &operator-(size_t value);
  CircularBufferIterator &operator+=(int value);
  CircularBufferIterator &operator-=(int value);
  CircularBufferIterator &operator++();
  CircularBufferIterator operator++(int);
  CircularBufferIterator &operator--();
  CircularBufferIterator operator--(int);

  explicit CircularBufferIterator(pointer ptr);
  pointer m_ptr;
};

#include "CircularBufferIterator.tpp"
