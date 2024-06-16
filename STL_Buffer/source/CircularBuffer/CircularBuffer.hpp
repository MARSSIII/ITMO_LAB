#pragma once

#include <initializer_list>
#include <type_traits>

#include <algorithm>
#include <iostream>
#include <memory>

template< typename T, typename Alloc = std::allocator< T > >
class CircularBuffer {
  private:
	size_t m_Size;
	size_t m_Capacity;

	Alloc m_Alloc;

	T *m_Arr;

	size_t m_start;
	size_t m_end;

	void m_RemoveBuffer() {
		for (size_t index = 0; index < m_Capacity; ++index) {
			m_Alloc.destroy(m_Arr + index);
		}

		m_Alloc.deallocate(m_Arr, m_Capacity);
	}

	template< bool IsConst >
	class BaseIterator {
	  public:
		friend class CircularBuffer;

		using pointer = std::conditional_t< IsConst, const T *, T * >;
		using reference = std::conditional_t< IsConst, const T &, T & >;
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

		reference operator*() const { return *(m_ptr); }
		pointer operator->() const { return m_ptr; }

		bool operator<(const BaseIterator &otherIterator) const { return (this->m_ptr < otherIterator.m_ptr); }

		bool operator>(const BaseIterator &otherIterator) const { return (this->m_ptr > otherIterator.m_ptr); }

		bool operator>=(const BaseIterator &otherIterator) const { return (this->m_ptr >= otherIterator.m_ptr); }

		bool operator<=(const BaseIterator &otherIterator) const { return (this->m_ptr <= otherIterator.m_ptr); }

		bool operator==(const BaseIterator &other) const { return (this->m_ptr == other.m_ptr); }

		bool operator!=(const BaseIterator &other) const { return (this->m_ptr != other.m_ptr); }

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
  
	template< bool IsConst >
	void swap(BaseIterator< IsConst > &first, BaseIterator< IsConst > &second) {
		using std::swap;
		swap(*first, *second);
	}


  public:
	CircularBuffer() : m_Size(0), m_Capacity(0), m_start(0), m_end(0), m_Arr(nullptr) {}

	CircularBuffer(size_t Capacity) :
		m_Arr(m_Alloc.allocate(Capacity)), m_Size(0), m_Capacity(Capacity), m_start(0), m_end(1) {}

	CircularBuffer(std::initializer_list< T > list) :
		m_Arr(m_Alloc.allocate(list.size())), m_Size(list.size()), m_Capacity(list.size()), m_start(0), m_end(list.size()) {
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

	~CircularBuffer() { this->m_RemoveBuffer(); }

	CircularBuffer(const CircularBuffer &other) {
		if (this == other) {
			return;
		}

		this->m_RemoveBuffer;

		m_Alloc(m_Arr, other.m_Capacity);

		size_t index = 0;

		try {
			for (; index < other.m_Capacity; ++index) {
				m_Alloc.construct(m_Arr + index, other.m_Arr[index]);
			}
		} catch (...) {
			for (size_t oldIndex = 0; oldIndex < index; ++oldIndex) {
				m_Alloc.destroy(m_Arr + oldIndex);
			}

			m_Alloc.deallocate(m_Arr, other.m_Capacity);
			throw;
		}

		m_Size = other.m_Size;
		m_Capacity = other.m_Capacity;
	}

	CircularBuffer &operator=(const CircularBuffer &other) {
		if (this == other) {
			return *this;
		}

		this->m_RemoveBuffer();

		m_Alloc(m_Arr, other.m_Capacity);

		size_t index = 0;

		try {
			for (; index < other.m_Capacity; ++index) {
				m_Alloc.construct(m_Arr + index, other.m_Arr[index]);
			}
		} catch (...) {
			for (size_t oldIndex = 0; oldIndex < index; ++oldIndex) {
				m_Alloc.destroy(m_Arr + oldIndex);
			}

			m_Alloc.deallocate(m_Arr, other.m_Capacity);
			throw;
		}

		m_Size = other.m_Size;
		m_Capacity = other.m_Capacity;
	}

	CircularBuffer(CircularBuffer &&other) {
		if (other == this) {
			return;
		}

		m_Size = other.m_Size;
		other.m_Size = 0;

		m_Capacity = other.m_Capacity;
		other.m_Capacity = 0;

		m_Alloc = other.m_Alloc;

		m_Arr = other.m_Arr;
		other.m_Arr = nullptr;

		m_start = other.m_start;
		other.m_start = 0;

		m_end = other.m_end;
		other.m_end = 0;
	}

	CircularBuffer &operator=(const CircularBuffer &&other) {
		if (this == other) {
			return *this;
		}

		m_Size = other.m_Size;
		other.m_Size = 0;

		m_Capacity = other.m_Capacity;
		other.m_Capacity = 0;

		m_Alloc = other.m_Alloc;

		m_Arr = other.m_Arr;
		other.m_Arr = nullptr;

		m_start = other.m_start;
		other.m_start = 0;

		m_end = other.m_end;
		other.m_end = 0;

		return *this;
	}

	using Iterator = BaseIterator< false >;
	using ConstIterator = BaseIterator< true >;

	T &operator[](size_t index) {
		if (m_start < m_end) {
			return (m_Arr[m_start + index]);
		}
		else {
			if (m_Capacity - m_start > index) {
				return (m_Arr[m_start + index]);
			}
			else {
				return (m_Arr[index - (m_Capacity - m_start)]);
			}
		}
	}

	size_t Size() const { return (this->m_Size); }

	size_t Capacity() const { return (this->m_Capacity); }

	bool Empty() const { return !(m_Size); }

	bool operator==(const CircularBuffer &other) {
		return (m_Size == other.m_Size && std::equal(begin(), end(), other.begin(), other.end()));
	}

	bool operator!=(const CircularBuffer &other) { return !(*this == other); }

	void ShowBuffer() const {
		std::cout << "m_start : " << m_start << "  m_end : " << m_end << std::endl << std::endl;

		std::cout << "{ ";

		size_t index;

		if (m_Size == 0) {
			std::cout << "empty ";
		}
		else {
			if (m_end <= m_start) {
				for (index = m_start; index < m_Capacity; ++index) {
					std::cout << m_Arr[index] << " ";
				}

				for (index = 0; index < m_end; ++index) {
					std::cout << m_Arr[index] << " ";
				}
			}
			else {
				for (index = m_start; index < m_end; ++index) {
					std::cout << m_Arr[index] << " ";
				}
			}
		}

		std::cout << "}";
	}

	void Push(T &value, Iterator iter) {
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
				}
				else {
					if (end() > iter) {
						for (auto i = end() - 1, j = end() - 2; i > iter; --i, --j) {
							std::swap(*i, *j);
						}
					}
					else {
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
			m_Alloc.destroy(iter.m_ptr);
		}
		else if (iter == end()) {
			m_Alloc.destroy(iter.m_ptr);

			++m_Size;
			m_end == m_Capacity ? m_end = 1 : ++m_end;
		}
		else {
			if (m_end < m_start) {
				if (end() > iter) {
					for (auto i = end(), j = end() - 1; i > iter; --i, --j) {
						std::swap(*i, *j);
					}
				}
				else {
					for (auto i = end(), j = end() - 1; i.m_ptr > m_Arr; --i, --j) {
						std::swap(*i, *j);
					}

					std::swap(*m_Arr, *(m_Arr + m_Capacity - 1));

					for (auto i = m_Arr + m_Capacity - 1; i > iter.m_ptr; --i) {
						std::swap(*i, *(i - 1));
					}
				}
			}
			else {
				for (auto i = end(), j = end() - 1; i > iter; --i, --j) {
					std::swap(*i, *j);
				}
			}

			++m_Size;
			m_end == m_Capacity ? m_end = 1 : ++m_end;
		}

		try {
			m_Alloc.construct(iter.m_ptr, value);
		} catch (...) {
			std::cerr << "Error construct in T" << std::endl;
		}
	}

	void Push(const T &value, ConstIterator iter) {
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
				}
				else {
					if (end() > iter) {
						for (auto i = end() - 1, j = end() - 2; i > iter; --i, --j) {
							std::swap(*i, *j);
						}
					}
					else {
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
			m_Alloc.destroy(iter.m_ptr);
		}
		else if (iter == end()) {
			m_Alloc.destroy(iter.m_ptr);

			++m_Size;
			m_end == m_Capacity ? m_end = 1 : ++m_end;
		}
		else {
			if (m_end < m_start) {
				if (end() > iter) {
					for (auto i = end(), j = end() - 1; i > iter; --i, --j) {
						std::swap(*i, *j);
					}
				}
				else {
					for (auto i = end(), j = end() - 1; i.m_ptr > m_Arr; --i, --j) {
						std::swap(*i, *j);
					}

					std::swap(*m_Arr, *(m_Arr + m_Capacity - 1));

					for (auto i = m_Arr + m_Capacity - 1; i > iter.m_ptr; --i) {
						std::swap(*i, *(i - 1));
					}
				}
			}
			else {
				for (auto i = end(), j = end() - 1; i > iter; --i, --j) {
					std::swap(*i, *j);
				}
			}

			++m_Size;
			m_end == m_Capacity ? m_end = 1 : ++m_end;
		}

		try {
			m_Alloc.construct(iter.m_ptr, value);
		} catch (...) {
			std::cerr << "Error construct in T" << std::endl;
		}
	}

	void Delete(Iterator iter) {
		if (m_Size == 0) {
			return;
		}

		if (m_Size != m_Capacity) {
			if (m_end > m_start) {
				if (end() < iter) {
					return;
				}
			}
			else {
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
				m_Alloc.destroy(iter.m_ptr - 1);
			}
			else {
				if (m_end > m_start) {
					for (auto i = iter, j = iter + 1; i < end() - 1; ++i, ++j) {
						std::swap(*i, *j);
					}
				}
				else {
					if (iter > begin()) {
						for (auto i = iter, j = iter + 1; i.m_ptr < m_Arr + m_Capacity - 1; ++i, ++j) {
							std::swap(*i, *j);
						}

						std::swap(*(m_Arr + m_Capacity - 1), *m_Arr);

						for (auto i = begin(), j = begin() + 1; i < end() - 1; ++i, ++j) {
							std::swap(*i, *j);
						}
					}
					else {
						for (auto i = iter, j = iter + 1; i < end() - 1; ++i, ++j) {
							std::swap(*i, *j);
						}
					}
				}
				m_Alloc.destroy(end().m_ptr - 1);
			}
		}
		else {
			if (iter == end()) {
				m_Alloc.destroy(iter.m_ptr - 1);
			}
			else {
				if (m_end > m_start) {
					for (auto i = iter, j = iter + 1; i < end() - 1; ++i, ++j) {
						std::swap(*i, *j);
					}
				}
				else {
					if (iter > begin()) {
						for (auto i = iter, j = iter + 1; i.m_ptr < m_Arr + m_Capacity - 1; ++i, ++j) {
							std::swap(*i, *j);
						}
						std::swap(*m_Arr, *(m_Arr + m_Capacity - 1));

						for (auto i = begin(), j = begin() + 1; i < end() - 1; ++i, ++j) {
							std::swap(*i, *j);
						}
					}
					else {
						for (auto i = iter, j = iter + 1; i < end() - 1; ++i, ++j) {
							std::swap(*i, *j);
						}
					}
				}

				m_Alloc.destroy(end().m_ptr - 1);
			}
		}

		--m_Size;
		if (m_start == 0 && m_end == 1) {
			--m_end;
		}
		else if (m_end == 1) {
			m_end = m_Capacity;
		}
		else {
			--m_end;
		}
	}

	void Delete(ConstIterator iter) {
		if (m_Size == 0) {
			return;
		}

		if (m_Size != m_Capacity) {
			if (m_end > m_start) {
				if (end() < iter) {
					return;
				}
			}
			else {
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
				m_Alloc.destroy(iter.m_ptr - 1);
			}
			else {
				if (m_end > m_start) {
					for (auto i = iter, j = iter + 1; i < end() - 1; ++i, ++j) {
						std::swap(*i, *j);
					}
				}
				else {
					if (iter > begin()) {
						for (auto i = iter, j = iter + 1; i.m_ptr < m_Arr + m_Capacity - 1; ++i, ++j) {
							std::swap(*i, *j);
						}

						std::swap(*(m_Arr + m_Capacity - 1), *m_Arr);

						for (auto i = begin(), j = begin() + 1; i < end() - 1; ++i, ++j) {
							std::swap(*i, *j);
						}
					}
					else {
						for (auto i = iter, j = iter + 1; i < end() - 1; ++i, ++j) {
							std::swap(*i, *j);
						}
					}
				}
				m_Alloc.destroy(end().m_ptr - 1);
			}
		}
		else {
			if (iter == end()) {
				m_Alloc.destroy(iter.m_ptr - 1);
			}
			else {
				if (m_end > m_start) {
					for (auto i = iter, j = iter + 1; i < end() - 1; ++i, ++j) {
						std::swap(*i, *j);
					}
				}
				else {
					if (iter > begin()) {
						for (auto i = iter, j = iter + 1; i.m_ptr < m_Arr + m_Capacity - 1; ++i, ++j) {
							std::swap(*i, *j);
						}
						std::swap(*m_Arr, *(m_Arr + m_Capacity - 1));

						for (auto i = begin(), j = begin() + 1; i < end() - 1; ++i, ++j) {
							std::swap(*i, *j);
						}
					}
					else {
						for (auto i = iter, j = iter + 1; i < end() - 1; ++i, ++j) {
							std::swap(*i, *j);
						}
					}
				}

				m_Alloc.destroy(end().m_ptr - 1);
			}
		}

		--m_Size;
		if (m_start == 0 && m_end == 1) {
			--m_end;
		}
		else if (m_end == 1) {
			m_end = m_Capacity;
		}
		else {
			--m_end;
		}
	}

	void reserve(size_t NewCap) {
		if (NewCap == m_Capacity) {
			return;
		}

		T *newArr = m_Alloc.allocate(NewCap);

		size_t index = 0;

		size_t flag = m_Size < NewCap ? m_Size : NewCap;

		try {
			for (; index < flag; ++index) {
				m_Alloc.construct(newArr + index, m_Arr[index]);
			}
		} catch (...) {
			for (size_t oldIndex = 0; oldIndex < index; ++oldIndex) {
				m_Alloc.destroy(newArr + oldIndex);
			}

			m_Alloc.deallocate(newArr, NewCap);
			throw;
		}

		for (size_t index = 0; index < m_Size; ++index) {
			m_Alloc.destroy(m_Arr + index);
		}
		m_Alloc.deallocate(m_Arr, m_Capacity);

		m_Arr = newArr;
		m_Capacity = NewCap;
	}

	void PushBack(T &value) {
		if (m_Capacity == 0) {
			return;
		}

		if (m_Size == m_Capacity) {
			m_Alloc.destroy(m_Arr + m_start);

			try {
				m_Alloc.construct(m_Arr + m_start, value);

			} catch (...) {
				std::cerr << "Error construct in T" << std::endl;
				return;
			}

			if (m_end == m_Capacity) {
				m_end = 1;

				if (m_start == m_Capacity - 1) {
					m_start = 0;
				}
				else {
					++m_start;
				}
			}
			else if (m_end <= m_start) {
				if (m_start == m_Capacity - 1) {
					m_start = 0;
				}
				else {
					++m_start;
				}

				++m_end;
			}
		}
		else {
			if (m_end == m_Capacity) {
				try {
					m_Alloc.construct(m_Arr, value);
				} catch (...) {
					std::cerr << "Error construct in T" << std::endl;
					return;
				}

				m_end = 1;
			}
			else {
				try {
					m_Alloc.construct(m_Arr + m_end, value);

				} catch (...) {
					std::cerr << "Error construct in T" << std::endl;
					return;
				}

				++m_end;
			}

			++m_Size;
		}
	}

	void PushBack(const T &value) {
		if (m_Capacity == 0) {
			return;
		}

		if (m_Size == m_Capacity) {
			m_Alloc.destroy(m_Arr + m_start);

			try {
				m_Alloc.construct(m_Arr + m_start, value);

			} catch (...) {
				std::cerr << "Error construct in T" << std::endl;
				return;
			}

			if (m_end == m_Capacity) {
				m_end = 1;

				if (m_start == m_Capacity - 1) {
					m_start = 0;
				}
				else {
					++m_start;
				}
			}
			else if (m_end <= m_start) {
				if (m_start == m_Capacity - 1) {
					m_start = 0;
				}
				else {
					++m_start;
				}

				++m_end;
			}
		}
		else {
			if (m_end == m_Capacity) {
				try {
					m_Alloc.construct(m_Arr, value);
				} catch (...) {
					std::cerr << "Error construct in T" << std::endl;
					return;
				}

				m_end = 1;
			}
			else {
				try {
					m_Alloc.construct(m_Arr + m_end, value);

				} catch (...) {
					std::cerr << "Error construct in T" << std::endl;
					return;
				}

				++m_end;
			}

			++m_Size;
		}
	}

	void PopBack() {
		if (m_Size == 0) {
			return;
		}

		m_Alloc.destroy(m_Arr + m_end - 1);

		if (m_end == 1) {
			m_end = m_Capacity;
		}
		else {
			--m_end;
		}

		--m_Size;
	}

	void PushFront(T &value) {
		if (m_Capacity == 0) {
			return;
		}

		if (m_Size == m_Capacity) {
			if (m_start < m_end) {
				m_Alloc.destroy(m_Arr + m_Capacity - 1);

				try {
					m_Alloc.construct(m_Arr + m_Capacity - 1, value);

				} catch (...) {
					std::cerr << "Error construct in T" << std::endl;
					return;
				}

				m_start = m_Capacity - 1;
				--m_end;
			}
			else {
				m_Alloc.destroy(m_Arr + m_start - 1);

				try {
					m_Alloc.construct(m_Arr + m_start - 1, value);

				} catch (...) {
					std::cerr << "Error construct in T" << std::endl;
					return;
				}

				--m_start;

				if (m_end == 1) {
					m_end = m_Capacity;
				}
				else {
					--m_end;
				}
			}
		}
		else {
			size_t tmpStart = m_start;

			if (m_start == 0) {
				m_start = m_Capacity - 1;

				if (m_end == 0) {
					m_end = m_Capacity;
				}
			}
			else {
				--m_start;
			}

			try {
				m_Alloc.construct(m_Arr + m_start, value);

			} catch (...) {
				m_start = tmpStart;
				std::cerr << "Error construct in T" << std::endl;
				return;
			}

			++m_Size;
		}
	}

	void PushFront(const T &value) {
		if (m_Capacity == 0) {
			return;
		}

		if (m_Size == m_Capacity) {
			if (m_start < m_end) {
				m_Alloc.destroy(m_Arr + m_Capacity - 1);

				try {
					m_Alloc.construct(m_Arr + m_Capacity - 1, value);

				} catch (...) {
					std::cerr << "Error construct in T" << std::endl;
					return;
				}

				m_start = m_Capacity - 1;
				--m_end;
			}
			else {
				m_Alloc.destroy(m_Arr + m_start - 1);

				try {
					m_Alloc.construct(m_Arr + m_start - 1, value);

				} catch (...) {
					std::cerr << "Error construct in T" << std::endl;
					return;
				}

				--m_start;

				if (m_end == 1) {
					m_end = m_Capacity;
				}
				else {
					--m_end;
				}
			}
		}
		else {
			size_t tmpStart = m_start;

			if (m_start == 0) {
				m_start = m_Capacity - 1;

				if (m_end == 0) {
					m_end = m_Capacity;
				}
			}
			else {
				--m_start;
			}

			try {
				m_Alloc.construct(m_Arr + m_start, value);

			} catch (...) {
				m_start = tmpStart;
				std::cerr << "Error construct in T" << std::endl;
				return;
			}

			++m_Size;
		}
	}

	void PopFront() {
		m_Alloc.destroy(m_Arr + m_start);

		if (m_start == m_Capacity - 1) {
			m_start = 0;
		}
		else {
			++m_start;
		}

		--m_Size;
	}

	Iterator begin() { return Iterator(m_Arr + m_start); }

	Iterator end() { return Iterator(m_Arr + m_end); }

	ConstIterator begin() const { return ConstIterator(m_Arr + m_start); }

	ConstIterator end() const { return ConstIterator(m_Arr + m_end); }

	ConstIterator Cbegin() const { return { m_Arr + m_start }; }

	ConstIterator Cend() const { return { m_Arr + m_end }; }
};




