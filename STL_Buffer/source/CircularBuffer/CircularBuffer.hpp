#pragma once

#include <initializer_list>
#include <memory>

#include "Iterator/CircularBufferIterator.hpp"

template <typename T, typename Alloc = std::allocator<T>> class CircularBuffer {
private:
  size_t m_Size;
  size_t m_Capacity;

  [[no_unique_address]] Alloc m_Alloc;
  using m_AllocTraits = std::allocator_traits<Alloc>;

  T *m_Arr;

  size_t m_start;
  size_t m_end;

  void m_RemoveBuffer();

  template <bool IsConst>
  void swap(CircularBufferIterator<T, IsConst> &first,
            CircularBufferIterator<T, IsConst> &second);

public:
  // Constructor class

  // default construct
  CircularBuffer();

  // size construct
  CircularBuffer(size_t Capacity);

  // init. list construct
  CircularBuffer(std::initializer_list<T> list);

  // destructor class
  ~CircularBuffer();

  // copy construct
  CircularBuffer(const CircularBuffer &other);

  CircularBuffer &operator=(const CircularBuffer &other);

  // move construct
  CircularBuffer(CircularBuffer &&other) noexcept;

  CircularBuffer &operator=(CircularBuffer &&other);

  // iterators
  using Iterator = CircularBufferIterator<T, false>;
  using ConstIterator = CircularBufferIterator<T, true>;

  // overloading operators
  T &operator[](size_t index);
  bool operator==(const CircularBuffer &other);
  bool operator!=(const CircularBuffer &other);

  // container methods
  size_t Size() const;
  size_t Capacity() const;
  [[nodiscard]] bool Empty() const;
  void ShowBuffer() const;

  void reserve(size_t NewCap);

  void Push(T &value, Iterator iter);
  void Push(const T &value, ConstIterator iter);

  void Delete(Iterator iter);
  void Delete(ConstIterator iter);

  void PushBack(T &value);
  void PushBack(const T &value);

  void PopBack();

  void PushFront(T &value);
  void PushFront(const T &value);

  void PopFront();

  // Iterator method
  Iterator begin();
  Iterator end();
  ConstIterator begin() const;
  ConstIterator end() const;
  ConstIterator Cbegin() const;
  ConstIterator Cend() const;
};

#include "CircularBuffer.tpp"
