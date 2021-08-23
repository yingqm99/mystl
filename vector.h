#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <memory>

namespace YING {
	template <typename T, typename Allocator = std::allocator<T>>
	class Vector {
	public:
		class Iterator {
		public:
			Iterator();
			Iterator(const Vector<T, Allocator>* v_, int index_);
			~Iterator() = default;
			Iterator& operator++();
			Iterator operator++(int);
			Iterator& operator--();
			Iterator operator--(int);
			Iterator& operator=(const Iterator& rhs);
			bool operator==(const Iterator& rhs) const;
			bool operator!=(const Iterator& rhs) const;
			T operator*() const;

			const Vector<T, Allocator>* get_v_() const;
			int get_index_() const;

		private:
			const Vector<T, Allocator>* v_;
			int index_;
			friend class Vector;
			// Iterator(T* _start_ptr);
		};
		Vector();
		Vector(int count, const T& value);
		Vector(const Vector<T, Allocator>& other);
		~Vector();

		void push_back(const T& value);
		void pop_back();

		bool empty() const;

		Iterator begin() const;
		Iterator end() const;
		
		size_t size() const;
		T operator[](int index) const;
		Vector<T, Allocator>& operator=(const Vector<T, Allocator>& other);
		Vector<T, Allocator>& operator*(const Vector<T, Allocator>* v_);
	private:
		void expand();
		T* data_;
		size_t size_;
		int capacity_;
		static Allocator alloc_;
	};

}

#endif