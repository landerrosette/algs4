#ifndef ALGS4_HUFFMAN_HPP
#define ALGS4_HUFFMAN_HPP


#include <compare>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "BinaryStdIO.hpp"
#include "PQBase.hpp"

namespace algs4 {
    namespace Huffman {
        namespace internal {
            inline int R = 256; // ASCII alphabet

            struct Node {
                char ch;
                int freq;
                const std::shared_ptr<const Node> left, right;

                Node(char ch, int freq, const std::shared_ptr<const Node> &left,
                     const std::shared_ptr<const Node> &right)
                    : ch(ch), freq(freq), left(left), right(right) {}

                bool isLeaf() const { return !left && !right; }
                friend auto operator<=>(const Node &l, const Node &r) { return l.freq <=> r.freq; }
                friend bool operator==(const Node &l, const Node &r) { return l.freq == r.freq; }
            };

            std::vector<std::string> buildCode(const std::shared_ptr<const Node> &root);
            void buildCode(std::vector<std::string> &st, const std::shared_ptr<const Node> &x, const std::string &s);
            std::shared_ptr<const Node> buildTrie(const std::vector<int> &freq);
            void writeTrie(const std::shared_ptr<const Node> &x);
            std::shared_ptr<const Node> readTrie();
        }

        void compress();
        void expand();
    }
}

// Make a lookup table from trie.
inline std::vector<std::string> algs4::Huffman::internal::buildCode(const std::shared_ptr<const Node> &root) {
    std::vector<std::string> st(R);
    buildCode(st, root, "");
    return st;
}

// Make a lookup table from trie (recursive).
inline void algs4::Huffman::internal::buildCode(std::vector<std::string> &st, const std::shared_ptr<const Node> &x,
                                                const std::string &s) {
    if (x->isLeaf()) {
        st[x->ch] = s;
        return;
    }
    buildCode(st, x->left, s + '0');
    buildCode(st, x->right, s + '1');
}

// Initialize priority queue with singleton trees.
inline auto algs4::Huffman::internal::buildTrie(const std::vector<int> &freq) -> std::shared_ptr<const Node> {
    class NodeMinPQ : public PQBase<std::shared_ptr<const Node>, decltype([](const std::shared_ptr<const Node> &l,
                                                                             const std::shared_ptr<const Node> &r) {
                return *l > *r;
            })> {
    public:
        explicit NodeMinPQ(int maxN) : PQBase(maxN) {}

        auto delMin() { return delTop(); }
    };

    NodeMinPQ pq(R);
    for (int c = 0; c < R; ++c)
        if (freq[c] > 0)
            pq.insert(std::make_shared<Node>(c, freq[c], nullptr, nullptr));

    // Merge two smallest trees.
    while (pq.size() > 1) {
        auto x = *pq.delMin();
        auto y = *pq.delMin();
        pq.insert(std::make_shared<Node>('\0', x->freq + y->freq, x, y));
    }
    return *pq.delMin();
}

// Write bitstring-encoded trie.
inline void algs4::Huffman::internal::writeTrie(const std::shared_ptr<const Node> &x) {
    if (x->isLeaf()) {
        BinaryStdIO::write(true);
        BinaryStdIO::write(x->ch);
        return;
    }
    BinaryStdIO::write(false);
    writeTrie(x->left);
    writeTrie(x->right);
}

inline auto algs4::Huffman::internal::readTrie() -> std::shared_ptr<const Node> {
    if (BinaryStdIO::readBool())
        return std::make_shared<Node>(BinaryStdIO::readChar(), 0, nullptr, nullptr);
    return std::make_shared<Node>('\0', 0, readTrie(), readTrie());
}

inline void algs4::Huffman::compress() {
    using namespace internal;

    std::string input = BinaryStdIO::readString();

    std::vector<int> freq(R);
    for (int i = 0; i < input.length(); ++i) ++freq[input[i]];

    auto root = buildTrie(freq);

    std::vector<std::string> st(R);
    buildCode(st, root, "");

    writeTrie(root);
    BinaryStdIO::write(static_cast<int>(input.length()));
    for (int i = 0; i < input.length(); ++i) {
        const auto &code = st[input[i]];
        for (int j = 0; j < code.length(); ++j) {
            if (code[j] == '1') BinaryStdIO::write(true);
            else BinaryStdIO::write(false);
        }
    }
    BinaryStdIO::closeOut();
}

inline void algs4::Huffman::expand() {
    using namespace internal;
    auto root = readTrie();
    int N = BinaryStdIO::readInt();
    for (int i = 0; i < N; ++i) {
        auto x = root;
        while (!x->isLeaf()) {
            if (BinaryStdIO::readBool()) x = x->right;
            else x = x->left;
        }
        BinaryStdIO::write(x->ch);
    }
    BinaryStdIO::closeOut();
}


#endif //ALGS4_HUFFMAN_HPP
