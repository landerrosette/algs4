#include "Huffman.h"

#include <iostream>
#include <vector>

#include "BinaryStdIO.h"
#include "MinPQ.h"

// Make a lookup table from trie.
std::vector<std::string> Huffman::buildCode(const std::shared_ptr<Node> &root) {
    std::vector<std::string> st(R);
    buildCode(st, root, "");
    return st;
}

// Make a lookup table from trie (recursive).
void Huffman::buildCode(std::vector<std::string> &st, const std::shared_ptr<Node> &x, const std::string &s) {
    if (x->isLeaf()) {
        st[x->ch] = s;
        return;
    }
    buildCode(st, x->left, s + '0');
    buildCode(st, x->right, s + '1');
}

// Initialize priority queue with singleton trees.
std::shared_ptr<Huffman::Node> Huffman::buildTrie(const std::vector<int> &freq) {
    MinPQ<NodePtr> pq(R);
    for (int c = 0; c < R; ++c) {
        if (freq[c] > 0) pq.insert(std::make_shared<Node>(c, freq[c], nullptr, nullptr));
    }

    // Merge two smallest trees.
    while (pq.size() > 1) {
        auto x = *pq.delMin();
        auto y = *pq.delMin();
        pq.insert(std::make_shared<Node>('\0', x->freq + y->freq, x, y));
    }
    return *pq.delMin();
}

// Write bitstring-encoded trie.
void Huffman::writeTrie(const std::shared_ptr<Node> &x) {
    if (x->isLeaf()) {
        BinaryStdIO::write(true);
        BinaryStdIO::write(x->ch);
        return;
    }
    BinaryStdIO::write(false);
    writeTrie(x->left);
    writeTrie(x->right);
}

std::shared_ptr<Huffman::Node> Huffman::readTrie() {
    if (BinaryStdIO::readBool()) return std::make_shared<Node>(BinaryStdIO::readChar(), 0, nullptr, nullptr);
    return std::make_shared<Node>('\0', 0, readTrie(), readTrie());
}

void Huffman::compress() {
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

void Huffman::expand() {
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
