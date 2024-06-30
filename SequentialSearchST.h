#ifndef ALGS4_SEQUENTIALSEARCHST_H
#define ALGS4_SEQUENTIALSEARCHST_H


#include "ST.h"
#include <string>
#include <iostream>
#include <memory>

template<typename Key, typename Value>
class SequentialSearchST : public ST<Key, Value> {
private:
    struct Node {
        Key key;
        Value val;
        std::shared_ptr<Node> next;

        Node(Key key, Value val, std::shared_ptr<Node> next) : key(key), val(val), next(next) {}
    };

    std::shared_ptr<Node> first = nullptr;

    std::shared_ptr<Node> remove(std::shared_ptr<Node> x, Key key) {
        if (x == nullptr) return nullptr; // 基准情况：如果当前节点为空，返回 null
        if (key == x->key) {
            --ST<Key, Value>::N;
            return x->next;
        }
        x->next = remove(x->next, key);     // 递归调用，在下一个节点中继续删除指定的键
        return x;                           // 返回当前节点，当前节点没有被删除
    }

public:
    Value get(Key key) override {
        for (auto x = first; x != nullptr; x = x->next) {
            if (key == x->key) return x->val;
        }
        return Value();
    }

    void put(Key key, Value val) override {
        for (auto x = first; x != nullptr; x = x->next) {
            if (key == x->key) {
                x->val = val;
                return;
            }
        }
        first = std::make_shared<Node>(key, val, first);
        ++ST<Key, Value>::N;
    }

    std::deque<Key> getKeys() override {
        std::deque<Key> queue;
        for (auto x = first; x != nullptr; x = x->next) {
            queue.push_back(x->key);
        }
        return queue;
    }

    void remove(Key key) override {
        first = remove(first, key);
    }
};


#endif //ALGS4_SEQUENTIALSEARCHST_H
