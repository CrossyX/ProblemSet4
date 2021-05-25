
// COS30008, Problem Set 4, 2021

#pragma once

#include <stdexcept>

template<typename S>
struct BNode
{
    S key;
    BNode<S>* left;
    BNode<S>* right;

    static BNode<S> NIL;

    const S& findMax() const
    {
        if (empty())
        {
            throw std::domain_error("Empty tree encountered.");
        }

        return right->empty() ? key : right->findMax();
    }

    const S& findMin() const
    {
        if (empty())
        {
            throw std::domain_error("Empty tree encountered.");
        }

        return left->empty() ? key : left->findMin();
    }

    bool remove(const S& aKey, BNode<S>* aParent)
    {
        BNode<S>* x = this;
        BNode<S>* y = aParent;

        while (!x->empty())
        {
            if (aKey == x->key)
            {
                break;
            }

            y = x;                                      // new parent

            x = aKey < x->key ? x->left : x->right;
        }

        if (x->empty())
        {
            return false;                               // delete failed
        }

        if (!x->left->empty())
        {
            const S& lKey = x->left->findMax();         // find max to left
            x->key = lKey;
            x->left->remove(lKey, x);
        }
        else
        {
            if (!x->right->empty())
            {
                const S& lKey = x->right->findMin();    // find min to right
                x->key = lKey;
                x->right->remove(lKey, x);
            }
            else
            {
                if (y->left == x)
                {
                    y->left = &NIL;
                }
                else
                {
                    y->right = &NIL;
                }

                delete x;                               // free deleted node
            }
        }

        return true;
    }

    // PS4 starts here

    BNode() :
        key(S()),
        left(&NIL),
        right(&NIL)
    {}

    BNode(const S& aKey) :
        key(aKey),
        left(&NIL),
        right(&NIL)
    {}

    BNode(S&& aKey) :
        key(std::move(aKey)),
        left(&NIL),
        right(&NIL)
    {}

    ~BNode()
    {
        if (left != &NIL)
        {
            delete left;
        }

        if (right != &NIL)
        {
            delete right;
        }
    }

    bool empty() const
    {
        return this == &NIL;
    }

    bool leaf() const
    {
        return (this->left == &NIL) && (this->right == &NIL);
    }

    size_t height() const
    {
        /*if this is leaf :
            return 0
        else:
            if height of left > height of right :
                return height of left + 1
            else :
                return height of right + 1*/


        if (this->leaf())
        {
            return 0;
        }
        else
        {
            int left_side = left->height();
            int right_side = right->height();
            if (left_side > right_side)
            {
                return left_side + 1;
            }
            else
            {
                return right_side + 1;
            }
        }
    }

    bool insert(const S& aKey)
    {
        BNode<S>* x = this;
        BNode<S>* y = &BNode<S>::NIL;

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
            BNode<S>* z = new BNode<S>(aKey);

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
};

template<typename S>
BNode<S> BNode<S>::NIL;
