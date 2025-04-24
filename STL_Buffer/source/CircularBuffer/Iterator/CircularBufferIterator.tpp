#pragma once

template <typename T, bool IsConst>
CircularBufferIterator<T, IsConst>::CircularBufferIterator(pointer ptr) : m_ptr(ptr) {}

template <typename T, bool IsConst>
CircularBufferIterator<T, IsConst>::CircularBufferIterator(const CircularBufferIterator& other) {
    if (&other != this) {
        this->m_ptr = other.m_ptr;
    }
}

template <typename T, bool IsConst>
CircularBufferIterator<T, IsConst>& CircularBufferIterator<T, IsConst>::operator=(const CircularBufferIterator& other) {
    if (&other != this) {
        this->m_ptr = other.m_ptr;
    }
    return *this;
}

template <typename T, bool IsConst>
CircularBufferIterator<T, IsConst>::operator CircularBufferIterator<T, true>() const {
    return {m_ptr};
}

template <typename T, bool IsConst>
typename CircularBufferIterator<T, IsConst>::reference
CircularBufferIterator<T, IsConst>::operator*() const {
    return *(m_ptr);
}

template <typename T, bool IsConst>
typename CircularBufferIterator<T, IsConst>::pointer
CircularBufferIterator<T, IsConst>::operator->() const {
    return m_ptr;
}

template <typename T, bool IsConst>
bool CircularBufferIterator<T, IsConst>::operator<(const CircularBufferIterator& other) const {
    return (this->m_ptr < other.m_ptr);
}
template <typename T, bool IsConst>
bool CircularBufferIterator<T, IsConst>::operator>(const CircularBufferIterator& other) const {
    return (this->m_ptr > other.m_ptr);
}
template <typename T, bool IsConst>
bool CircularBufferIterator<T, IsConst>::operator>=(const CircularBufferIterator& other) const {
    return (this->m_ptr >= other.m_ptr);
}
template <typename T, bool IsConst>
bool CircularBufferIterator<T, IsConst>::operator<=(const CircularBufferIterator& other) const {
    return (this->m_ptr <= other.m_ptr);
}
template <typename T, bool IsConst>
bool CircularBufferIterator<T, IsConst>::operator==(const CircularBufferIterator& other) const {
    return (this->m_ptr == other.m_ptr);
}
template <typename T, bool IsConst>
bool CircularBufferIterator<T, IsConst>::operator!=(const CircularBufferIterator& other) const {
    return (this->m_ptr != other.m_ptr);
}
template <typename T, bool IsConst>
CircularBufferIterator<T, IsConst>& CircularBufferIterator<T, IsConst>::operator+(size_t value) {
    m_ptr += value;
    return *this;
}
template <typename T, bool IsConst>
CircularBufferIterator<T, IsConst>& CircularBufferIterator<T, IsConst>::operator-(size_t value) {
    m_ptr -= value;
    return *this;
}
template <typename T, bool IsConst>
CircularBufferIterator<T, IsConst>& CircularBufferIterator<T, IsConst>::operator+=(int value) {
    m_ptr = m_ptr + value;
    return *this;
}
template <typename T, bool IsConst>
CircularBufferIterator<T, IsConst>& CircularBufferIterator<T, IsConst>::operator-=(int value) {
    m_ptr = m_ptr - value;
    return *this;
}
template <typename T, bool IsConst>
CircularBufferIterator<T, IsConst>& CircularBufferIterator<T, IsConst>::operator++() {
    ++m_ptr;
    return *this;
}
template <typename T, bool IsConst>
CircularBufferIterator<T, IsConst> CircularBufferIterator<T, IsConst>::operator++(int) {
    CircularBufferIterator copy = *this;
    ++m_ptr;
    return copy;
}
template <typename T, bool IsConst>
CircularBufferIterator<T, IsConst>& CircularBufferIterator<T, IsConst>::operator--() {
    --m_ptr;
    return *this;
}
template <typename T, bool IsConst>
CircularBufferIterator<T, IsConst> CircularBufferIterator<T, IsConst>::operator--(int) {
    CircularBufferIterator copy = *this;
    --m_ptr;
    return copy;
}
