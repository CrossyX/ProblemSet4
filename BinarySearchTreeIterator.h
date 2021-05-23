
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
		return fBNodeTree->key;
	}

	Iterator& operator++()
	{
		const BNode<T>* top = fStack.top();
		
		if (fBNodeTree->key != top->key)
		{
			fStack.push(fBNodeTree);
		}

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
		return
			fBNodeTree == aOtherIter.fBNodeTree &&
			fStack == aOtherIter.fStack;
	}

	bool operator!=(const Iterator& aOtherIter) const
	{
		return !(*this == aOtherIter);
	}

	Iterator begin() const
	{
		return fStack.top();
	}

	Iterator end() const
	{
		Iterator iter = *this;

		iter.fBNodeTree = nullptr;
		iter.fStack.empty();

		return iter;
	}
};
