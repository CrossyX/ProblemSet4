
// COS30008, Problem Set 4, 2021

#pragma once

#include <stack>

#include "BNode.h"

template<typename T>
class BinarySearchTreeIterator
{
private:
	const BNode<T>* fBNodeTree;				// binary search tree
	std::stack<const BNode<T>*> fStack;		// DFS traversal stack

public:

	using Iterator = BinarySearchTreeIterator<T>;

	BinarySearchTreeIterator(const BNode<T>* aBNodeTree)
	{
		fBNodeTree = aBNodeTree;
		fStack = std::stack<const BNode<T>*>();
	}

	const T& operator*() const
	{
		const BNode<T>* node = fStack.top();
		const T& key = fBNodeTree->key;
		return node->key;
		//return fBNodeTree->key;
	}

	Iterator& operator++()
	{
		fStack.pop();

		return *this;
	}

	Iterator operator++(int)
	{
		Iterator temp = *this;

		++(*this);

		return temp;
	}

	bool operator==(const Iterator& aOtherIter) const
	{
		return fStack.size() == aOtherIter.fStack.size();
	}

	bool operator!=(const Iterator& aOtherIter) const
	{
		return !(*this == aOtherIter);
	}

	Iterator begin() const
	{
		Iterator iterator = Iterator(*this);
		std::cout << iterator.fBNodeTree->key << endl;
		return Iterator(*this);
	}

	Iterator end() const
	{
		fStack.empty();
		return Iterator(&BNode<T>::NIL);
	}
};
