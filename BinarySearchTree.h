
// COS30008, Problem Set 4, 2021

#pragma once

#include "BNode.h"

template<typename T>
class BinarySearchTreeIterator;

template<typename T>
class BinarySearchTree
{
private:
	BNode<T>* fRoot;

public:

	using Iterator = BinarySearchTreeIterator<T>;

	BinarySearchTree() :
		fRoot(&BNode<T>::NIL)
	{}

	~BinarySearchTree()
	{
		if (fRoot->left != &BNode<T>::NIL)
		{
			delete fRoot->left;
		}

		if (fRoot->right != &BNode<T>::NIL)
		{
			delete fRoot->right;
		}
	}

	bool empty() const
	{
		return this == &BNode<T>::NIL;
	}

	bool insert(const T& aKey)
	{
		if (fRoot == &BNode<T>::NIL)
		{
			fRoot = new BNode<T>(aKey);
			return true;
		}

		BNode<T>* x = fRoot;
		BNode<T>* y = &BNode<T>::NIL;

		while (!x->empty())
		{
			y = x;

			if (aKey == x->key)
			{
				return false;
			}

			x = aKey < x->key ? x->left : x->right;
		}

		if (y->empty())
		{
			return false;
		}
		else
		{
			BNode<T>* z = new BNode<T>(aKey);

			if (aKey < y->key)
			{
				y->left = z;
			}
			else
			{
				y->right = z;
			}
		}

		return true;
	}

	bool remove(const T& aKey)
	{
		return fRoot->remove(aKey, &BNode<T>::NIL);
	}

	size_t height() const
	{

		return fRoot->height();
	}

	Iterator begin() const
	{
		return Iterator(fRoot).begin();
	}

	Iterator end() const
	{
		return Iterator(fRoot).end();
	}
};
