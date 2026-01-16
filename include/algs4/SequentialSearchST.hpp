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
            Key key_;
            Value val_;
            std::unique_ptr<Node> next_;

            Node(Key key, Value val, std::unique_ptr<Node> next)
                : key_(std::move(key)), val_(std::move(val)), next_(std::move(next)) {}
        };

        std::ptrdiff_t N_ = 0;
        std::unique_ptr<Node> first_;

        std::unique_ptr<Node> remove(std::unique_ptr<Node> x, const Key &key);

    public:
        constexpr SequentialSearchST() = default;
        using ST<Key, Value>::get;
        const Value *get(const Key &key) const override;
        void put(Key key, Value val) override;
        void remove(const Key &key) override { first_ = remove(std::move(first_), key); }
        std::ptrdiff_t size() const override { return N_; }
        std::vector<Key> keys() const override;
    };
}

template<typename Key, typename Value>
auto algs4::SequentialSearchST<Key, Value>::remove(std::unique_ptr<Node> x, const Key &key) -> std::unique_ptr<Node> {
    if (!x)
        return nullptr;
    if (key == x->key_) {
        --N_;
        return std::move(x->next_);
    }
    x->next_ = remove(std::move(x->next_), key);
    return x;
}

template<typename Key, typename Value>
const Value *algs4::SequentialSearchST<Key, Value>::get(const Key &key) const {
    for (const Node *x = first_.get(); x; x = x->next_.get())
        if (key == x->key_)
            return &x->val_;
    return nullptr;
}

template<typename Key, typename Value>
void algs4::SequentialSearchST<Key, Value>::put(Key key, Value val) {
    for (Node *x = first_.get(); x; x = x->next_.get())
        if (key == x->key_) {
            x->val_ = std::move(val);
            return;
        }
    first_ = std::make_unique<Node>(std::move(key), std::move(val), std::move(first_));
    ++N_;
}

template<typename Key, typename Value>
std::vector<Key> algs4::SequentialSearchST<Key, Value>::keys() const {
    std::vector<Key> queue;
    for (const Node *x = first_.get(); x; x = x->next_.get())
        queue.push_back(x->key_);
    return queue;
}


#endif //ALGS4_SEQUENTIALSEARCHST_HPP
