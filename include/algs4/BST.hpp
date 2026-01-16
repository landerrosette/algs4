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
        void put(Key key, Value val) override { this->root_ = put(std::move(this->root_), key, val); }
        void remove(const Key &key) override { this->root_ = remove(std::move(this->root_), key); }
        void removeMin() override { this->root_ = removeMin(std::move(this->root_)); }
        void removeMax() override { this->root_ = removeMax(std::move(this->root_)); }
    };
}

template<std::totally_ordered Key, typename Value>
auto algs4::BST<Key, Value>::put(std::unique_ptr<Node> x, Key key, Value val) -> std::unique_ptr<Node> {
    if (!x) return std::make_unique<Node>(std::move(key), std::move(val), 1);
    if (key < x->key_) x->left_ = put(std::move(x->left_), std::move(key), std::move(val));
    else if (key > x->key_) x->right_ = put(std::move(x->right_), std::move(key), std::move(val));
    else x->val_ = std::move(val);
    x->N_ = this->size(x->left_.get()) + this->size(x->right_.get()) + 1;
    return x;
}

template<std::totally_ordered Key, typename Value>
auto algs4::BST<Key, Value>::extractMin(std::unique_ptr<Node> &x) -> std::unique_ptr<Node> {
    if (!x) return nullptr;
    if (!x->left_) {
        auto min = std::move(x);
        x = std::move(min->right_);
        min->right_ = nullptr;
        return min;
    }
    auto min = extractMin(x->left_);
    x->N_ = this->size(x->left_.get()) + this->size(x->right_.get()) + 1;
    return min;
}

template<std::totally_ordered Key, typename Value>
auto algs4::BST<Key, Value>::remove(std::unique_ptr<Node> x, const Key &key) -> std::unique_ptr<Node> {
    if (!x) return nullptr;
    if (key < x->key_) x->left_ = remove(std::move(x->left_), key);
    else if (key > x->key_) x->right_ = remove(std::move(x->right_), key);
    else {
        if (!x->right_) return std::move(x->left_);
        if (!x->left_) return std::move(x->right_);
        auto t = std::move(x);
        x = extractMin(t->right_);
        x->right_ = std::move(t->right_);
        x->left_ = std::move(t->left_);
    }
    x->N_ = this->size(x->left_.get()) + this->size(x->right_.get()) + 1;
    return x;
}

template<std::totally_ordered Key, typename Value>
auto algs4::BST<Key, Value>::removeMin(std::unique_ptr<Node> x) -> std::unique_ptr<Node> {
    if (!x) return nullptr;
    if (!x->left_) return std::move(x->right_);
    x->left_ = removeMin(std::move(x->left_));
    x->N_ = this->size(x->left_.get()) + this->size(x->right_.get()) + 1;
    return x;
}

template<std::totally_ordered Key, typename Value>
auto algs4::BST<Key, Value>::removeMax(std::unique_ptr<Node> x) -> std::unique_ptr<Node> {
    if (!x) return nullptr;
    if (!x->right_) return std::move(x->left_);
    x->right_ = removeMax(std::move(x->right_));
    x->N_ = this->size(x->left_.get()) + this->size(x->right_.get()) + 1;
    return x;
}


#endif //ALGS4_BST_HPP
