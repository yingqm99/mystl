#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "vector.h"
#include <functional>

namespace YING {
	template <typename T, typename Compare = std::less<T>>
	class Heap_ {
	public:
		Heap_();
		Heap_(const YING::Vector<T>& v_, Compare comp_);
		~Heap_() = default;
		void heapify_();
		bool is_valid_() const;
		void insert_(const T& value);
		void delete_(const T& value);
		size_t size() const;
		bool empty() const;
		T top_() const;
		void pop_top_();

	private:
		friend class priority_queue;
		void fix_down_(int index_);
		void fix_up_(int index_);
		int find_(const T& value) const;
		YING::Vector v_;
		Compare comp_;
	};

	template <typename T, typename Compare = std::less<T>>
	class Priority_queue {
	public:
		Priority_queue();
		~Priority_queue() = default;
		void push(const T& value);
		void pop();
		size_t size() const;
		bool empty() const;
		T top() const;

	private:
		Heap_<T, Compare> heap_;
		Compare comp_;
	};
}

#endif