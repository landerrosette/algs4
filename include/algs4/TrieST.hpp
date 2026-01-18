/*
 * Copyright (C) 2024-2026 landerrosette
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
        std::ptrdiff_t N_ = 0;

        struct Node {
            std::optional<Value> val_;
            std::array<std::unique_ptr<Node>, R> next_;
        };

        std::unique_ptr<Node> root_;

        std::unique_ptr<Node> put(std::unique_ptr<Node> x, std::string_view key, Value val, std::ptrdiff_t d);
        const Node *get(const Node *x, std::string_view key, std::ptrdiff_t d) const;
        std::unique_ptr<Node> remove(std::unique_ptr<Node> x, std::string_view key, std::ptrdiff_t d);
        void collect(const Node *x, const std::string &pre, Queue<std::string> &q) const;
        void collect(const Node *x, const std::string &pre, std::string_view pat, Queue<std::string> &q) const;
        std::ptrdiff_t search(const Node *x, std::string_view s, std::ptrdiff_t d, std::ptrdiff_t length) const;

    public:
        void put(std::string key, Value val) override;
        using ST<std::string, Value>::get;
        const Value *get(const std::string &key) const override;
        void remove(const std::string &key) override { root_ = remove(std::move(root_), key, 0); }
        std::ptrdiff_t size() const override { return N_; }
        Queue<std::string> keys() const override { return keysWithPrefix(""); }
        std::string longestPrefixOf(std::string_view s) const override;
        Queue<std::string> keysWithPrefix(const std::string &pre) const override;
        Queue<std::string> keysThatMatch(std::string_view pat) const override;
    };
}

template<typename Value>
auto algs4::TrieST<Value>::put(std::unique_ptr<Node> x, std::string_view key, Value val,
                               std::ptrdiff_t d) -> std::unique_ptr<Node> {
    if (!x) x = std::make_unique<Node>();
    if (d == std::ssize(key)) {
        if (!x->val_) ++N_;
        x->val_ = std::move(val);
        return x;
    }
    unsigned char c = key[d];
    x->next_[c] = put(std::move(x->next_[c]), key, std::move(val), d + 1);
    return x;
}

template<typename Value>
auto algs4::TrieST<Value>::get(const Node *x, std::string_view key, std::ptrdiff_t d) const -> const Node * {
    if (!x) return nullptr;
    if (d == std::ssize(key)) return x;
    unsigned char c = key[d];
    return get(x->next_[c].get(), key, d + 1);
}

template<typename Value>
auto algs4::TrieST<Value>::remove(std::unique_ptr<Node> x, std::string_view key,
                                  std::ptrdiff_t d) -> std::unique_ptr<Node> {
    if (!x) return nullptr;
    if (d == std::ssize(key)) {
        if (x->val_) --N_;
        x->val_ = std::nullopt;
    } else {
        unsigned char c = key[d];
        x->next_[c] = remove(std::move(x->next_[c]), key, d + 1);
    }

    // Remove subtrie rooted at x if it is completely empty.
    if (x->val_) return x;
    for (int c = 0; c < R; ++c)
        if (x->next_[c]) return x;
    return nullptr;
}

template<typename Value>
void algs4::TrieST<Value>::collect(const Node *x, const std::string &pre, Queue<std::string> &q) const {
    if (!x) return;
    if (x->val_) q.enqueue(pre);
    for (int c = 0; c < R; ++c)
        collect(x->next_[c].get(), pre + static_cast<char>(c), q);
}

template<typename Value>
void algs4::TrieST<Value>::collect(const Node *x, const std::string &pre, std::string_view pat,
                                   Queue<std::string> &q) const {
    if (!x) return;
    auto d = std::ssize(pre);
    if (d == std::ssize(pat) && x->val_) q.enqueue(pre);
    if (d == std::ssize(pat)) return;

    char next = pat[d];
    for (int c = 0; c < R; ++c)
        if (next == '.' || next == c)
            collect(x->next_[c].get(), pre + static_cast<char>(c), pat, q);
}

template<typename Value>
std::ptrdiff_t algs4::TrieST<Value>::search(const Node *x, std::string_view s, std::ptrdiff_t d,
                                            std::ptrdiff_t length) const {
    if (!x) return length;
    if (x->val_) length = d;
    if (d == std::ssize(s)) return length;
    unsigned char c = s[d];
    return search(x->next_[c].get(), s, d + 1, length);
}

template<typename Value>
void algs4::TrieST<Value>::put(std::string key, Value val) {
    root_ = put(std::move(root_), key, std::move(val), 0);
}

template<typename Value>
const Value *algs4::TrieST<Value>::get(const std::string &key) const {
    const Node *x = get(root_.get(), key, 0);
    if (!x) return nullptr;
    return &*x->val_;
}

template<typename Value>
std::string algs4::TrieST<Value>::longestPrefixOf(std::string_view s) const {
    auto length = search(root_.get(), s, 0, 0);
    return std::string(s.substr(0, length));
}

template<typename Value>
algs4::Queue<std::string> algs4::TrieST<Value>::keysWithPrefix(const std::string &pre) const {
    Queue<std::string> q;
    collect(get(root_.get(), pre, 0), pre, q);
    return q;
}

template<typename Value>
algs4::Queue<std::string> algs4::TrieST<Value>::keysThatMatch(std::string_view pat) const {
    Queue<std::string> q;
    collect(root_.get(), "", pat, q);
    return q;
}

#endif // ALGS4_TRIEST_HPP
