
#include "vector.h"
#include <cassert>
#include <memory>
#include <cstddef>
#include <iostream>

namespace YING {
	template <typename T, typename Allocator>
	Vector<T, Allocator>::Vector()
		:data_(alloc_.allocate(1)), size_(0), capacity_(1) {}
	
	template <typename T, typename Allocator>
	Vector<T, Allocator>::Vector(int count, const T& value) {
		T* ptr_mem_ = alloc_.allocate(count);
		data_ = ptr_mem_;
		for (int i = 0; i < count; i++) {
			alloc_.construct(ptr_mem_++, value);
		}
		capacity_ = count;
		size_ = static_cast<size_t>(count);
	}

	template <typename T, typename Allocator>
	Vector<T, Allocator>::Vector(const Vector<T, Allocator>& other) {
		T* ptr_mem_ = alloc_.allocate(other.size());
		data_ = ptr_mem_;
		for (size_t i = 0; i < other.size(); i++) {
			alloc_.construct(ptr_mem_++, other[i]);
		}
		capacity_ = other.size();
		size_ = other.size();
	}

	template <typename T, typename Allocator>
	Vector<T, Allocator>::~Vector() {
		for (size_t i = 0; i < size(); i++) {
			alloc_.destroy(data_ + i);
		}
		alloc_.deallocate(data_, size());
	}

	template <typename T, typename Allocator>
	void Vector<T, Allocator>::push_back(const T& value) {
		if (size_ == capacity_) {
			expand();
		}
		alloc_.construct(data_ + size(), value);
		size_++;
	}

	template <typename T, typename Allocator>
	void Vector<T, Allocator>::pop_back() {
		assert(size_ > 0);
		alloc_.destroy(data_ + size_);
		size_--;
	}

	template <typename T, typename Allocator>
	size_t Vector<T, Allocator>::size() const {
		return size_;
	}

	template <typename T, typename Allocator>
	T Vector<T, Allocator>::operator[](int index) const {
		assert(index < size_ && index >= 0);
		return data_[index];
	}

	template <typename T, typename Allocator>
	Vector<T, Allocator>& Vector<T, Allocator>::operator=(const Vector<T, Allocator>& rhs) {
		Vector<T, Allocator>::Vector(rhs);
		return *this;
	}

	template <typename T, typename Allocator>
	Vector<T, Allocator>& Vector<T, Allocator>::operator*(const Vector<T, Allocator>* v_) {
		return data_;
	}

	template <typename T, typename Allocator>
	void Vector<T, Allocator>::expand() {
		capacity_ *= 2;
		T* temp_ = alloc_.allocate(capacity_);
		for (size_t i = 0; i < size(); i++) {
			alloc_.construct(temp_ + i, data_[i]);
		}
		if (data_) {
			for (size_t i = 0; i < size(); i++) {
				alloc_.destroy(data_ + i);
			}
			alloc_.deallocate(data_, size());
		}

		data_ = temp_;
		size_ = size();
	}

	template <typename T, typename Allocator>
	Vector<T, Allocator>::Iterator::Iterator()
		:v_(nullptr), index_(-1) {}

	template <typename T, typename Allocator>
	Vector<T, Allocator>::Iterator::Iterator(const Vector<T, Allocator>* v_, int index_)
		:v_(v_), index_(index_) {}


	template <typename T, typename Allocator>
	typename Vector<T, Allocator>::Iterator& Vector<T, Allocator>::Iterator::operator++() {
		if (index_ == -1) {
			return *this;
		}
		index_++;
		if (index_ == v_->size()) {
			v_ = nullptr;
			index_ = -1;
		}
		return *this;
	}

	template <typename T, typename Allocator>
	typename Vector<T, Allocator>::Iterator Vector<T, Allocator>::Iterator::operator++(int) {
		Vector<T, Allocator>::Iterator _temp = *this;
		index_++;
		if (index_ == v_->size()) {
			index_ = -1;
		}
		return *this;
	}

	template <typename T, typename Allocator>
	typename Vector<T, Allocator>::Iterator& Vector<T, Allocator>::Iterator::operator--() {
		if (index_ == -1) {
			return *this;
		}
		index_--;
		return *this;
	}

	template <typename T, typename Allocator>
	typename Vector<T, Allocator>::Iterator Vector<T, Allocator>::Iterator::operator--(int) {
		Vector<T, Allocator>::Iterator _temp = *this;
		index_--;
		return _temp;
	}

	template <typename T, typename Allocator>
	T Vector<T, Allocator>::Iterator::operator*() const {
		// std::cout << v_->size() << " " << index_ << std::endl;
		return (*v_)[index_];
	}

	template <typename T, typename Allocator>
	typename Vector<T, Allocator>::Iterator& Vector<T, Allocator>::Iterator::operator=(const Iterator& rhs) {
		v_ = rhs.get_v_();
		index_ = rhs.get_index_();
		return *this;
	}

	template <typename T, typename Allocator>
	bool Vector<T, Allocator>::Iterator::operator==(const Vector<T, Allocator>::Iterator& rhs) const {
		return v_ == rhs.get_v_() && index_ == rhs.get_index_();
	}

	template <typename T, typename Allocator>
	bool Vector<T, Allocator>::Iterator::operator!=(const Vector<T, Allocator>::Iterator& rhs) const {
		return !(*this == rhs);
	}


	template <typename T, typename Allocator>
	typename Vector<T, Allocator>::Iterator Vector<T, Allocator>::begin() const {
		// std::cout << *data_ << std::endl;
		return Vector<T, Allocator>::Iterator(this, 0);
	}

	template <typename T, typename Allocator>
	typename Vector<T, Allocator>::Iterator Vector<T, Allocator>::end() const {
		return Iterator();
	}

	template <typename T, typename Allocator>
	const Vector<T, Allocator>* Vector<T, Allocator>::Iterator::get_v_() const {
		return v_;
	}

	template <typename T, typename Allocator>
	int Vector<T, Allocator>::Iterator::get_index_() const {
		return index_;
	}

	template <typename T, typename Allocator>
	Allocator Vector<T, Allocator>::alloc_;



}
