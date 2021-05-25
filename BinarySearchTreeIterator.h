
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

		const BNode<T>* current = aBNodeTree;
		
		while (current->key != 0 || fStack.size() > 0)
		{
			while (current->key != 0)
			{
				fStack.push(current);
				current = current->left;
			}

			current = fStack.top();
			fStack.pop();

			std::cout << current->key << " ";

			current = current->right;
		}
	}

	const T& operator*() const
	{
		return fBNodeTree->key;
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
		return Iterator(fBNodeTree);
	}

	Iterator end() const
	{
		return Iterator(&BNode<T>::NIL);
	}
};
