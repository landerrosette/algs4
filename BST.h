#ifndef ALGS4_BST_H
#define ALGS4_BST_H


#include "OrderedST.h"
#include <memory>

template<typename Key, typename Value>
class BST : public OrderedST<Key, Value> {
protected:
    struct Node {
        Key key;
        Value val;
        std::shared_ptr<Node> left, right;
        int N; // 以该结点为根的子树中的结点总数

        Node(Key key, Value val, int N) : key(key), val(val), N(N) {}

        virtual ~Node() = default;
    };

    std::shared_ptr<Node> root;

    std::optional<Value> get(std::shared_ptr<Node> x, const Key &key) const;

    std::shared_ptr<Node> put(std::shared_ptr<Node> x, const Key &key, const Value &val);

    std::shared_ptr<Node> remove(std::shared_ptr<Node> x, const Key &key);

    int size(std::shared_ptr<Node> x) const;

    std::shared_ptr<Node> min(std::shared_ptr<Node> x) const;

    std::shared_ptr<Node> max(std::shared_ptr<Node> x) const;

    std::shared_ptr<Node> floor(std::shared_ptr<Node> x, const Key &key) const;

    std::shared_ptr<Node> ceiling(std::shared_ptr<Node> x, const Key &key) const;

    int rank(std::shared_ptr<Node> x, const Key &key) const;

    std::shared_ptr<Node> select(std::shared_ptr<Node> x, int k) const;

    std::shared_ptr<Node> removeMin(std::shared_ptr<Node> x);

    std::shared_ptr<Node> removeMax(std::shared_ptr<Node> x);

    void keys(std::shared_ptr<Node> x, std::list<Key> &queue, const Key &lo, const Key &hi) const;

public:
    std::optional<Value> get(const Key &key) const override { return get(root, key); }

    void put(const Key &key, const Value &val) override { root = put(root, key, val); }

    void remove(const Key &key) override { root = remove(root, key); }

    int size() const override { return size(root); }

    std::optional<Key> min() const override;

    std::optional<Key> max() const override;

    std::optional<Key> floor(const Key &key) const override;

    std::optional<Key> ceiling(const Key &key) const override;

    int rank(const Key &key) const override { return rank(root, key); }

    std::optional<Key> select(int k) const override { return select(root, k)->key; }

    void removeMin() override { root = removeMin(root); }

    void removeMax() override { root = removeMax(root); }

    using OrderedST<Key, Value>::keys;

    std::list<Key> keys(const Key &lo, const Key &hi) const override;
};

template<typename Key, typename Value>
std::optional<Value> BST<Key, Value>::get(std::shared_ptr<Node> x, const Key &key) const {
    if (!x) return std::nullopt;
    if (key < x->key) return get(x->left, key);
    else if (key > x->key) return get(x->right, key);
    else return x->val;
}

template<typename Key, typename Value>
std::shared_ptr<typename BST<Key, Value>::Node>
BST<Key, Value>::put(std::shared_ptr<Node> x, const Key &key, const Value &val) {
    if (!x) return std::make_shared<Node>(key, val, 1);
    if (key < x->key) x->left = put(x->left, key, val);
    else if (key > x->key) x->right = put(x->right, key, val);
    else x->val = val;
    x->N = size(x->left) + size(x->right) + 1;
    return x;
}

template<typename Key, typename Value>
std::shared_ptr<typename BST<Key, Value>::Node> BST<Key, Value>::remove(std::shared_ptr<Node> x, const Key &key) {
    if (!x) return nullptr;
    if (key < x->key) x->left = remove(x->left, key);
    else if (key > x->key) x->right = remove(x->right, key);
    else {
        if (!x->right) return x->left;
        if (!x->left) return x->right;
        auto t = x;
        x = min(t->right);
        x->right = removeMin(t->right);
        x->left = t->left;
    }
    x->N = size(x->left) + size(x->right) + 1;
    return x;
}

template<typename Key, typename Value>
int BST<Key, Value>::size(std::shared_ptr<Node> x) const {
    if (!x) return 0;
    return x->N;
}

template<typename Key, typename Value>
std::shared_ptr<typename BST<Key, Value>::Node> BST<Key, Value>::min(std::shared_ptr<Node> x) const {
    if (!x) return nullptr;
    if (!x->left) return x;
    return min(x->left);
}

template<typename Key, typename Value>
std::shared_ptr<typename BST<Key, Value>::Node> BST<Key, Value>::max(std::shared_ptr<Node> x) const {
    if (!x) return nullptr;
    if (!x->right) return x;
    return max(x->right);
}

template<typename Key, typename Value>
std::shared_ptr<typename BST<Key, Value>::Node> BST<Key, Value>::floor(std::shared_ptr<Node> x, const Key &key) const {
    if (!x) return nullptr;
    if (key < x->key) return floor(x->left, key);
    else if (key == x->key) return x;
    else {
        auto t = floor(x->right, key);
        if (t) return t;
        return x;
    }
}

template<typename Key, typename Value>
std::shared_ptr<typename BST<Key, Value>::Node>
BST<Key, Value>::ceiling(std::shared_ptr<Node> x, const Key &key) const {
    if (!x) return nullptr;
    if (key > x->key) return ceiling(x->right, key);
    else if (key == x->key) return x;
    else {
        auto t = ceiling(x->left, key);
        if (t) return t;
        return x;
    }
}

template<typename Key, typename Value>
int BST<Key, Value>::rank(std::shared_ptr<Node> x, const Key &key) const {
    if (!x) return 0;
    if (key < x->key) return rank(x->left, key);
    else if (key > x->key)
        return size(x->left) /* 左子树的结点总数 */ + 1 /* 根结点 */ + rank(x->right, key);
    else return size(x->left);
}

template<typename Key, typename Value>
std::shared_ptr<typename BST<Key, Value>::Node> BST<Key, Value>::select(std::shared_ptr<Node> x, int k) const {
    if (!x) return nullptr;
    int t = size(x->left);
    if (k < t) return select(x->left, k);
    else if (k > t) return select(x->right, k - t - 1);
    else return x;
}

template<typename Key, typename Value>
std::shared_ptr<typename BST<Key, Value>::Node> BST<Key, Value>::removeMin(std::shared_ptr<Node> x) {
    if (!x) return nullptr;
    if (!x->left) return x->right;
    x->left = removeMin(x->left);
    x->N = size(x->left) + size(x->right) + 1;
    return x;
}

template<typename Key, typename Value>
std::shared_ptr<typename BST<Key, Value>::Node> BST<Key, Value>::removeMax(std::shared_ptr<Node> x) {
    if (!x) return nullptr;
    if (!x->right) return x->left;
    x->right = removeMax(x->right);
    x->N = size(x->left) + size(x->right) + 1;
    return x;
}

template<typename Key, typename Value>
void BST<Key, Value>::keys(std::shared_ptr<Node> x, std::list<Key> &queue, const Key &lo, const Key &hi) const {
    if (!x) return;
    if (lo < x->key) keys(x->left, queue, lo, hi);
    if (lo <= x->key && hi >= x->key) queue.push_back(x->key);
    if (hi > x->key) keys(x->right, queue, lo, hi);
}

template<typename Key, typename Value>
std::optional<Key> BST<Key, Value>::min() const {
    auto x = min(root);
    if (!x) return std::nullopt;
    return x->key;
}

template<typename Key, typename Value>
std::optional<Key> BST<Key, Value>::max() const {
    auto x = max(root);
    if (!x) return std::nullopt;
    return x->key;
}

template<typename Key, typename Value>
std::optional<Key> BST<Key, Value>::floor(const Key &key) const {
    auto x = floor(root, key);
    if (!x) return std::nullopt;
    return x->key;
}

template<typename Key, typename Value>
std::optional<Key> BST<Key, Value>::ceiling(const Key &key) const {
    auto x = ceiling(root, key);
    if (!x) return std::nullopt;
    return x->key;
}

template<typename Key, typename Value>
std::list<Key> BST<Key, Value>::keys(const Key &lo, const Key &hi) const {
    std::list<Key> queue;
    keys(root, queue, lo, hi);
    return queue;
}


#endif //ALGS4_BST_H
