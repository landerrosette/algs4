#ifndef ALGS4_SEQUENTIALSEARCHST_H
#define ALGS4_SEQUENTIALSEARCHST_H


#include <memory>
#include <utility>

#include "ST.h"

namespace algs4 {
    template<typename Key, typename Value>
    class SequentialSearchST : public ST<Key, Value> {
    private:
        struct Node {
            Key key;
            Value val;
            std::unique_ptr<Node> next;

            Node(const Key &key, const Value &val, std::unique_ptr<Node> next)
                : key(key), val(val), next(std::move(next)) {}
        };

        int N = 0;
        std::unique_ptr<Node> first;

        std::unique_ptr<Node> remove(std::unique_ptr<Node> &x, const Key &key);

    public:
        std::optional<Value> get(const Key &key) const override;
        void put(const Key &key, const Value &val) override;
        void remove(const Key &key) override { first = remove(first, key); }
        int size() const override { return N; }
        std::list<Key> keys() const override;
    };
}

template<typename Key, typename Value>
auto algs4::SequentialSearchST<Key, Value>::remove(std::unique_ptr<Node> &x, const Key &key) -> std::unique_ptr<Node> {
    if (!x)
        return nullptr;
    if (key == x->key) {
        --N;
        return std::move(x->next);
    }
    x->next = remove(x->next, key);
    return std::move(x);
}

template<typename Key, typename Value>
std::optional<Value> algs4::SequentialSearchST<Key, Value>::get(const Key &key) const {
    for (const Node *x = first.get(); x; x = x->next.get()) {
        if (key == x->key)
            return x->val;
    }
    return std::nullopt;
}

template<typename Key, typename Value>
void algs4::SequentialSearchST<Key, Value>::put(const Key &key, const Value &val) {
    for (Node *x = first.get(); x; x = x->next.get()) {
        if (key == x->key) {
            x->val = val;
            return;
        }
    }
    first = std::make_unique<Node>(key, val, std::move(first));
    ++N;
}

template<typename Key, typename Value>
std::list<Key> algs4::SequentialSearchST<Key, Value>::keys() const {
    std::list<Key> queue;
    for (const Node *x = first.get(); x; x = x->next.get())
        queue.push_back(x->key);
    return queue;
}


#endif //ALGS4_SEQUENTIALSEARCHST_H
