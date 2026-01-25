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

#ifndef ALGS4_HUFFMAN_HPP
#define ALGS4_HUFFMAN_HPP

#include <compare>
#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "BinaryStdIO.hpp"
#include "PQBase.hpp"

namespace algs4 {
namespace Huffman {
    namespace detail {
        constexpr int R = 256;  // ASCII alphabet

        struct Node {
            char ch;
            std::ptrdiff_t freq;
            const std::shared_ptr<const Node> left, right;

            Node(char ch, std::ptrdiff_t freq, const std::shared_ptr<const Node>& left,
                 const std::shared_ptr<const Node>& right)
                : ch(ch), freq(freq), left(left), right(right) {}

            bool isLeaf() const { return !left && !right; }
            friend auto operator<=>(const Node& l, const Node& r) { return l.freq <=> r.freq; }
            friend bool operator==(const Node& l, const Node& r) { return l.freq == r.freq; }
        };

        // Make a lookup table from trie (recursive).
        inline void buildCode(std::vector<std::string>& st, const std::shared_ptr<const Node>& x,
                              const std::string& s) {
            if (x->isLeaf()) {
                st[static_cast<unsigned char>(x->ch)] = s;
                return;
            }
            buildCode(st, x->left, s + '0');
            buildCode(st, x->right, s + '1');
        }

        // Make a lookup table from trie.
        inline std::vector<std::string> buildCode(const std::shared_ptr<const Node>& root) {
            std::vector<std::string> st(R);
            buildCode(st, root, "");
            return st;
        }

        inline std::shared_ptr<const Node> buildTrie(const std::vector<std::ptrdiff_t>& freq) {
            class NodeMinPQ
                : public algs4::detail::PQBase<std::shared_ptr<const Node>,
                                               decltype([](const std::shared_ptr<const Node>& l,
                                                           const std::shared_ptr<const Node>& r) { return *l > *r; })> {
            public:
                auto delMin() { return delTop(); }
            };

            // Initialize priority queue with singleton trees.
            NodeMinPQ pq;
            for (int c = 0; c < R; ++c)
                if (freq[c] > 0) pq.insert(std::make_shared<Node>(c, freq[c], nullptr, nullptr));

            // Merge two smallest trees.
            while (pq.size() > 1) {
                auto x = pq.delMin();
                auto y = pq.delMin();
                pq.insert(std::make_shared<Node>('\0', x->freq + y->freq, x, y));
            }
            return pq.delMin();
        }

        // Write bitstring-encoded trie.
        inline void writeTrie(const std::shared_ptr<const Node>& x) {
            if (x->isLeaf()) {
                BinaryStdIO::write(true);
                BinaryStdIO::write(x->ch);
                return;
            }
            BinaryStdIO::write(false);
            writeTrie(x->left);
            writeTrie(x->right);
        }

        inline std::shared_ptr<const Node> readTrie() {
            if (BinaryStdIO::read<bool>())
                return std::make_shared<Node>(BinaryStdIO::read<char>(), 0, nullptr, nullptr);
            return std::make_shared<Node>('\0', 0, readTrie(), readTrie());
        }
    }  // namespace detail

    inline void compress() {
        using namespace detail;

        auto input = BinaryStdIO::read<std::string>();

        // Tabulate frequency counts.
        std::vector<std::ptrdiff_t> freq(R);
        for (unsigned char c : input) ++freq[c];

        // Build Huffman code trie.
        auto root = buildTrie(freq);

        // Build code table (recursive).
        std::vector<std::string> st(R);
        buildCode(st, root, "");

        // Print trie for decoder (recursive).
        writeTrie(root);

        // Print number of chars.
        BinaryStdIO::write(static_cast<int>(std::ssize(input)));

        // Use Huffman code to encode input.
        for (unsigned char i : input) {
            for (const auto& code = st[i]; char c : code) {
                if (c == '1')
                    BinaryStdIO::write(true);
                else
                    BinaryStdIO::write(false);
            }
        }
        BinaryStdIO::closeOut();
    }

    inline void expand() {
        using namespace detail;
        auto root = readTrie();
        auto N = BinaryStdIO::read<int>();
        while (N--) {
            auto x = root;
            while (!x->isLeaf())
                if (BinaryStdIO::read<bool>())
                    x = x->right;
                else
                    x = x->left;
            BinaryStdIO::write(x->ch);
        }
        BinaryStdIO::closeOut();
    }
}  // namespace Huffman
}  // namespace algs4

#endif  // ALGS4_HUFFMAN_HPP
