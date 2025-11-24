#ifndef ALGS4_HUFFMAN_H
#define ALGS4_HUFFMAN_H


#include <memory>
#include <string>
#include <vector>

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
                friend bool operator<(const Node &l, const Node &r) { return l.freq < r.freq; }
                friend bool operator>(const Node &l, const Node &r) { return r < l; }
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


#endif //ALGS4_HUFFMAN_H
