#ifndef ALGS4_BST_H
#define ALGS4_BST_H


#include "OrderedST.h"
#include <memory>

template<typename Key, typename Value>
class BST : public OrderedST<Key, Value> {
private:
    struct Node {
        Key key;
        Value val;
        std::shared_ptr<Node> left, right;
        int N;  // 以该结点为根的子树中的结点总数

        Node(Key key, Value val, int N) :
                key(key), val(val), left(nullptr), right(nullptr), N(N) {}
    };

    std::shared_ptr<Node> root = nullptr;

    Value get(std::shared_ptr<Node> x, const Key &key) const {
        if (x == nullptr) return Value();
        if (key < x->key) return get(x->left, key);
        else if (key > x->key) return get(x->right, key);
        else return x->val;
    }

    std::shared_ptr<Node> put(std::shared_ptr<Node> x, const Key &key, const Value &val) {
        if (x == nullptr) return std::make_shared<Node>(key, val, 1);
        if (key < x->key) x->left = put(x->left, key, val);
        else if (key > x->key) x->right = put(x->right, key, val);
        else x->val = val;
        x->N = size(x->left) + size(x->right) + 1;
        return x;
    }

    std::shared_ptr<Node> remove(std::shared_ptr<Node> x, const Key &key) {
        if (x == nullptr) return nullptr;
        if (key < x->key) x->left = remove(x->left, key);
        else if (key > x->key) x->right = remove(x->right, key);
        else {
            if (x->right == nullptr) return x->left;
            if (x->left == nullptr) return x->right;
            std::shared_ptr<Node> t = x;
            x = min(t->right);
            x->right = removeMin(t->right);
            x->left = t->left;
        }
        x->N = size(x->left) + size(x->right) + 1;
        return x;
    }

    int size(std::shared_ptr<Node> x) const {
        if (x == nullptr) return 0;
        return x->N;
    }

    std::shared_ptr<Node> min(std::shared_ptr<Node> x) const {
        if (x->left == nullptr) return x;
        return min(x->left);
    }

    std::shared_ptr<Node> max(std::shared_ptr<Node> x) const {
        if (x->right == nullptr) return x;
        return max(x->right);
    }

    std::shared_ptr<Node> floor(std::shared_ptr<Node> x, const Key &key) const {
        if (x == nullptr) return nullptr;
        if (key < x->key) return floor(x->left, key);
        else if (key == x->key) return x;
        else {
            std::shared_ptr<Node> t = floor(x->right, key);
            if (t == nullptr) return x;
            return t;
        }
    }

    std::shared_ptr<Node> ceiling(std::shared_ptr<Node> x, const Key &key) const {
        if (x == nullptr) return nullptr;
        if (key > x->key) return ceiling(x->right, key);
        else if (key == x->key) return x;
        else {
            std::shared_ptr<Node> t = ceiling(x->left, key);
            if (t == nullptr) return x;
            return t;
        }
    }

    int rank(std::shared_ptr<Node> x, const Key &key) const {
        if (x == nullptr) return 0;
        if (key < x->key) return rank(x->left, key);
        else if (key > x->key)
            return size(x->left) /* 左子树的结点总数 */ + 1 /* 根结点 */ + rank(x->right, key);
        else return size(x->left);
    }

    std::shared_ptr<Node> select(std::shared_ptr<Node> x, int k) const {
        if (x == nullptr) return nullptr;
        int t = size(x->left);
        if (k < t) return select(x->left, k);
        else if (k > t) return select(x->right, k - t - 1);
        else return x;
    }

    std::shared_ptr<Node> removeMin(std::shared_ptr<Node> x) {
        if (x->left == nullptr) return x->right;
        x->left = removeMin(x->left);
        x->N = size(x->left) + size(x->right) + 1;
        return x;
    }

    std::shared_ptr<Node> removeMax(std::shared_ptr<Node> x) {
        if (x->right == nullptr) return x->left;
        x->right = removeMax(x->right);
        x->N = size(x->left) + size(x->right) + 1;
        return x;
    }

    void getKeys(std::shared_ptr<Node> x, std::deque<Key> &queue, const Key &lo, const Key &hi) const {
        if (x == nullptr) return;
        if (lo < x->key) getKeys(x->left, queue, lo, hi);
        if (lo <= x->key && hi >= x->key) queue.push_back(x->key);
        if (hi > x->key) getKeys(x->right, queue, lo, hi);
    }

public:
    Value get(const Key &key) const override {
        return get(root, key);
    }

    void put(const Key &key, const Value &val) override {
        root = put(root, key, val);
    }

    void remove(const Key &key) override {
        root = remove(root, key);
    }

    int size() const override {
        return size(root);
    }

    Key min() const override {
        if (this->isEmpty()) return Key();
        return min(root)->key;
    }

    Key max() const override {
        if (this->isEmpty()) return Key();
        return max(root)->key;
    }

    Key floor(const Key &key) const override {
        std::shared_ptr<Node> x = floor(root, key);
        if (x == nullptr) return Key();
        return x->key;
    }

    Key ceiling(const Key &key) const override {
        std::shared_ptr<Node> x = ceiling(root, key);
        if (x == nullptr) return Key();
        return x->key;
    }

    int rank(const Key &key) const override {
        return rank(root, key);
    }

    Key select(int k) const override {
        if (this->isEmpty()) return Key();
        return select(root, k)->key;
    }

    void removeMin() override {
        if (this->isEmpty()) return;
        removeMin(root);
    }

    void removeMax() override {
        if (this->isEmpty()) return;
        removeMax(root);
    }

    std::deque<Key> getKeys() const override {
        return getKeys(min(), max());
    }

    std::deque<Key> getKeys(const Key &lo, const Key &hi) const override {
        std::deque<Key> queue;
        getKeys(root, queue, lo, hi);
        return queue;
    }
};


#endif //ALGS4_BST_H
