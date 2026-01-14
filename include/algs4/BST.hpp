#ifndef ALGS4_BST_HPP
#define ALGS4_BST_HPP


#include "BSTBase.hpp"

namespace algs4 {
    namespace internal {
        template<std::totally_ordered Key, typename Value>
        struct BSTNode : public BSTNodeBase<Key, Value, BSTNode<Key, Value> > {
            BSTNode(Key key, Value val, std::ptrdiff_t N)
                : BSTNodeBase<Key, Value, BSTNode>(std::move(key), std::move(val), N) {}
        };
    }

    template<std::totally_ordered Key, typename Value>
    class BST : public BSTBase<Key, Value, internal::BSTNode<Key, Value> > {
    private:
        using Node = internal::BSTNode<Key, Value>;

        std::unique_ptr<Node> put(std::unique_ptr<Node> x, Key key, Value val);
        std::unique_ptr<Node> extractMin(std::unique_ptr<Node> &x);
        std::unique_ptr<Node> remove(std::unique_ptr<Node> x, const Key &key);
        std::unique_ptr<Node> removeMin(std::unique_ptr<Node> x);
        std::unique_ptr<Node> removeMax(std::unique_ptr<Node> x);

    public:
        void put(Key key, Value val) override { this->root = put(std::move(this->root), key, val); }
        void remove(const Key &key) override { this->root = remove(std::move(this->root), key); }
        void removeMin() override { this->root = removeMin(std::move(this->root)); }
        void removeMax() override { this->root = removeMax(std::move(this->root)); }
    };
}

template<std::totally_ordered Key, typename Value>
auto algs4::BST<Key, Value>::put(std::unique_ptr<Node> x, Key key, Value val) -> std::unique_ptr<Node> {
    if (!x) return std::make_unique<Node>(std::move(key), std::move(val), 1);
    if (key < x->key) x->left = put(std::move(x->left), std::move(key), std::move(val));
    else if (key > x->key) x->right = put(std::move(x->right), std::move(key), std::move(val));
    else x->val = std::move(val);
    x->N = this->size(x->left.get()) + this->size(x->right.get()) + 1;
    return x;
}

template<std::totally_ordered Key, typename Value>
auto algs4::BST<Key, Value>::extractMin(std::unique_ptr<Node> &x) -> std::unique_ptr<Node> {
    if (!x) return nullptr;
    if (!x->left) {
        auto min = std::move(x);
        x = std::move(min->right);
        min->right = nullptr;
        return min;
    }
    auto min = extractMin(x->left);
    x->N = this->size(x->left.get()) + this->size(x->right.get()) + 1;
    return min;
}

template<std::totally_ordered Key, typename Value>
auto algs4::BST<Key, Value>::remove(std::unique_ptr<Node> x, const Key &key) -> std::unique_ptr<Node> {
    if (!x) return nullptr;
    if (key < x->key) x->left = remove(std::move(x->left), key);
    else if (key > x->key) x->right = remove(std::move(x->right), key);
    else {
        if (!x->right) return std::move(x->left);
        if (!x->left) return std::move(x->right);
        auto t = std::move(x);
        x = extractMin(t->right);
        x->right = std::move(t->right);
        x->left = std::move(t->left);
    }
    x->N = this->size(x->left.get()) + this->size(x->right.get()) + 1;
    return x;
}

template<std::totally_ordered Key, typename Value>
auto algs4::BST<Key, Value>::removeMin(std::unique_ptr<Node> x) -> std::unique_ptr<Node> {
    if (!x) return nullptr;
    if (!x->left) return std::move(x->right);
    x->left = removeMin(std::move(x->left));
    x->N = this->size(x->left.get()) + this->size(x->right.get()) + 1;
    return x;
}

template<std::totally_ordered Key, typename Value>
auto algs4::BST<Key, Value>::removeMax(std::unique_ptr<Node> x) -> std::unique_ptr<Node> {
    if (!x) return nullptr;
    if (!x->right) return std::move(x->left);
    x->right = removeMax(std::move(x->right));
    x->N = this->size(x->left.get()) + this->size(x->right.get()) + 1;
    return x;
}


#endif //ALGS4_BST_HPP
