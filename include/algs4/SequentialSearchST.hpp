#ifndef ALGS4_SEQUENTIALSEARCHST_HPP
#define ALGS4_SEQUENTIALSEARCHST_HPP


#include <cstddef>
#include <memory>
#include <utility>

#include "ST.hpp"

namespace algs4 {
    template<typename Key, typename Value>
    class SequentialSearchST : public ST<Key, Value> {
    private:
        struct Node {
            Key key;
            Value val;
            std::unique_ptr<Node> next;

            Node(Key key, Value val, std::unique_ptr<Node> next)
                : key(std::move(key)), val(std::move(val)), next(std::move(next)) {}
        };

        std::ptrdiff_t N = 0;
        std::unique_ptr<Node> first;

        std::unique_ptr<Node> remove(std::unique_ptr<Node> x, const Key &key);

    public:
        constexpr SequentialSearchST() = default;
        using ST<Key, Value>::get;
        const Value *get(const Key &key) const override;
        void put(Key key, Value val) override;
        void remove(const Key &key) override { first = remove(std::move(first), key); }
        std::ptrdiff_t size() const override { return N; }
        std::vector<Key> keys() const override;
    };
}

template<typename Key, typename Value>
auto algs4::SequentialSearchST<Key, Value>::remove(std::unique_ptr<Node> x, const Key &key) -> std::unique_ptr<Node> {
    if (!x)
        return nullptr;
    if (key == x->key) {
        --N;
        return std::move(x->next);
    }
    x->next = remove(std::move(x->next), key);
    return x;
}

template<typename Key, typename Value>
const Value *algs4::SequentialSearchST<Key, Value>::get(const Key &key) const {
    for (const Node *x = first.get(); x; x = x->next.get())
        if (key == x->key)
            return &x->val;
    return nullptr;
}

template<typename Key, typename Value>
void algs4::SequentialSearchST<Key, Value>::put(Key key, Value val) {
    for (Node *x = first.get(); x; x = x->next.get())
        if (key == x->key) {
            x->val = std::move(val);
            return;
        }
    first = std::make_unique<Node>(std::move(key), std::move(val), std::move(first));
    ++N;
}

template<typename Key, typename Value>
std::vector<Key> algs4::SequentialSearchST<Key, Value>::keys() const {
    std::vector<Key> queue;
    for (const Node *x = first.get(); x; x = x->next.get())
        queue.push_back(x->key);
    return queue;
}


#endif //ALGS4_SEQUENTIALSEARCHST_HPP
