#pragma once

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <type_traits>
#include <utility>

template <typename T, typename Alloc = std::allocator<T>>
class CircularBuffer {
  private:
  size_t m_Size;
  size_t m_Capacity;

  Alloc m_Alloc;
  using m_AllocTraits = std::allocator_traits<Alloc>;

  T *m_Arr;

  size_t m_start;
  size_t m_end;

  template <bool IsConst>
  class BaseIterator;

  void m_RemoveBuffer();

  template <bool IsConst>
  void swap(BaseIterator<IsConst> &first, BaseIterator<IsConst> &second);

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
  using Iterator = BaseIterator<false>;
  using ConstIterator = BaseIterator<true>;

  // overloading operators
  T &operator[](size_t index);
  bool operator==(const CircularBuffer &other);
  bool operator!=(const CircularBuffer &other);

  // container methods
  size_t Size() const;
  size_t Capacity() const;
  bool Empty() const;
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

// Construct class

// default construct
template <typename T, typename Alloc>
CircularBuffer<T, Alloc>::CircularBuffer()
    : m_Size(0), m_Capacity(0), m_start(0), m_end(0), m_Arr(nullptr) {}

// size construct
template <typename T, typename Alloc>
CircularBuffer<T, Alloc>::CircularBuffer(size_t Capacity)
    : m_Arr(m_Alloc.allocate(Capacity)),
      m_Size(0),
      m_Capacity(Capacity),
      m_start(0),
      m_end(1) {}

// init. list constuct
template <typename T, typename Alloc>
CircularBuffer<T, Alloc>::CircularBuffer(std::initializer_list<T> list)
    : m_Arr(m_Alloc.allocate(list.size())),
      m_Size(list.size()),
      m_Capacity(list.size()),
      m_start(0),
      m_end(list.size()) {
  if (list.size() == 0) {
    return;
  }

  size_t index = 0;
  try {
    for (; index < list.size(); ++index) {
      m_Alloc.construct(m_Arr + index, list[index]);
    }
  } catch (...) {
    for (size_t oldIndex = 0; oldIndex < index; ++oldIndex) {
      m_Alloc.destroy(m_Arr + oldIndex);
    }

    m_Alloc.deallocate(m_Arr, m_Capacity);
  }
}

// destructor

template <typename T, typename Alloc>
CircularBuffer<T, Alloc>::~CircularBuffer() {
  this->m_RemoveBuffer();
}

// copy construct
template <typename T, typename Alloc>
CircularBuffer<T, Alloc>::CircularBuffer(const CircularBuffer &other) {
  if (this == other) {
    return;
  }

  Alloc newAlloc = m_AllocTraits::propagate_on_container_copy_assignment::value
                       ? other.m_Alloc
                       : m_Alloc;

  T *newArr = m_AllocTraits::allocate(newAlloc, m_Arr, other.m_Capacity);

  size_t index = 0;

  try {
    for (; index < other.m_Size; ++index) {
      m_AllocTraits::construct(newAlloc, newArr + index, other.m_Arr[index]);
    }
  } catch (...) {
    for (size_t oldIndex = 0; oldIndex < index; ++oldIndex) {
      m_AllocTraits::destroy(newAlloc, newArr + oldIndex);
    }

    m_AllocTraits::deallocate(newAlloc, newArr, other.m_Capacity);
    throw;
  }

  this->m_RemoveBuffer();

  m_Arr = newArr;
  m_Alloc = newAlloc;
  m_Size = other.m_Size;
  m_Capacity = other.m_Capacity;
}

template <typename T, typename Alloc>
CircularBuffer<T, Alloc> &CircularBuffer<T, Alloc>::operator=(
    const CircularBuffer<T, Alloc> &other) {
  if (this == other) {
    return *this;
  }

  Alloc newAlloc = m_AllocTraits::propagate_on_container_copy_assignment::value
                       ? other.m_Alloc
                       : m_Alloc;

  T *newArr = m_AllocTraits::allocate(newAlloc, m_Arr, other.m_Capacity);

  size_t index = 0;

  try {
    for (; index < other.m_Size; ++index) {
      m_AllocTraits::construct(newAlloc, newArr + index, other.m_Arr[index]);
    }
  } catch (...) {
    for (size_t oldIndex = 0; oldIndex < index; ++oldIndex) {
      m_AllocTraits::destroy(newAlloc, newArr + oldIndex);
    }

    m_AllocTraits::deallocate(newAlloc, newArr, other.m_Capacity);
    throw;
  }

  this->m_RemoveBuffer();

  m_Arr = newArr;
  m_Alloc = newAlloc;
  m_Size = other.m_Size;
  m_Capacity = other.m_Capacity;
}

// move construct

template <typename T, typename Alloc>
CircularBuffer<T, Alloc>::CircularBuffer(
    CircularBuffer<T, Alloc> &&other) noexcept {
  if (other == this) {
    return;
  }

  std::swap(m_Size, other.m_Size);
  std::swap(m_Capacity, other.m_Capacity);
  std::swap(m_Alloc, other.m_Alloc);
  std::swap(m_start, other.m_start);
  std::swap(m_end, other.m_end);
  std::swap(m_Arr, other.m_Arr);
}

template <typename T, typename Alloc>
CircularBuffer<T, Alloc> &CircularBuffer<T, Alloc>::operator=(
    CircularBuffer<T, Alloc> &&other) {
  if (this == other) {
    return *this;
  }

  std::swap(m_Size, other.m_Size);
  std::swap(m_Capacity, other.m_Capacity);
  std::swap(m_Alloc, other.m_Alloc);
  std::swap(m_start, other.m_start);
  std::swap(m_end, other.m_end);
  std::swap(m_Arr, other.m_Arr);

  return *this;
}

template <typename T, typename Alloc>
void CircularBuffer<T, Alloc>::m_RemoveBuffer() {
  for (size_t index = 0; index < m_Size; ++index) {
    m_AllocTraits::destroy(m_Alloc, m_Arr + index);
  }

  m_AllocTraits::deallocate(m_Alloc, m_Arr, m_Capacity);
}

template <typename T, typename Alloc>
template <bool IsConst>
void CircularBuffer<T, Alloc>::swap(BaseIterator<IsConst> &first,
                                    BaseIterator<IsConst> &second) {
  using std::swap;
  swap(*first, *second);
}

// iterator class
template <typename T, typename Alloc>
template <bool IsConst>
class CircularBuffer<T, Alloc>::BaseIterator {
  public:
  friend class CircularBuffer;

  using value_type = T;
  using pointer = std::conditional_t<IsConst, const T *, T *>;
  using reference = std::conditional_t<IsConst, const T &, T &>;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::random_access_iterator_tag;

  BaseIterator(const BaseIterator &other) {
    if (other != *this) {
      this->m_ptr = other.m_ptr;
    }
  }
  BaseIterator &operator=(const BaseIterator &other) {
    if (other != *this) {
      this->m_ptr = other.m_ptr;
    }

    return *this;
  }

  BaseIterator(BaseIterator &&other) = default;
  BaseIterator &operator=(BaseIterator &&other) = default;

  operator BaseIterator<true>() const { return {m_ptr}; }

  reference operator*() const { return *(m_ptr); }
  pointer operator->() const { return m_ptr; }

  bool operator<(const BaseIterator &otherIterator) const {
    return (this->m_ptr < otherIterator.m_ptr);
  }

  bool operator>(const BaseIterator &otherIterator) const {
    return (this->m_ptr > otherIterator.m_ptr);
  }

  bool operator>=(const BaseIterator &otherIterator) const {
    return (this->m_ptr >= otherIterator.m_ptr);
  }

  bool operator<=(const BaseIterator &otherIterator) const {
    return (this->m_ptr <= otherIterator.m_ptr);
  }

  bool operator==(const BaseIterator &other) const {
    return (this->m_ptr == other.m_ptr);
  }

  bool operator!=(const BaseIterator &other) const {
    return (this->m_ptr != other.m_ptr);
  }

  BaseIterator &operator+(size_t value) {
    m_ptr += value;
    return *this;
  }

  BaseIterator &operator-(size_t value) {
    m_ptr -= value;
    return *this;
  }

  BaseIterator &operator+=(int value) {
    m_ptr = m_ptr + value;
    return *this;
  }

  BaseIterator &operator-=(int value) {
    m_ptr = m_ptr - value;
    return *this;
  }

  BaseIterator &operator++() {
    ++m_ptr;
    return *this;
  }

  BaseIterator operator++(int) {
    BaseIterator copy = *this;
    ++m_ptr;
    return copy;
  }

  BaseIterator &operator--() {
    --m_ptr;
    return *this;
  }

  BaseIterator operator--(int) {
    BaseIterator copy = m_ptr;
    --m_ptr;
    return copy;
  }

  private:
  explicit BaseIterator(pointer ptr) : m_ptr(ptr) {}

  pointer m_ptr;
};

// overloading operators

template <typename T, typename Alloc>
T &CircularBuffer<T, Alloc>::operator[](size_t index) {
  if (m_start < m_end) {
    return (m_Arr[m_start + index]);
  } else {
    if (m_Capacity - m_start > index) {
      return (m_Arr[m_start + index]);
    } else {
      return (m_Arr[index - (m_Capacity - m_start)]);
    }
  }
}

template <typename T, typename Alloc>
bool CircularBuffer<T, Alloc>::operator==(const CircularBuffer &other) {
  return (m_Size == other.m_Size &&
          std::equal(begin(), end(), other.begin(), other.end()));
}

template <typename T, typename Alloc>
bool CircularBuffer<T, Alloc>::operator!=(const CircularBuffer &other) {
  return !(*this == other);
}

// container methods

template <typename T, typename Alloc>
size_t CircularBuffer<T, Alloc>::Size() const {
  return (this->m_Size);
}

template <typename T, typename Alloc>
size_t CircularBuffer<T, Alloc>::Capacity() const {
  return (this->m_Capacity);
}

template <typename T, typename Alloc>
bool CircularBuffer<T, Alloc>::Empty() const {
  return !(m_Size);
}

template <typename T, typename Alloc>
void CircularBuffer<T, Alloc>::ShowBuffer() const {
  std::cout << "m_start : " << m_start << "  m_end : " << m_end << std::endl
            << std::endl;

  std::cout << "{ ";

  size_t index;

  if (m_Size == 0) {
    std::cout << "empty ";
  } else {
    if (m_end <= m_start) {
      for (index = m_start; index < m_Capacity; ++index) {
        std::cout << m_Arr[index] << " ";
      }

      for (index = 0; index < m_end; ++index) {
        std::cout << m_Arr[index] << " ";
      }
    } else {
      for (index = m_start; index < m_end; ++index) {
        std::cout << m_Arr[index] << " ";
      }
    }
  }

  std::cout << "}";
}

template <typename T, typename Alloc>
void CircularBuffer<T, Alloc>::reserve(size_t NewCap) {
  if (NewCap == m_Capacity) {
    return;
  }

  T *newArr = m_AllocTraits::allocate(m_Alloc, NewCap);

  size_t index = 0;

  size_t flag = m_Size < NewCap ? m_Size : NewCap;

  try {
    for (; index < flag; ++index) {
      m_AllocTraits::construct(m_Alloc, newArr, m_Arr[index]);
    }
  } catch (...) {
    for (size_t oldIndex = 0; oldIndex < index; ++oldIndex) {
      m_AllocTraits::destroy(m_Alloc, newArr + oldIndex);
    }

    m_AllocTraits::deallocate(m_Alloc, newArr, NewCap);
    throw;
  }

  for (size_t index = 0; index < m_Size; ++index) {
    m_AllocTraits::destroy(m_Alloc, m_Arr + index);
  }
  m_AllocTraits::deallocate(m_Alloc, m_Arr, m_Capacity);

  m_Arr = newArr;
  m_Capacity = NewCap;
}

template <typename T, typename Alloc>
void CircularBuffer<T, Alloc>::Push(T &value, Iterator iter) {
  if (m_Capacity == 0) {
    return;
  }

  if (iter.m_ptr < m_Arr || iter.m_ptr > m_Arr + m_Capacity) {
    return;
  }

  if (m_Size == m_Capacity) {
    if (iter != end()) {
      if (m_start < m_end) {
        for (auto i = end(), j = end() - 1; i > iter; --i, --j) {
          std::swap(*i, *j);
        }
      } else {
        if (end() > iter) {
          for (auto i = end() - 1, j = end() - 2; i > iter; --i, --j) {
            std::swap(*i, *j);
          }
        } else {
          for (auto i = end() - 1, j = end() - 2; i.m_ptr > m_Arr; --i, --j) {
            std::swap(*i, *j);
          }

          std::swap(*m_Arr, *(m_Arr + m_Capacity - 1));

          for (auto i = m_Arr + m_Capacity - 1; i > iter.m_ptr; --i) {
            std::swap(*i, *(i - 1));
          }
        }
      }
    }
    m_AllocTraits::destroy(m_Alloc, iter.m_ptr);
  } else if (iter == end()) {
    m_AllocTraits::destroy(m_Alloc, iter.m_ptr);

    ++m_Size;
    m_end == m_Capacity ? m_end = 1 : ++m_end;
  } else {
    if (m_end < m_start) {
      if (end() > iter) {
        for (auto i = end(), j = end() - 1; i > iter; --i, --j) {
          std::swap(*i, *j);
        }
      } else {
        for (auto i = end(), j = end() - 1; i.m_ptr > m_Arr; --i, --j) {
          std::swap(*i, *j);
        }

        std::swap(*m_Arr, *(m_Arr + m_Capacity - 1));

        for (auto i = m_Arr + m_Capacity - 1; i > iter.m_ptr; --i) {
          std::swap(*i, *(i - 1));
        }
      }
    } else {
      for (auto i = end(), j = end() - 1; i > iter; --i, --j) {
        std::swap(*i, *j);
      }
    }

    ++m_Size;
    m_end == m_Capacity ? m_end = 1 : ++m_end;
  }

  try {
    m_AllocTraits::construct(m_Alloc, iter.m_ptr, value);
  } catch (...) {
    std::cerr << "Error construct in T" << std::endl;
  }
}

template <typename T, typename Alloc>
void CircularBuffer<T, Alloc>::Push(const T &value, ConstIterator iter) {
  if (m_Capacity == 0) {
    return;
  }

  if (iter.m_ptr < m_Arr || iter.m_ptr > m_Arr + m_Capacity) {
    return;
  }

  if (m_Size == m_Capacity) {
    if (iter != end()) {
      if (m_start < m_end) {
        for (auto i = end(), j = end() - 1; i > iter; --i, --j) {
          std::swap(*i, *j);
        }
      } else {
        if (end() > iter) {
          for (auto i = end() - 1, j = end() - 2; i > iter; --i, --j) {
            std::swap(*i, *j);
          }
        } else {
          for (auto i = end() - 1, j = end() - 2; i.m_ptr > m_Arr; --i, --j) {
            std::swap(*i, *j);
          }

          std::swap(*m_Arr, *(m_Arr + m_Capacity - 1));

          for (auto i = m_Arr + m_Capacity - 1; i > iter.m_ptr; --i) {
            std::swap(*i, *(i - 1));
          }
        }
      }
    }
    m_AllocTraits::destroy(m_Alloc, iter.m_ptr);
  } else if (iter == end()) {
    m_AllocTraits::destroy(m_Alloc, iter.m_ptr);

    ++m_Size;
    m_end == m_Capacity ? m_end = 1 : ++m_end;
  } else {
    if (m_end < m_start) {
      if (end() > iter) {
        for (auto i = end(), j = end() - 1; i > iter; --i, --j) {
          std::swap(*i, *j);
        }
      } else {
        for (auto i = end(), j = end() - 1; i.m_ptr > m_Arr; --i, --j) {
          std::swap(*i, *j);
        }

        std::swap(*m_Arr, *(m_Arr + m_Capacity - 1));

        for (auto i = m_Arr + m_Capacity - 1; i > iter.m_ptr; --i) {
          std::swap(*i, *(i - 1));
        }
      }
    } else {
      for (auto i = end(), j = end() - 1; i > iter; --i, --j) {
        std::swap(*i, *j);
      }
    }

    ++m_Size;
    m_end == m_Capacity ? m_end = 1 : ++m_end;
  }

  try {
    m_AllocTraits::construct(m_Alloc, iter.m_ptr, value);
  } catch (...) {
    std::cerr << "Error construct in T" << std::endl;
  }
}

template <typename T, typename Alloc>
void CircularBuffer<T, Alloc>::Delete(Iterator iter) {
  if (m_Size == 0) {
    return;
  }

  if (m_Size != m_Capacity) {
    if (m_end > m_start) {
      if (end() < iter) {
        return;
      }
    } else {
      if (end() < iter && iter < begin()) {
        return;
      }
    }
  }

  if (iter.m_ptr < m_Arr || iter.m_ptr > m_Arr + m_Capacity) {
    return;
  }

  if (m_Size == m_Capacity) {
    if (iter == end()) {
      m_AllocTraits::destroy(m_Alloc, iter.m_ptr - 1);
    } else {
      if (m_end > m_start) {
        for (auto i = iter, j = iter + 1; i < end() - 1; ++i, ++j) {
          std::swap(*i, *j);
        }
      } else {
        if (iter > begin()) {
          for (auto i = iter, j = iter + 1; i.m_ptr < m_Arr + m_Capacity - 1;
               ++i, ++j) {
            std::swap(*i, *j);
          }

          std::swap(*(m_Arr + m_Capacity - 1), *m_Arr);

          for (auto i = begin(), j = begin() + 1; i < end() - 1; ++i, ++j) {
            std::swap(*i, *j);
          }
        } else {
          for (auto i = iter, j = iter + 1; i < end() - 1; ++i, ++j) {
            std::swap(*i, *j);
          }
        }
      }
      m_AllocTraits::destroy(m_Alloc, end().m_ptr - 1);
    }
  } else {
    if (iter == end()) {
      m_AllocTraits::destroy(m_Alloc, iter.m_ptr - 1);
    } else {
      if (m_end > m_start) {
        for (auto i = iter, j = iter + 1; i < end() - 1; ++i, ++j) {
          std::swap(*i, *j);
        }
      } else {
        if (iter > begin()) {
          for (auto i = iter, j = iter + 1; i.m_ptr < m_Arr + m_Capacity - 1;
               ++i, ++j) {
            std::swap(*i, *j);
          }
          std::swap(*m_Arr, *(m_Arr + m_Capacity - 1));

          for (auto i = begin(), j = begin() + 1; i < end() - 1; ++i, ++j) {
            std::swap(*i, *j);
          }
        } else {
          for (auto i = iter, j = iter + 1; i < end() - 1; ++i, ++j) {
            std::swap(*i, *j);
          }
        }
      }

      m_AllocTraits::destroy(m_Alloc, end().m_ptr - 1);
    }
  }

  --m_Size;
  if (m_start == 0 && m_end == 1) {
    --m_end;
  } else if (m_end == 1) {
    m_end = m_Capacity;
  } else {
    --m_end;
  }
}

template <typename T, typename Alloc>
void CircularBuffer<T, Alloc>::Delete(ConstIterator iter) {
  if (m_Size == 0) {
    return;
  }

  if (m_Size != m_Capacity) {
    if (m_end > m_start) {
      if (end() < iter) {
        return;
      }
    } else {
      if (end() < iter && iter < begin()) {
        return;
      }
    }
  }

  if (iter.m_ptr < m_Arr || iter.m_ptr > m_Arr + m_Capacity) {
    return;
  }

  if (m_Size == m_Capacity) {
    if (iter == end()) {
      m_AllocTraits::destroy(m_Alloc, iter.m_ptr - 1);
    } else {
      if (m_end > m_start) {
        for (auto i = iter, j = iter + 1; i < end() - 1; ++i, ++j) {
          std::swap(*i, *j);
        }
      } else {
        if (iter > begin()) {
          for (auto i = iter, j = iter + 1; i.m_ptr < m_Arr + m_Capacity - 1;
               ++i, ++j) {
            std::swap(*i, *j);
          }

          std::swap(*(m_Arr + m_Capacity - 1), *m_Arr);

          for (auto i = begin(), j = begin() + 1; i < end() - 1; ++i, ++j) {
            std::swap(*i, *j);
          }
        } else {
          for (auto i = iter, j = iter + 1; i < end() - 1; ++i, ++j) {
            std::swap(*i, *j);
          }
        }
      }
      m_AllocTraits::destroy(m_Alloc, end().m_ptr - 1);
    }
  } else {
    if (iter == end()) {
      m_AllocTraits::destroy(m_Alloc, iter.m_ptr - 1);
    } else {
      if (m_end > m_start) {
        for (auto i = iter, j = iter + 1; i < end() - 1; ++i, ++j) {
          std::swap(*i, *j);
        }
      } else {
        if (iter > begin()) {
          for (auto i = iter, j = iter + 1; i.m_ptr < m_Arr + m_Capacity - 1;
               ++i, ++j) {
            std::swap(*i, *j);
          }
          std::swap(*m_Arr, *(m_Arr + m_Capacity - 1));

          for (auto i = begin(), j = begin() + 1; i < end() - 1; ++i, ++j) {
            std::swap(*i, *j);
          }
        } else {
          for (auto i = iter, j = iter + 1; i < end() - 1; ++i, ++j) {
            std::swap(*i, *j);
          }
        }
      }

      m_AllocTraits::destroy(m_Alloc, end().m_ptr - 1);
    }
  }

  --m_Size;
  if (m_start == 0 && m_end == 1) {
    --m_end;
  } else if (m_end == 1) {
    m_end = m_Capacity;
  } else {
    --m_end;
  }
}

template <typename T, typename Alloc>
void CircularBuffer<T, Alloc>::PushBack(T &value) {
  if (m_Capacity == 0) {
    return;
  }

  if (m_Size == m_Capacity) {
    m_AllocTraits::destroy(m_Alloc, m_Arr + m_start);

    try {
      m_AllocTraits::construct(m_Alloc, m_Arr + m_start, value);

    } catch (...) {
      std::cerr << "Error construct in T" << std::endl;
      return;
    }

    if (m_end == m_Capacity) {
      m_end = 1;

      if (m_start == m_Capacity - 1) {
        m_start = 0;
      } else {
        ++m_start;
      }
    } else if (m_end <= m_start) {
      if (m_start == m_Capacity - 1) {
        m_start = 0;
      } else {
        ++m_start;
      }

      ++m_end;
    }
  } else {
    if (m_end == m_Capacity) {
      try {
        m_AllocTraits::construct(m_Alloc, m_Arr, value);
      } catch (...) {
        std::cerr << "Error construct in T" << std::endl;
        return;
      }

      m_end = 1;
    } else {
      try {
        m_AllocTraits::construct(m_Alloc, m_Arr + m_end, value);

      } catch (...) {
        std::cerr << "Error construct in T" << std::endl;
        return;
      }

      ++m_end;
    }

    ++m_Size;
  }
}

template <typename T, typename Alloc>
void CircularBuffer<T, Alloc>::PushBack(const T &value) {
  if (m_Capacity == 0) {
    return;
  }

  if (m_Size == m_Capacity) {
    m_AllocTraits::destroy(m_Alloc, m_Arr + m_start);

    try {
      m_AllocTraits::construct(m_Alloc, m_Arr + m_start, value);

    } catch (...) {
      std::cerr << "Error construct in T" << std::endl;
      return;
    }

    if (m_end == m_Capacity) {
      m_end = 1;

      if (m_start == m_Capacity - 1) {
        m_start = 0;
      } else {
        ++m_start;
      }
    } else if (m_end <= m_start) {
      if (m_start == m_Capacity - 1) {
        m_start = 0;
      } else {
        ++m_start;
      }

      ++m_end;
    }
  } else {
    if (m_end == m_Capacity) {
      try {
        m_AllocTraits::construct(m_Alloc, m_Arr, value);
      } catch (...) {
        std::cerr << "Error construct in T" << std::endl;
        return;
      }

      m_end = 1;
    } else {
      try {
        m_AllocTraits::construct(m_Alloc, m_Arr + m_end, value);

      } catch (...) {
        std::cerr << "Error construct in T" << std::endl;
        return;
      }

      ++m_end;
    }

    ++m_Size;
  }
}

template <typename T, typename Alloc>
void CircularBuffer<T, Alloc>::PopBack() {
  if (m_Size == 0) {
    return;
  }

  m_AllocTraits::destroy(m_Alloc, m_Arr + m_end - 1);

  if (m_end == 1) {
    m_end = m_Capacity;
  } else {
    --m_end;
  }

  --m_Size;
}

template <typename T, typename Alloc>
void CircularBuffer<T, Alloc>::PushFront(T &value) {
  if (m_Capacity == 0) {
    return;
  }

  if (m_Size == m_Capacity) {
    if (m_start < m_end) {
      m_AllocTraits::destroy(m_Alloc, m_Arr + m_Capacity - 1);

      try {
        m_AllocTraits::construct(m_Alloc, m_Arr + m_Capacity - 1, value);

      } catch (...) {
        std::cerr << "Error construct in T" << std::endl;
        return;
      }

      m_start = m_Capacity - 1;
      --m_end;
    } else {
      m_AllocTraits::destroy(m_Alloc, m_Arr + m_start - 1);

      try {
        m_AllocTraits::construct(m_Alloc, m_Arr + m_start - 1, value);

      } catch (...) {
        std::cerr << "Error construct in T" << std::endl;
        return;
      }

      --m_start;

      if (m_end == 1) {
        m_end = m_Capacity;
      } else {
        --m_end;
      }
    }
  } else {
    size_t tmpStart = m_start;

    if (m_start == 0) {
      m_start = m_Capacity - 1;

      if (m_end == 0) {
        m_end = m_Capacity;
      }
    } else {
      --m_start;
    }

    try {
      m_AllocTraits::construct(m_Alloc, m_Arr + m_start, value);

    } catch (...) {
      m_start = tmpStart;
      std::cerr << "Error construct in T" << std::endl;
      return;
    }

    ++m_Size;
  }
}

template <typename T, typename Alloc>
void CircularBuffer<T, Alloc>::PushFront(const T &value) {
  if (m_Capacity == 0) {
    return;
  }

  if (m_Size == m_Capacity) {
    if (m_start < m_end) {
      m_AllocTraits::destroy(m_Alloc, m_Arr + m_Capacity - 1);

      try {
        m_AllocTraits::construct(m_Alloc, m_Arr + m_Capacity - 1, value);

      } catch (...) {
        std::cerr << "Error construct in T" << std::endl;
        return;
      }

      m_start = m_Capacity - 1;
      --m_end;
    } else {
      m_AllocTraits::destroy(m_Alloc, m_Arr + m_start - 1);

      try {
        m_AllocTraits::construct(m_Alloc, m_Arr + m_start - 1, value);

      } catch (...) {
        std::cerr << "Error construct in T" << std::endl;
        return;
      }

      --m_start;

      if (m_end == 1) {
        m_end = m_Capacity;
      } else {
        --m_end;
      }
    }
  } else {
    size_t tmpStart = m_start;

    if (m_start == 0) {
      m_start = m_Capacity - 1;

      if (m_end == 0) {
        m_end = m_Capacity;
      }
    } else {
      --m_start;
    }

    try {
      m_AllocTraits::construct(m_Alloc, m_Arr + m_start, value);

    } catch (...) {
      m_start = tmpStart;
      std::cerr << "Error construct in T" << std::endl;
      return;
    }

    ++m_Size;
  }
}

template <typename T, typename Alloc>
void CircularBuffer<T, Alloc>::PopFront() {
  m_AllocTraits::destroy(m_Alloc, m_Arr + m_start);

  if (m_start == m_Capacity - 1) {
    m_start = 0;
  } else {
    ++m_start;
  }

  --m_Size;
}

// Iterator method

template <typename T, typename Alloc>
typename CircularBuffer<T, Alloc>::Iterator CircularBuffer<T, Alloc>::begin() {
  return Iterator(m_Arr + m_start);
}

template <typename T, typename Alloc>
typename CircularBuffer<T, Alloc>::Iterator CircularBuffer<T, Alloc>::end() {
  return Iterator(m_Arr + m_end);
}

template <typename T, typename Alloc>
typename CircularBuffer<T, Alloc>::ConstIterator
CircularBuffer<T, Alloc>::begin() const {
  return ConstIterator(m_Arr + m_start);
}

template <typename T, typename Alloc>
typename CircularBuffer<T, Alloc>::ConstIterator CircularBuffer<T, Alloc>::end()
    const {
  return ConstIterator(m_Arr + m_end);
}

template <typename T, typename Alloc>
typename CircularBuffer<T, Alloc>::ConstIterator
CircularBuffer<T, Alloc>::Cbegin() const {
  return {m_Arr + m_start};
}

template <typename T, typename Alloc>
typename CircularBuffer<T, Alloc>::ConstIterator
CircularBuffer<T, Alloc>::Cend() const {
  return {m_Arr + m_end};
}

