/*
 * Copyright (C) 2024-2026  landerrosette <57791410+landerrosette@users.noreply.github.com>
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
template <std::movable Value>
class TST : public StringST<Value> {
private:
    struct Node {
        char c;
        std::unique_ptr<Node> left, mid, right;
        std::optional<Value> val;

        explicit Node(char c) : c(c) {}
    };

    std::unique_ptr<Node> root_;
    std::ptrdiff_t N_ = 0;

    std::unique_ptr<Node> put(std::unique_ptr<Node> x, std::string_view key, Value val, std::ptrdiff_t d) {
        char c = key[d];
        if (!x) x = std::make_unique<Node>(c);
        if (c < x->c)
            x->left = put(std::move(x->left), key, std::move(val), d);
        else if (c > x->c)
            x->right = put(std::move(x->right), key, std::move(val), d);
        else if (d < std::ssize(key) - 1)
            x->mid = put(std::move(x->mid), key, std::move(val), d + 1);
        else {
            if (!x->val) ++N_;
            x->val = std::move(val);
        }
        return x;
    }

    const Node* get(const Node* x, std::string_view key, std::ptrdiff_t d) const {
        if (!x) return nullptr;
        char c = key[d];
        if (c < x->c)
            return get(x->left.get(), key, d);
        else if (c > x->c)
            return get(x->right.get(), key, d);
        else if (d < std::ssize(key) - 1)
            return get(x->mid.get(), key, d + 1);
        else
            return x;
    }

    std::unique_ptr<Node> extractMin(std::unique_ptr<Node>& x) {
        if (!x) return nullptr;
        if (!x->left) {
            auto min = std::move(x);
            x = std::move(min->right);
            return min;
        }
        return extractMin(x->left);
    }

    std::unique_ptr<Node> remove(std::unique_ptr<Node> x, std::string_view key, std::ptrdiff_t d) {
        if (!x) return nullptr;
        char c = key[d];
        if (c < x->c)
            x->left = remove(std::move(x->left), key, d);
        else if (c > x->c)
            x->right = remove(std::move(x->right), key, d);
        else if (d + 1 < std::ssize(key))
            x->mid = remove(std::move(x->mid), key, d + 1);
        else {
            if (x->val) --N_;
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

    void collect(const Node* x, const std::string& pre, Queue<std::string>& q) const {
        if (!x) return;
        collect(x->left.get(), pre, q);
        if (x->val) q.enqueue(pre + x->c);
        collect(x->mid.get(), pre + x->c, q);
        collect(x->right.get(), pre, q);
    }

    void collect(const Node* x, const std::string& pre, std::string_view pat, Queue<std::string>& q) const {
        if (!x) return;
        auto d = std::ssize(pre);
        char next = pat[d];
        if (next == '.' || next < x->c) collect(x->left.get(), pre, pat, q);
        if (next == '.' || next == x->c) {
            if (d == std::ssize(pat) - 1 && x->val) q.enqueue(pre + x->c);
            if (d < std::ssize(pat) - 1) collect(x->mid.get(), pre + x->c, pat, q);
        }
        if (next == '.' || next > x->c) collect(x->right.get(), pre, pat, q);
    }

    std::ptrdiff_t search(const Node* x, std::string_view s, std::ptrdiff_t d, std::ptrdiff_t length) const {
        if (!x) return length;
        char c = s[d];
        if (c < x->c)
            return search(x->left.get(), s, d, length);
        else if (c > x->c)
            return search(x->right.get(), s, d, length);
        else {
            if (x->val) length = d + 1;
            if (d + 1 == std::ssize(s)) return length;
            return search(x->mid.get(), s, d + 1, length);
        }
    }

public:
    void put(std::string key, Value val) override {
        assert(!key.empty());
        root_ = put(std::move(root_), key, std::move(val), 0);
    }

    using ST<std::string, Value>::get;
    const Value* get(const std::string& key) const override {
        assert(!key.empty());
        const Node* x = get(root_.get(), key, 0);
        if (!x) return nullptr;
        return &*x->val;
    }

    void remove(const std::string& key) override {
        assert(!key.empty());
        root_ = remove(std::move(root_), key, 0);
    }

    std::ptrdiff_t size() const override { return N_; }

    Queue<std::string> keys() const override {
        Queue<std::string> q;
        collect(root_.get(), "", q);
        return q;
    }

    std::string longestPrefixOf(std::string_view s) const override {
        if (s.empty()) return "";
        auto length = search(root_.get(), s, 0, 0);
        return std::string(s.substr(0, length));
    }

    Queue<std::string> keysWithPrefix(const std::string& pre) const override {
        Queue<std::string> q;
        if (const Node* x = get(root_.get(), pre, 0)) {
            if (x->val) q.enqueue(pre);
            collect(x->mid.get(), pre, q);
        }
        return q;
    }

    Queue<std::string> keysThatMatch(std::string_view pat) const override {
        Queue<std::string> q;
        collect(root_.get(), "", pat, q);
        return q;
    }
};
}  // namespace algs4

#endif  // ALGS4_TST_HPP
