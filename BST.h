#ifndef ALGS4_BST_H
#define ALGS4_BST_H


#include "OrderedST.h"
#include <memory>
#include <utility>

template<typename Key, typename Value>
class BST : public OrderedST<Key, Value> {
protected:
    struct Node {
        Key key;
        Value val;
        std::unique_ptr<Node> left, right;
        int N; // number of nodes in subtree rooted here

        Node(const Key &key, const Value &val, int N) : key(key), val(val), N(N) {}
    };

    std::unique_ptr<Node> root;

    std::optional<Value> get(const Node *x, const Key &key) const;

    std::unique_ptr<Node> put(std::unique_ptr<Node> &x, const Key &key, const Value &val);

    std::unique_ptr<Node> remove(std::unique_ptr<Node> &x, const Key &key);

    int size(const Node *x) const;

    const Node *min(const Node *x) const;

    std::unique_ptr<Node> min(std::unique_ptr<Node> &x); // extract the minimum node

    const Node *max(const Node *x) const;

    const Node *floor(const Node *x, const Key &key) const;

    const Node *ceiling(const Node *x, const Key &key) const;

    int rank(const Node *x, const Key &key) const;

    const Node *select(const Node *x, int k) const;

    std::unique_ptr<Node> removeMin(std::unique_ptr<Node> &x);

    std::unique_ptr<Node> removeMax(std::unique_ptr<Node> &x);

    void keys(const Node *x, std::list<Key> &queue, const Key &lo, const Key &hi) const;

public:
    std::optional<Value> get(const Key &key) const override { return get(root.get(), key); }

    void put(const Key &key, const Value &val) override { root = put(root, key, val); }

    void remove(const Key &key) override { root = remove(root, key); }

    int size() const override { return size(root.get()); }

    std::optional<Key> min() const override;

    std::optional<Key> max() const override;

    std::optional<Key> floor(const Key &key) const override;

    std::optional<Key> ceiling(const Key &key) const override;

    int rank(const Key &key) const override { return rank(root.get(), key); }

    std::optional<Key> select(int k) const override { return select(root.get(), k)->key; }

    void removeMin() override { root = removeMin(root); }

    void removeMax() override { root = removeMax(root); }

    using OrderedST<Key, Value>::keys;

    std::list<Key> keys(const Key &lo, const Key &hi) const override;
};

template<typename Key, typename Value>
std::optional<Value> BST<Key, Value>::get(const Node *x, const Key &key) const {
    if (!x) return std::nullopt;
    if (key < x->key) return get(x->left.get(), key);
    else if (key > x->key) return get(x->right.get(), key);
    else return x->val;
}

template<typename Key, typename Value>
std::unique_ptr<typename BST<Key, Value>::Node> BST<Key, Value>::put(std::unique_ptr<Node> &x, const Key &key,
                                                                     const Value &val) {
    if (!x) return std::make_unique<Node>(key, val, 1);
    if (key < x->key) x->left = put(x->left, key, val);
    else if (key > x->key) x->right = put(x->right, key, val);
    else x->val = val;
    x->N = size(x->left.get()) + size(x->right.get()) + 1;
    return std::move(x);
}

template<typename Key, typename Value>
std::unique_ptr<typename BST<Key, Value>::Node> BST<Key, Value>::remove(std::unique_ptr<Node> &x, const Key &key) {
    if (!x) return nullptr;
    if (key < x->key) x->left = remove(x->left, key);
    else if (key > x->key) x->right = remove(x->right, key);
    else {
        if (!x->right) return std::move(x->left);
        if (!x->left) return std::move(x->right);
        auto t = std::move(x);
        x = min(t->right);
        x->right = std::move(t->right);
        x->left = std::move(t->left);
    }
    x->N = size(x->left.get()) + size(x->right.get()) + 1;
    return std::move(x);
}

template<typename Key, typename Value>
int BST<Key, Value>::size(const Node *x) const {
    if (!x) return 0;
    return x->N;
}

template<typename Key, typename Value>
const typename BST<Key, Value>::Node *BST<Key, Value>::min(const Node *x) const {
    if (!x) return nullptr;
    if (!x->left) return x;
    return min(x->left.get());
}

template<typename Key, typename Value>
std::unique_ptr<typename BST<Key, Value>::Node> BST<Key, Value>::min(std::unique_ptr<Node> &x) {
    if (!x) return nullptr;
    if (!x->left) {
        auto min = std::move(x);
        x = std::move(min->right);
        min->right = nullptr;
        return min;
    }
    return min(x->left);
}

template<typename Key, typename Value>
const typename BST<Key, Value>::Node *BST<Key, Value>::max(const Node *x) const {
    if (!x) return nullptr;
    if (!x->right) return x;
    return max(x->right.get());
}

template<typename Key, typename Value>
const typename BST<Key, Value>::Node *BST<Key, Value>::floor(const Node *x, const Key &key) const {
    if (!x) return nullptr;
    if (key < x->key) return floor(x->left.get(), key);
    else if (key == x->key) return x;
    else {
        if (const Node *t = floor(x->right.get(), key)) return t;
        return x;
    }
}

template<typename Key, typename Value>
const typename BST<Key, Value>::Node *BST<Key, Value>::ceiling(const Node *x, const Key &key) const {
    if (!x) return nullptr;
    if (key > x->key) return ceiling(x->right.get(), key);
    else if (key == x->key) return x;
    else {
        if (const Node *t = ceiling(x->left.get(), key)) return t;
        return x;
    }
}

template<typename Key, typename Value>
int BST<Key, Value>::rank(const Node *x, const Key &key) const {
    if (!x) return 0;
    if (key < x->key) return rank(x->left.get(), key);
    else if (key > x->key)
        return size(x->left.get()) /* nodes in left subtree */ + 1 /* root */ + rank(x->right.get(), key);
    else return size(x->left.get());
}

template<typename Key, typename Value>
const typename BST<Key, Value>::Node *BST<Key, Value>::select(const Node *x, int k) const {
    if (!x) return nullptr;
    int t = size(x->left.get());
    if (k < t) return select(x->left.get(), k);
    else if (k > t) return select(x->right.get(), k - t - 1);
    else return x;
}

template<typename Key, typename Value>
std::unique_ptr<typename BST<Key, Value>::Node> BST<Key, Value>::removeMin(std::unique_ptr<Node> &x) {
    if (!x) return nullptr;
    if (!x->left) return std::move(x->right);
    x->left = removeMin(x->left);
    x->N = size(x->left.get()) + size(x->right.get()) + 1;
    return std::move(x);
}

template<typename Key, typename Value>
std::unique_ptr<typename BST<Key, Value>::Node> BST<Key, Value>::removeMax(std::unique_ptr<Node> &x) {
    if (!x) return nullptr;
    if (!x->right) return std::move(x->left);
    x->right = removeMax(x->right);
    x->N = size(x->left.get()) + size(x->right.get()) + 1;
    return std::move(x);
}

template<typename Key, typename Value>
void BST<Key, Value>::keys(const Node *x, std::list<Key> &queue, const Key &lo, const Key &hi) const {
    if (!x) return;
    if (lo < x->key) keys(x->left.get(), queue, lo, hi);
    if (lo <= x->key && hi >= x->key) queue.push_back(x->key);
    if (hi > x->key) keys(x->right.get(), queue, lo, hi);
}

template<typename Key, typename Value>
std::optional<Key> BST<Key, Value>::min() const {
    const Node *x = min(root.get());
    if (!x) return std::nullopt;
    return x->key;
}

template<typename Key, typename Value>
std::optional<Key> BST<Key, Value>::max() const {
    const Node *x = max(root.get());
    if (!x) return std::nullopt;
    return x->key;
}

template<typename Key, typename Value>
std::optional<Key> BST<Key, Value>::floor(const Key &key) const {
    const Node *x = floor(root.get(), key);
    if (!x) return std::nullopt;
    return x->key;
}

template<typename Key, typename Value>
std::optional<Key> BST<Key, Value>::ceiling(const Key &key) const {
    const Node *x = ceiling(root.get(), key);
    if (!x) return std::nullopt;
    return x->key;
}

template<typename Key, typename Value>
std::list<Key> BST<Key, Value>::keys(const Key &lo, const Key &hi) const {
    std::list<Key> queue;
    keys(root.get(), queue, lo, hi);
    return queue;
}


#endif //ALGS4_BST_H
