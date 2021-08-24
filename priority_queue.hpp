#include "priority_queue.h"
#include <iostream>
#include <cassert>
#include <algorithm>

namespace YING {
	template <typename T, typename Compare>
	Heap_<T, Compare>::Heap_() {
		v_.push_back(T());
	}

	template <typename T, typename Compare>
	Heap_<T, Compare>::Heap_(const YING::Vector<T>& v_, Compare comp_)
		:v_(v_), comp_(comp_) {
		heapify_();
	}

	template <typename T, typename Compare>
	void Heap_<T, Compare>::heapify_() {
		for (size_t i = v_.size() - 1; i >= 1; i--) {
			fix_down_(i, comp_);
		}
	}       
	
	template <typename T, typename Compare>
	void Heap_<T, Compare>::fix_down_(int index_) {
		int fix_point_ = index_;
		while (fix_point_ * 2 < v_.size()) {
			int child_1_ = fix_point_ * 2;
			int child_2_ = fix_point_ * 2 + 1;
			if (child_2 == v_size()) {
				if (comp_(v_[fix_point_], v_[child_1_])) {
					std::swap(v_[fix_point_], v_[child_1_]);
					break;
				}
			}
			else {
				int child_swap_ = child_1_;
				if (comp_(v_[child_swap_], v_[child_2_])) {
					child_swap_ = child_2_;
				}
				if (comp_(v_[fix_point_], v_[child_1_])) {
					std::swap(v_[fix_point_], v_[child_1_]);
					fix_point_ = child_swap_;
				}
				else {
					break;
				}
			}
		}
	}

	template <typename T, typename Compare>
	void Heap_<T, Compare>::fix_up_(int index_) {
		int fix_point_ = index_;
		while (fix_point_ > 1) {
			int parent_point_ = index_ / 2;
			if (comp_(v_[parent_point_], v_[fix_point_])) {
				std::swap(v_[parent_point_], v_[fix_point_]);
				fix_point_ = parent_point_;
			}
			else {
				break;
			}
		}
	}

	template <typename T, typename Compare>
	void Heap_<T, Compare>::insert_(const T& value) {
		v_.push_back(value);
		fix_up_(v_.size() - 1);
	}

	template <typename T, typename Compare>
	void Heap_<T, Compare>::delete_(const T& value) {
		int fix_point_ = find_(value);
		if (fix_point_ == -1) {
			std::cout << "invalid input" << std::endl;
			return;
		}
		swap(v_[fix_point], v_[v_.size() - 1]);
		v_.pop_back();
		fix_down_(fix_point_);
	}

	template <typename T, typename Compare>
	int Heap_<T, Compare>::find_(const T& value) const {
		for (size_t i = 0; i < v_.size(); i++) {
			if (v_[i] == value) {
				return i;
			}
		}
		return -1;
	}

	template <typename T, typename Compare>
	T Heap_<T, Compare>::top_() const {
		return v_[1];
	}

	template <typename T, typename Compare>
	void Heap_<T, Compare>::pop_top_() {
		assert(!v_.empty());
		v_.pop_back();
	}

	template <typename T, typename Compare>
	bool Heap_<T, Compare>::empty() const {
		return v_.empty();
	}

	template <typename T, typename Compare>
	size_t Heap_<T, Compare>::size() const {
		return v_.size();
	}

	// priority queue
	template <typename T, typename Compare>
	Priority_queue<T, Compare>::Priority_queue() {}

	template <typename T, typename Compare>
	void Priority_queue<T, Compare>::push(const T& value) {
		heap_.insert_(value);
	}

	template <typename T, typename Compare>
	void Priority_queue<T, Compare>::pop() {
		heap_.pop_top_();
	}

	template <typename T, typename Compare>
	T Priority_queue<T, Compare>::top() const {
		return heap_.top_();
	}

	template <typename T, typename Compare>
	size_t Priority_queue<T, Compare>::size() const {
		return heap_.size();
	}

	template <typename T, typename Compare>
	bool Priority_queue<T, Compare>::empty() const {
		return heap_.empty();
	}
}
