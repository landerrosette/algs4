#ifndef ALGS4_SEQUENTIALSEARCHST_H
#define ALGS4_SEQUENTIALSEARCHST_H


#include "ST.h"
#include <memory>

template <typename Key, typename Value>
class SequentialSearchST : public ST<Key, Value> {
private:
    struct Node {
        Key key;
        Value val;
        std::shared_ptr<Node> next;

        Node(Key key, Value val, std::shared_ptr<Node> next) : key(key), val(val), next(next) {}
    };

    int N = 0;
    std::shared_ptr<Node> first;

    std::shared_ptr<Node> remove(std::shared_ptr<Node> x, Key key);

public:
    std::optional<Value> get(const Key& key) const override;

    void put(const Key& key, const Value& val) override;

    void remove(const Key& key) override { first = remove(first, key); }

    int size() const override { return N; }

    std::list<Key> keys() const override;
};

template <typename Key, typename Value>
std::shared_ptr<typename SequentialSearchST<Key, Value>::Node>
SequentialSearchST<Key, Value>::remove(std::shared_ptr<Node> x, Key key) {
    if (!x) return nullptr; // 基准情况：如果当前节点为空，返回 nullptr
    if (key == x->key) {
        --N;
        return x->next;
    }
    x->next = remove(x->next, key); // 递归调用，在下一个节点中继续删除指定的键
    return x;                       // 返回当前节点，当前节点没有被删除
}

template <typename Key, typename Value>
std::optional<Value> SequentialSearchST<Key, Value>::get(const Key& key) const {
    for (auto x = first; x; x = x->next) {
        if (key == x->key) return x->val;
    }
    return std::nullopt;
}

template <typename Key, typename Value>
void SequentialSearchST<Key, Value>::put(const Key& key, const Value& val) {
    for (auto x = first; x; x = x->next) {
        if (key == x->key) {
            x->val = val;
            return;
        }
    }
    first = std::make_shared<Node>(key, val, first);
    ++N;
}

template <typename Key, typename Value>
std::list<Key> SequentialSearchST<Key, Value>::keys() const {
    std::list<Key> queue;
    for (auto x = first; x; x = x->next) queue.push_back(x->key);
    return queue;
}


#endif //ALGS4_SEQUENTIALSEARCHST_H
