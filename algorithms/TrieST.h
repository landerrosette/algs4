#ifndef TRIEST_H
#define TRIEST_H


#include <memory>
#include <optional>
#include <vector>

#include "StringST.h"

template<typename Value>
class TrieST : public StringST<Value> {
private:
    inline static int R = 256; // radix
    int N = 0;

    struct Node {
        std::optional<Value> val;
        std::vector<std::unique_ptr<Node> > next = std::vector<std::unique_ptr<Node> >(R);
    };

    std::unique_ptr<Node> root;

    const Node *get(const Node *x, std::string_view key, int d) const;

    std::unique_ptr<Node> put(std::unique_ptr<Node> &x, std::string_view key, const Value &val, int d);

    std::unique_ptr<Node> remove(std::unique_ptr<Node> &x, std::string_view key, int d);

    void collect(const Node *x, const std::string &pre, std::list<std::string> &q) const;

    void collect(const Node *x, const std::string &pre, std::string_view pat,
                 std::list<std::string> &q) const;

    int search(const Node *x, std::string_view s, int d, int length) const;

public:
    std::optional<Value> get(const std::string &key) const override;

    void put(const std::string &key, const Value &val) override { root = put(root, key, val, 0); }

    void remove(const std::string &key) override { root = remove(root, key, 0); }

    int size() const override { return N; }

    std::list<std::string> keys() const override { return keysWithPrefix(""); }

    std::string longestPrefixOf(std::string_view s) const override;

    std::list<std::string> keysWithPrefix(const std::string &pre) const override;

    std::list<std::string> keysThatMatch(std::string_view pat) const override;
};

template<typename Value>
const typename TrieST<Value>::Node *TrieST<Value>::get(const Node *x, std::string_view key, int d) const {
    if (!x) return nullptr;
    if (d == key.length()) return x;
    char c = key[d];
    return get(x->next[c].get(), key, d + 1);
}

template<typename Value>
std::unique_ptr<typename TrieST<Value>::Node> TrieST<Value>::put(std::unique_ptr<Node> &x, std::string_view key,
                                                                 const Value &val, int d) {
    if (!x) x = std::make_unique<Node>();
    if (d == key.length()) {
        if (!x->val) ++N;
        x->val = val;
        return std::move(x);
    }
    char c = key[d];
    x->next[c] = put(x->next[c], key, val, d + 1);
    return std::move(x);
}

template<typename Value>
std::unique_ptr<typename TrieST<Value>::Node> TrieST<Value>::remove(std::unique_ptr<Node> &x, std::string_view key,
                                                                    int d) {
    if (!x) return nullptr;
    if (d == key.length()) {
        if (x->val) --N;
        x->val = std::nullopt;
    } else {
        char c = key[d];
        x->next[c] = remove(x->next[c], key, d + 1);
    }

    // Remove subtrie rooted at x if it is completely empty.
    if (x->val) return std::move(x);
    for (int c = 0; c < R; ++c) {
        if (x->next[c]) return std::move(x);
    }
    return nullptr;
}

template<typename Value>
void TrieST<Value>::collect(const Node *x, const std::string &pre, std::list<std::string> &q) const {
    if (!x) return;
    if (x->val) q.push_back(pre);
    for (int c = 0; c < R; ++c) collect(x->next[c].get(), pre + static_cast<char>(c), q);
}

template<typename Value>
void TrieST<Value>::collect(const Node *x, const std::string &pre, std::string_view pat,
                            std::list<std::string> &q) const {
    if (!x) return;
    int d = pre.length();
    if (d == pat.length() && x->val) q.push_back(pre);
    if (d == pat.length()) return;

    char next = pat[d];
    for (int c = 0; c < R; ++c) {
        if (next == '.' || next == c) collect(x->next[c].get(), pre + static_cast<char>(c), pat, q);
    }
}

template<typename Value>
int TrieST<Value>::search(const Node *x, std::string_view s, int d, int length) const {
    if (!x) return length;
    if (x->val) length = d;
    if (d == s.length()) return length;
    char c = s[d];
    return search(x->next[c].get(), s, d + 1, length);
}

template<typename Value>
std::optional<Value> TrieST<Value>::get(const std::string &key) const {
    const Node *x = get(root.get(), key, 0);
    if (!x) return std::nullopt;
    return x->val;
}

template<typename Value>
std::string TrieST<Value>::longestPrefixOf(std::string_view s) const {
    int length = search(root.get(), s, 0, 0);
    return std::string(s.substr(0, length));
}

template<typename Value>
std::list<std::string> TrieST<Value>::keysWithPrefix(const std::string &pre) const {
    std::list<std::string> q;
    collect(get(root.get(), pre, 0), pre, q);
    return q;
}

template<typename Value>
std::list<std::string> TrieST<Value>::keysThatMatch(std::string_view pat) const {
    std::list<std::string> q;
    collect(root.get(), "", pat, q);
    return q;
}


#endif //TRIEST_H
