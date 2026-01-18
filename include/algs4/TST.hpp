/*
 * Copyright (C) 2024 landerrosette
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
        std::ptrdiff_t N_ = 0;

        struct Node {
            char c_;
            std::unique_ptr<Node> left_, mid_, right_;
            std::optional<Value> val_;

            explicit Node(char c) : c_(c) {}
        };

        std::unique_ptr<Node> root_;

        std::unique_ptr<Node> put(std::unique_ptr<Node> x, std::string_view key, Value val, std::ptrdiff_t d);
        const Node *get(const Node *x, std::string_view key, std::ptrdiff_t d) const;
        std::unique_ptr<Node> extractMin(std::unique_ptr<Node> &x);
        std::unique_ptr<Node> remove(std::unique_ptr<Node> x, std::string_view key, std::ptrdiff_t d);
        void collect(const Node *x, const std::string &pre, Queue<std::string> &q) const;
        void collect(const Node *x, const std::string &pre, std::string_view pat, Queue<std::string> &q) const;
        std::ptrdiff_t search(const Node *x, std::string_view s, std::ptrdiff_t d, std::ptrdiff_t length) const;

    public:
        void put(std::string key, Value val) override;
        using ST<std::string, Value>::get;
        const Value *get(const std::string &key) const override;
        void remove(const std::string &key) override;
        std::ptrdiff_t size() const override { return N_; }
        Queue<std::string> keys() const override;
        std::string longestPrefixOf(std::string_view s) const override;
        Queue<std::string> keysWithPrefix(const std::string &pre) const override;
        Queue<std::string> keysThatMatch(std::string_view pat) const override;
    };
}

template<typename Value>
auto algs4::TST<Value>::put(std::unique_ptr<Node> x, std::string_view key, Value val,
                            std::ptrdiff_t d) -> std::unique_ptr<Node> {
    char c = key[d];
    if (!x) x = std::make_unique<Node>(c);
    if (c < x->c_) x->left_ = put(std::move(x->left_), key, std::move(val), d);
    else if (c > x->c_) x->right_ = put(std::move(x->right_), key, std::move(val), d);
    else if (d < std::ssize(key) - 1) x->mid_ = put(std::move(x->mid_), key, std::move(val), d + 1);
    else {
        if (!x->val_) ++N_;
        x->val_ = std::move(val);
    }
    return x;
}

template<typename Value>
auto algs4::TST<Value>::get(const Node *x, std::string_view key, std::ptrdiff_t d) const -> const Node * {
    if (!x) return nullptr;
    char c = key[d];
    if (c < x->c_) return get(x->left_.get(), key, d);
    else if (c > x->c_) return get(x->right_.get(), key, d);
    else if (d < std::ssize(key) - 1) return get(x->mid_.get(), key, d + 1);
    else return x;
}

template<typename Value>
auto algs4::TST<Value>::extractMin(std::unique_ptr<Node> &x) -> std::unique_ptr<Node> {
    if (!x) return nullptr;
    if (!x->left_) {
        auto min = std::move(x);
        x = std::move(min->right_);
        return min;
    }
    return extractMin(x->left_);
}

template<typename Value>
auto algs4::TST<Value>::remove(std::unique_ptr<Node> x, std::string_view key,
                               std::ptrdiff_t d) -> std::unique_ptr<Node> {
    if (!x) return nullptr;
    char c = key[d];
    if (c < x->c_) x->left_ = remove(std::move(x->left_), key, d);
    else if (c > x->c_) x->right_ = remove(std::move(x->right_), key, d);
    else if (d + 1 < std::ssize(key)) x->mid_ = remove(std::move(x->mid_), key, d + 1);
    else {
        if (x->val_) --N_;
        x->val_ = std::nullopt;
    }

    if (!x->mid_ && !x->val_) {
        if (!x->right_) return std::move(x->left_);
        if (!x->left_) return std::move(x->right_);
        auto t = std::move(x);
        x = extractMin(t->right_);
        x->right_ = std::move(t->right_);
        x->left_ = std::move(t->left_);
    }
    return x;
}

template<typename Value>
void algs4::TST<Value>::collect(const Node *x, const std::string &pre, Queue<std::string> &q) const {
    if (!x) return;
    collect(x->left_.get(), pre, q);
    if (x->val_) q.enqueue(pre + x->c_);
    collect(x->mid_.get(), pre + x->c_, q);
    collect(x->right_.get(), pre, q);
}

template<typename Value>
void algs4::TST<Value>::collect(const Node *x, const std::string &pre, std::string_view pat,
                                Queue<std::string> &q) const {
    if (!x) return;
    auto d = std::ssize(pre);
    char next = pat[d];
    if (next == '.' || next < x->c_) collect(x->left_.get(), pre, pat, q);
    if (next == '.' || next == x->c_) {
        if (d == std::ssize(pat) - 1 && x->val_) q.enqueue(pre + x->c_);
        if (d < std::ssize(pat) - 1) collect(x->mid_.get(), pre + x->c_, pat, q);
    }
    if (next == '.' || next > x->c_) collect(x->right_.get(), pre, pat, q);
}

template<typename Value>
std::ptrdiff_t algs4::TST<Value>::search(const Node *x, std::string_view s, std::ptrdiff_t d,
                                         std::ptrdiff_t length) const {
    if (!x) return length;
    char c = s[d];
    if (c < x->c_) return search(x->left_.get(), s, d, length);
    else if (c > x->c_) return search(x->right_.get(), s, d, length);
    else {
        if (x->val_) length = d + 1;
        if (d + 1 == std::ssize(s)) return length;
        return search(x->mid_.get(), s, d + 1, length);
    }
}

template<typename Value>
void algs4::TST<Value>::put(std::string key, Value val) {
    assert(!key.empty());
    root_ = put(std::move(root_), key, std::move(val), 0);
}

template<typename Value>
const Value *algs4::TST<Value>::get(const std::string &key) const {
    assert(!key.empty());
    const Node *x = get(root_.get(), key, 0);
    if (!x) return nullptr;
    return &*x->val_;
}

template<typename Value>
void algs4::TST<Value>::remove(const std::string &key) {
    assert(!key.empty());
    root_ = remove(std::move(root_), key, 0);
}

template<typename Value>
algs4::Queue<std::string> algs4::TST<Value>::keys() const {
    Queue<std::string> q;
    collect(root_.get(), "", q);
    return q;
}

template<typename Value>
std::string algs4::TST<Value>::longestPrefixOf(std::string_view s) const {
    if (s.empty()) return "";
    auto length = search(root_.get(), s, 0, 0);
    return std::string(s.substr(0, length));
}

template<typename Value>
algs4::Queue<std::string> algs4::TST<Value>::keysWithPrefix(const std::string &pre) const {
    Queue<std::string> q;
    if (const Node *x = get(root_.get(), pre, 0)) {
        if (x->val_) q.enqueue(pre);
        collect(x->mid_.get(), pre, q);
    }
    return q;
}

template<typename Value>
algs4::Queue<std::string> algs4::TST<Value>::keysThatMatch(std::string_view pat) const {
    Queue<std::string> q;
    collect(root_.get(), "", pat, q);
    return q;
}

#endif // ALGS4_TST_HPP
