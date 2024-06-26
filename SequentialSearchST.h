#ifndef ALGS4_SEQUENTIALSEARCHST_H
#define ALGS4_SEQUENTIALSEARCHST_H


#include "ST.h"
#include <string>
#include <iostream>

template<typename Key, typename Value>
class SequentialSearchST : public ST<Key, Value> {
private:
    struct Node {
        Key key;
        Value val;
        Node *next;

        Node(Key key, Value val, Node *next) : key(key), val(val), next(next) {}
    };

    Node *first;

public:
    SequentialSearchST() : first(nullptr) {}

    Value get(Key key) override {
        for (Node *x = first; x != nullptr; x = x->next) {
            if (key == x->key) return x->val;
        }
        return Value();
    }

    void put(Key key, Value val) override {
        for (Node *x = first; x != nullptr; x = x->next) {
            if (key == x->key) {
                x->val = val;
                return;
            }
        }
        first = new Node(key, val, first);
    }

    std::vector<Key> keys() override {
        std::vector<Key> keys;
        for (Node *x = first; x != nullptr; x = x->next) {
            keys.push_back(x->key);
        }
        return keys;
    }

    ~SequentialSearchST() override {
        Node *current = first;
        while (current != nullptr) {
            Node *next = current->next;
            delete current;
            current = next;
        }
    }

    // % algs4 < tinyST.txt
    static void main() {
        SequentialSearchST<std::string, int> st;
        std::string key;
        for (int i = 0; std::cin >> key; ++i) {
            st.put(key, i);
        }
        for (const auto &s: st.keys()) {
            std::cout << s << " " << st.get(s) << "\n";
        }
    }
};


#endif //ALGS4_SEQUENTIALSEARCHST_H
