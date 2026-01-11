#ifndef ALGS4_BSTBASE_HPP
#define ALGS4_BSTBASE_HPP


#include <cassert>
#include <cstddef>
#include <memory>

#include "OrderedST.hpp"

namespace algs4 {
    namespace internal {
        template<std::totally_ordered Key, typename Value, typename Derived>
        struct BSTNodeBase {
            Key key;
            Value val;
            std::unique_ptr<Derived> left, right;
            std::ptrdiff_t N; // number of nodes in subtree rooted here

            BSTNodeBase(const Key &key, const Value &val, std::ptrdiff_t N) : key(key), val(val), N(N) {}
        };
    }

    template<std::totally_ordered Key, typename Value, typename Node>
    class BSTBase : public OrderedST<Key, Value> {
    protected:
        std::unique_ptr<Node> root;

        std::optional<Value> get(const Node *x, const Key &key) const;
        std::ptrdiff_t size(const Node *x) const;
        const Node *min(const Node *x) const;
        const Node *max(const Node *x) const;
        const Node *floor(const Node *x, const Key &key) const;
        const Node *ceiling(const Node *x, const Key &key) const;
        std::ptrdiff_t rank(const Node *x, const Key &key) const;
        const Node *select(const Node *x, std::ptrdiff_t k) const;
        void keys(const Node *x, std::list<Key> &queue, const Key &lo, const Key &hi) const;

    public:
        std::optional<Value> get(const Key &key) const override { return get(root.get(), key); }
        std::ptrdiff_t size() const override { return size(root.get()); }
        std::optional<Key> min() const override;
        std::optional<Key> max() const override;
        std::optional<Key> floor(const Key &key) const override;
        std::optional<Key> ceiling(const Key &key) const override;
        std::ptrdiff_t rank(const Key &key) const override { return rank(root.get(), key); }
        Key select(std::ptrdiff_t k) const override;
        using OrderedST<Key, Value>::keys;
        std::list<Key> keys(const Key &lo, const Key &hi) const override;
    };
}

template<std::totally_ordered Key, typename Value, typename Node>
std::optional<Value> algs4::BSTBase<Key, Value, Node>::get(const Node *x, const Key &key) const {
    if (!x) return std::nullopt;
    if (key < x->key) return get(x->left.get(), key);
    else if (key > x->key) return get(x->right.get(), key);
    else return x->val;
}

template<std::totally_ordered Key, typename Value, typename Node>
std::ptrdiff_t algs4::BSTBase<Key, Value, Node>::size(const Node *x) const {
    if (!x) return 0;
    return x->N;
}

template<std::totally_ordered Key, typename Value, typename Node>
const Node *algs4::BSTBase<Key, Value, Node>::min(const Node *x) const {
    if (!x->left) return x;
    return min(x->left.get());
}

template<std::totally_ordered Key, typename Value, typename Node>
const Node *algs4::BSTBase<Key, Value, Node>::max(const Node *x) const {
    if (!x->right) return x;
    return max(x->right.get());
}

template<std::totally_ordered Key, typename Value, typename Node>
const Node *algs4::BSTBase<Key, Value, Node>::floor(const Node *x, const Key &key) const {
    if (!x) return nullptr;
    if (key == x->key) return x;
    if (key < x->key) return floor(x->left.get(), key);
    if (const Node *t = floor(x->right.get(), key)) return t;
    else return x;
}

template<std::totally_ordered Key, typename Value, typename Node>
const Node *algs4::BSTBase<Key, Value, Node>::ceiling(const Node *x, const Key &key) const {
    if (!x) return nullptr;
    if (key == x->key) return x;
    if (key > x->key) return ceiling(x->right.get(), key);
    if (const Node *t = ceiling(x->left.get(), key)) return t;
    else return x;
}

template<std::totally_ordered Key, typename Value, typename Node>
std::ptrdiff_t algs4::BSTBase<Key, Value, Node>::rank(const Node *x, const Key &key) const {
    if (!x) return 0;
    if (key < x->key) return rank(x->left.get(), key);
    else if (key > x->key)
        return size(x->left.get()) /* nodes in left subtree */ + 1 /* root */ + rank(x->right.get(), key);
    else return size(x->left.get());
}

template<std::totally_ordered Key, typename Value, typename Node>
const Node *algs4::BSTBase<Key, Value, Node>::select(const Node *x, std::ptrdiff_t k) const {
    if (!x) return nullptr;
    if (auto t = size(x->left.get()); t > k) return select(x->left.get(), k);
    else if (t < k) return select(x->right.get(), k - t - 1);
    else return x;
}

template<std::totally_ordered Key, typename Value, typename Node>
void algs4::BSTBase<Key, Value, Node>::keys(const Node *x, std::list<Key> &queue, const Key &lo, const Key &hi) const {
    if (!x) return;
    if (lo < x->key) keys(x->left.get(), queue, lo, hi);
    if (lo <= x->key && hi >= x->key) queue.push_back(x->key);
    if (hi > x->key) keys(x->right.get(), queue, lo, hi);
}

template<std::totally_ordered Key, typename Value, typename Node>
std::optional<Key> algs4::BSTBase<Key, Value, Node>::min() const {
    if (this->isEmpty()) return std::nullopt;
    const Node *x = min(root.get());
    if (!x) return std::nullopt;
    return x->key;
}

template<std::totally_ordered Key, typename Value, typename Node>
std::optional<Key> algs4::BSTBase<Key, Value, Node>::max() const {
    if (this->isEmpty()) return std::nullopt;
    const Node *x = max(root.get());
    if (!x) return std::nullopt;
    return x->key;
}

template<std::totally_ordered Key, typename Value, typename Node>
std::optional<Key> algs4::BSTBase<Key, Value, Node>::floor(const Key &key) const {
    if (this->isEmpty()) return std::nullopt;
    const Node *x = floor(root.get(), key);
    if (!x) return std::nullopt;
    return x->key;
}

template<std::totally_ordered Key, typename Value, typename Node>
std::optional<Key> algs4::BSTBase<Key, Value, Node>::ceiling(const Key &key) const {
    if (this->isEmpty()) return std::nullopt;
    const Node *x = ceiling(root.get(), key);
    if (!x) return std::nullopt;
    return x->key;
}

template<std::totally_ordered Key, typename Value, typename Node>
Key algs4::BSTBase<Key, Value, Node>::select(std::ptrdiff_t k) const {
    assert(k < size());
    return select(root.get(), k)->key;
}

template<std::totally_ordered Key, typename Value, typename Node>
std::list<Key> algs4::BSTBase<Key, Value, Node>::keys(const Key &lo, const Key &hi) const {
    std::list<Key> queue;
    keys(root.get(), queue, lo, hi);
    return queue;
}


#endif //ALGS4_BSTBASE_HPP
