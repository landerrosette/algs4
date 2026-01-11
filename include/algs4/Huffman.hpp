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
        namespace internal {
            constexpr int R = 256; // ASCII alphabet

            struct Node {
                char ch;
                std::ptrdiff_t freq;
                const std::shared_ptr<const Node> left, right;

                Node(char ch, std::ptrdiff_t freq, const std::shared_ptr<const Node> &left,
                     const std::shared_ptr<const Node> &right)
                    : ch(ch), freq(freq), left(left), right(right) {}

                bool isLeaf() const { return !left && !right; }
                friend auto operator<=>(const Node &l, const Node &r) { return l.freq <=> r.freq; }
                friend bool operator==(const Node &l, const Node &r) { return l.freq == r.freq; }
            };

            std::vector<std::string> buildCode(const std::shared_ptr<const Node> &root);
            void buildCode(std::vector<std::string> &st, const std::shared_ptr<const Node> &x, const std::string &s);
            std::shared_ptr<const Node> buildTrie(const std::vector<std::ptrdiff_t> &freq);
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
inline auto algs4::Huffman::internal::buildTrie(const std::vector<std::ptrdiff_t> &freq)
    -> std::shared_ptr<const Node> {
    class NodeMinPQ : public PQBase<std::shared_ptr<const Node>, decltype([](const std::shared_ptr<const Node> &l,
                                                                             const std::shared_ptr<const Node> &r) {
                return *l > *r;
            })> {
    public:
        explicit NodeMinPQ(std::ptrdiff_t maxN) : PQBase(maxN) {}

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
    if (BinaryStdIO::read<bool>())
        return std::make_shared<Node>(BinaryStdIO::read<char>(), 0, nullptr, nullptr);
    return std::make_shared<Node>('\0', 0, readTrie(), readTrie());
}

inline void algs4::Huffman::compress() {
    using namespace internal;

    auto input = BinaryStdIO::read<std::string>();

    std::vector<std::ptrdiff_t> freq(R);
    for (unsigned char c: input) ++freq[c];

    auto root = buildTrie(freq);

    std::vector<std::string> st(R);
    buildCode(st, root, "");

    writeTrie(root);
    BinaryStdIO::write(std::ssize(input));
    for (unsigned char i: input) {
        for (const auto &code = st[i]; char j: code) {
            if (j == '1') BinaryStdIO::write(true);
            else BinaryStdIO::write(false);
        }
    }
    BinaryStdIO::closeOut();
}

inline void algs4::Huffman::expand() {
    using namespace internal;
    auto root = readTrie();
    auto N = BinaryStdIO::read<std::ptrdiff_t>();
    for (auto i = N; i > 0; --i) {
        auto x = root;
        while (!x->isLeaf()) {
            if (BinaryStdIO::read<bool>()) x = x->right;
            else x = x->left;
        }
        BinaryStdIO::write(x->ch);
    }
    BinaryStdIO::closeOut();
}


#endif //ALGS4_HUFFMAN_HPP
