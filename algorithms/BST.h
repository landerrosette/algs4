#ifndef ALGS4_BST_H
#define ALGS4_BST_H


#include "BSTBase.h"

namespace algs4 {
    namespace internal {
        template<typename Key, typename Value>
        struct BSTNode : public BSTNodeBase<Key, Value, BSTNode<Key, Value> > {
            using BSTNodeBase<Key, Value, BSTNode>::BSTNodeBase;
        };
    }

    template<typename Key, typename Value>
    class BST : public BSTBase<Key, Value, internal::BSTNode<Key, Value> > {
    private:
        using Node = internal::BSTNode<Key, Value>;

        std::unique_ptr<Node> put(std::unique_ptr<Node> &x, const Key &key, const Value &val);
        std::unique_ptr<Node> extractMin(std::unique_ptr<Node> &x);
        std::unique_ptr<Node> remove(std::unique_ptr<Node> &x, const Key &key);
        std::unique_ptr<Node> removeMin(std::unique_ptr<Node> &x);
        std::unique_ptr<Node> removeMax(std::unique_ptr<Node> &x);

    public:
        void put(const Key &key, const Value &val) override { this->root = put(this->root, key, val); }
        void remove(const Key &key) override { this->root = remove(this->root, key); }
        void removeMin() override { this->root = removeMin(this->root); }
        void removeMax() override { this->root = removeMax(this->root); }
    };
}

template<typename Key, typename Value>
auto algs4::BST<Key, Value>::put(std::unique_ptr<Node> &x, const Key &key, const Value &val) -> std::unique_ptr<Node> {
    if (!x)
        return std::make_unique<Node>(key, val, 1);
    if (key < x->key)
        x->left = put(x->left, key, val);
    else if (key > x->key)
        x->right = put(x->right, key, val);
    else
        x->val = val;
    x->N = this->size(x->left.get()) + this->size(x->right.get()) + 1;
    return std::move(x);
}

template<typename Key, typename Value>
auto algs4::BST<Key, Value>::extractMin(std::unique_ptr<Node> &x) -> std::unique_ptr<Node> {
    if (!x)
        return nullptr;
    if (!x->left) {
        auto min = std::move(x);
        x = std::move(min->right);
        min->right = nullptr;
        return min;
    }
    return extractMin(x->left);
}

template<typename Key, typename Value>
auto algs4::BST<Key, Value>::remove(std::unique_ptr<Node> &x, const Key &key) -> std::unique_ptr<Node> {
    if (!x)
        return nullptr;
    if (key < x->key)
        x->left = remove(x->left, key);
    else if (key > x->key)
        x->right = remove(x->right, key);
    else {
        if (!x->right)
            return std::move(x->left);
        if (!x->left)
            return std::move(x->right);
        auto t = std::move(x);
        x = extractMin(t->right);
        x->right = std::move(t->right);
        x->left = std::move(t->left);
    }
    x->N = this->size(x->left.get()) + this->size(x->right.get()) + 1;
    return std::move(x);
}

template<typename Key, typename Value>
auto algs4::BST<Key, Value>::removeMin(std::unique_ptr<Node> &x) -> std::unique_ptr<Node> {
    if (!x)
        return nullptr;
    if (!x->left)
        return std::move(x->right);
    x->left = removeMin(x->left);
    x->N = this->size(x->left.get()) + this->size(x->right.get()) + 1;
    return std::move(x);
}

template<typename Key, typename Value>
auto algs4::BST<Key, Value>::removeMax(std::unique_ptr<Node> &x) -> std::unique_ptr<Node> {
    if (!x)
        return nullptr;
    if (!x->right)
        return std::move(x->left);
    x->right = removeMax(x->right);
    x->N = this->size(x->left.get()) + this->size(x->right.get()) + 1;
    return std::move(x);
}


#endif //ALGS4_BST_H
