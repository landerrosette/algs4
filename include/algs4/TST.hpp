#ifndef ALGS4_TST_HPP
#define ALGS4_TST_HPP


#include <cassert>
#include <cstddef>
#include <memory>
#include <optional>
#include <string_view>
#include <utility>

#include "StringST.hpp"

namespace algs4 {
    template<typename Value>
    class TST : public StringST<Value> {
    private:
        std::ptrdiff_t N = 0;

        struct Node {
            char c;
            std::unique_ptr<Node> left, mid, right;
            std::optional<Value> val;

            explicit Node(char c) : c(c) {}
        };

        std::unique_ptr<Node> root;

        const Node *get(const Node *x, std::string_view key, std::ptrdiff_t d) const;
        std::unique_ptr<Node> put(std::unique_ptr<Node> x, std::string_view key, Value val, std::ptrdiff_t d);
        std::unique_ptr<Node> remove(std::unique_ptr<Node> x, std::string_view key, std::ptrdiff_t d);
        void collect(const Node *x, const std::string &pre, std::vector<std::string> &q) const;
        void collect(const Node *x, const std::string &pre, std::string_view pat, std::vector<std::string> &q) const;
        std::ptrdiff_t search(const Node *x, std::string_view s, std::ptrdiff_t d, std::ptrdiff_t length) const;
        std::unique_ptr<Node> extractMin(std::unique_ptr<Node> &x);

    public:
        using ST<std::string, Value>::get;
        const Value *get(const std::string &key) const override;
        void put(std::string key, Value val) override;
        void remove(const std::string &key) override;
        std::ptrdiff_t size() const override { return N; }
        std::vector<std::string> keys() const override;
        std::string longestPrefixOf(std::string_view s) const override;
        std::vector<std::string> keysWithPrefix(const std::string &pre) const override;
        std::vector<std::string> keysThatMatch(std::string_view pat) const override;
    };
}

template<typename Value>
auto algs4::TST<Value>::get(const Node *x, std::string_view key, std::ptrdiff_t d) const -> const Node * {
    if (!x) return nullptr;
    char c = key[d];
    if (c < x->c) return get(x->left.get(), key, d);
    else if (c > x->c) return get(x->right.get(), key, d);
    else if (d + 1 < std::ssize(key)) return get(x->mid.get(), key, d + 1);
    else return x;
}

template<typename Value>
auto algs4::TST<Value>::put(std::unique_ptr<Node> x, std::string_view key, Value val,
                            std::ptrdiff_t d) -> std::unique_ptr<Node> {
    char c = key[d];
    if (!x) x = std::make_unique<Node>(c);
    if (c < x->c) x->left = put(std::move(x->left), key, std::move(val), d);
    else if (c > x->c) x->right = put(std::move(x->right), key, std::move(val), d);
    else if (d + 1 < std::ssize(key)) x->mid = put(std::move(x->mid), key, std::move(val), d + 1);
    else {
        if (!x->val) ++N;
        x->val = std::move(val);
    }
    return x;
}

template<typename Value>
auto algs4::TST<Value>::remove(std::unique_ptr<Node> x, std::string_view key,
                               std::ptrdiff_t d) -> std::unique_ptr<Node> {
    if (!x) return nullptr;
    char c = key[d];
    if (c < x->c) x->left = remove(std::move(x->left), key, d);
    else if (c > x->c) x->right = remove(std::move(x->right), key, d);
    else if (d + 1 < std::ssize(key)) x->mid = remove(std::move(x->mid), key, d + 1);
    else {
        if (x->val) --N;
        x->val = std::nullopt;
    }

    if (!x->mid && !x->val) {
        if (!x->right) return std::move(x->left);
        if (!x->left) return std::move(x->right);
        auto t = std::move(x);
        x = extractMin(t->right);
        x->right = std::move(t->right);
        x->left = std::move(t->left);
    }
    return x;
}

template<typename Value>
void algs4::TST<Value>::collect(const Node *x, const std::string &pre, std::vector<std::string> &q) const {
    if (!x) return;
    collect(x->left.get(), pre, q);
    if (x->val) q.push_back(pre + x->c);
    collect(x->mid.get(), pre + x->c, q);
    collect(x->right.get(), pre, q);
}

template<typename Value>
void algs4::TST<Value>::collect(const Node *x, const std::string &pre, std::string_view pat,
                                std::vector<std::string> &q) const {
    if (!x) return;
    auto d = std::ssize(pre);
    char next = pat[d];
    if (next == '.' || next < x->c) collect(x->left.get(), pre, pat, q);
    if (next == '.' || next == x->c) {
        if (d + 1 == std::ssize(pat) && x->val) q.push_back(pre + x->c);
        if (d + 1 < std::ssize(pat)) collect(x->mid.get(), pre + x->c, pat, q);
    }
    if (next == '.' || next > x->c) collect(x->right.get(), pre, pat, q);
}

template<typename Value>
std::ptrdiff_t algs4::TST<Value>::search(const Node *x, std::string_view s, std::ptrdiff_t d,
                                         std::ptrdiff_t length) const {
    if (!x) return length;
    char c = s[d];
    if (c < x->c) return search(x->left.get(), s, d, length);
    else if (c > x->c) return search(x->right.get(), s, d, length);
    else {
        if (x->val) length = d + 1;
        if (d + 1 == std::ssize(s)) return length;
        return search(x->mid.get(), s, d + 1, length);
    }
}

template<typename Value>
auto algs4::TST<Value>::extractMin(std::unique_ptr<Node> &x) -> std::unique_ptr<Node> {
    if (!x) return nullptr;
    if (!x->left) {
        auto min = std::move(x);
        x = std::move(min->right);
        return min;
    }
    return extractMin(x->left);
}

template<typename Value>
const Value *algs4::TST<Value>::get(const std::string &key) const {
    assert(!key.empty());
    const Node *x = get(root.get(), key, 0);
    if (!x) return nullptr;
    return &*x->val;
}

template<typename Value>
void algs4::TST<Value>::put(std::string key, Value val) {
    assert(!key.empty());
    root = put(std::move(root), key, std::move(val), 0);
}

template<typename Value>
void algs4::TST<Value>::remove(const std::string &key) {
    assert(!key.empty());
    root = remove(std::move(root), key, 0);
}

template<typename Value>
std::vector<std::string> algs4::TST<Value>::keys() const {
    // return keysWithPrefix(""); // Passing an empty key to get() is undefined.
    std::vector<std::string> q;
    collect(root.get(), "", q);
    return q;
}

template<typename Value>
std::string algs4::TST<Value>::longestPrefixOf(std::string_view s) const {
    if (s.empty()) return "";
    auto length = search(root.get(), s, 0, 0);
    return std::string(s.substr(0, length));
}

template<typename Value>
std::vector<std::string> algs4::TST<Value>::keysWithPrefix(const std::string &pre) const {
    std::vector<std::string> q;
    if (const Node *x = get(root.get(), pre, 0)) {
        if (x->val) q.push_back(pre);
        collect(x->mid.get(), pre, q);
    }
    return q;
}

template<typename Value>
std::vector<std::string> algs4::TST<Value>::keysThatMatch(std::string_view pat) const {
    std::vector<std::string> q;
    collect(root.get(), "", pat, q);
    return q;
}


#endif //ALGS4_TST_HPP
