#pragma once
#ifndef RB_TREE_H
#define RB_TREE_H

#include <functional>
#include "map.h"
#include "set.h"
enum RB_TREE_COLOR_ { RED, BLACK };

template <typename T,
	typename Compare = std::less<T>
>
class RB_Tree_ {
public:
	RB_Tree_();
	RB_Tree_(const RB_Tree_ other);
	~RB_Tree_();

private:
	friend class Map;
	friend class Set;
	struct Node {
		Node() {}
		Node(const T& datum, Node* left, Node* right, RB_TREE_COLOR_ color)
			:datum_(datum), left_(left), right_(right), color_(color) {}
		T datum_;
		Node* left_;
		Node* right_;
		RB_TREE_COLOR_ color_;
	};

	void insert_(const T& value);
	void delete_(const T& value);


};

#endif
