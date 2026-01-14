#ifndef ALGS4_TRIEST_HPP
#define ALGS4_TRIEST_HPP


#include <array>
#include <cstddef>
#include <memory>
#include <optional>
#include <string_view>
#include <utility>

#include "StringST.hpp"

namespace algs4 {
    template<typename Value>
    class TrieST : public StringST<Value> {
    private:
        static constexpr int R = 256; // radix
        std::ptrdiff_t N = 0;

        struct Node {
            std::optional<Value> val;
            std::array<std::unique_ptr<Node>, R> next;
        };

        std::unique_ptr<Node> root;

        const Node *get(const Node *x, std::string_view key, std::ptrdiff_t d) const;
        std::unique_ptr<Node> put(std::unique_ptr<Node> x, std::string_view key, Value val, std::ptrdiff_t d);
        std::unique_ptr<Node> remove(std::unique_ptr<Node> x, std::string_view key, std::ptrdiff_t d);
        void collect(const Node *x, const std::string &pre, std::vector<std::string> &q) const;
        void collect(const Node *x, const std::string &pre, std::string_view pat, std::vector<std::string> &q) const;
        std::ptrdiff_t search(const Node *x, std::string_view s, std::ptrdiff_t d, std::ptrdiff_t length) const;

    public:
        using ST<std::string, Value>::get;
        const Value *get(const std::string &key) const override;
        void put(std::string key, Value val) override;
        void remove(const std::string &key) override { root = remove(std::move(root), key, 0); }
        std::ptrdiff_t size() const override { return N; }
        std::vector<std::string> keys() const override { return keysWithPrefix(""); }
        std::string longestPrefixOf(std::string_view s) const override;
        std::vector<std::string> keysWithPrefix(const std::string &pre) const override;
        std::vector<std::string> keysThatMatch(std::string_view pat) const override;
    };
}

template<typename Value>
auto algs4::TrieST<Value>::get(const Node *x, std::string_view key, std::ptrdiff_t d) const -> const Node * {
    if (!x) return nullptr;
    if (d == std::ssize(key)) return x;
    unsigned char c = key[d];
    return get(x->next[c].get(), key, d + 1);
}

template<typename Value>
auto algs4::TrieST<Value>::put(std::unique_ptr<Node> x, std::string_view key, Value val,
                               std::ptrdiff_t d) -> std::unique_ptr<Node> {
    if (!x) x = std::make_unique<Node>();
    if (d == std::ssize(key)) {
        if (!x->val) ++N;
        x->val = std::move(val);
        return x;
    }
    unsigned char c = key[d];
    x->next[c] = put(std::move(x->next[c]), key, std::move(val), d + 1);
    return x;
}

template<typename Value>
auto algs4::TrieST<Value>::remove(std::unique_ptr<Node> x, std::string_view key,
                                  std::ptrdiff_t d) -> std::unique_ptr<Node> {
    if (!x) return nullptr;
    if (d == std::ssize(key)) {
        if (x->val) --N;
        x->val = std::nullopt;
    } else {
        unsigned char c = key[d];
        x->next[c] = remove(std::move(x->next[c]), key, d + 1);
    }

    // Remove subtrie rooted at x if it is completely empty.
    if (x->val) return x;
    for (int c = 0; c < R; ++c)
        if (x->next[c]) return x;
    return nullptr;
}

template<typename Value>
void algs4::TrieST<Value>::collect(const Node *x, const std::string &pre, std::vector<std::string> &q) const {
    if (!x) return;
    if (x->val) q.push_back(pre);
    for (int c = 0; c < R; ++c)
        collect(x->next[c].get(), pre + static_cast<char>(c), q);
}

template<typename Value>
void algs4::TrieST<Value>::collect(const Node *x, const std::string &pre, std::string_view pat,
                                   std::vector<std::string> &q) const {
    if (!x) return;
    auto d = std::ssize(pre);
    if (d == std::ssize(pat) && x->val) q.push_back(pre);
    if (d == std::ssize(pat)) return;

    char next = pat[d];
    for (int c = 0; c < R; ++c)
        if (next == '.' || next == c)
            collect(x->next[c].get(), pre + static_cast<char>(c), pat, q);
}

template<typename Value>
std::ptrdiff_t algs4::TrieST<Value>::search(const Node *x, std::string_view s, std::ptrdiff_t d,
                                            std::ptrdiff_t length) const {
    if (!x) return length;
    if (x->val) length = d;
    if (d == std::ssize(s)) return length;
    unsigned char c = s[d];
    return search(x->next[c].get(), s, d + 1, length);
}

template<typename Value>
const Value *algs4::TrieST<Value>::get(const std::string &key) const {
    const Node *x = get(root.get(), key, 0);
    if (!x) return nullptr;
    return &*x->val;
}

template<typename Value>
void algs4::TrieST<Value>::put(std::string key, Value val) {
    root = put(std::move(root), key, std::move(val), 0);
}

template<typename Value>
std::string algs4::TrieST<Value>::longestPrefixOf(std::string_view s) const {
    auto length = search(root.get(), s, 0, 0);
    return std::string(s.substr(0, length));
}

template<typename Value>
std::vector<std::string> algs4::TrieST<Value>::keysWithPrefix(const std::string &pre) const {
    std::vector<std::string> q;
    collect(get(root.get(), pre, 0), pre, q);
    return q;
}

template<typename Value>
std::vector<std::string> algs4::TrieST<Value>::keysThatMatch(std::string_view pat) const {
    std::vector<std::string> q;
    collect(root.get(), "", pat, q);
    return q;
}


#endif //ALGS4_TRIEST_HPP
