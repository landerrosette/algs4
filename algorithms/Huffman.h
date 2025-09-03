#ifndef ALGS4_HUFFMAN_H
#define ALGS4_HUFFMAN_H


#include <memory>
#include <string>
#include <vector>

class Huffman {
private:
    inline static int R = 256; // ASCII alphabet

    struct Node {
        char ch;
        int freq;
        const std::shared_ptr<Node> left, right;

        Node(char ch, int freq, const std::shared_ptr<Node> &left,
             const std::shared_ptr<Node> &right) : ch(ch), freq(freq), left(left), right(right) {}

        bool isLeaf() const { return !left && !right; }

        friend bool operator<(const Node &l, const Node &r) { return l.freq < r.freq; }

        friend bool operator>(const Node &l, const Node &r) { return r < l; }
    };

    static std::vector<std::string> buildCode(const std::shared_ptr<Node> &root);

    static void buildCode(std::vector<std::string> &st, const std::shared_ptr<Node> &x, const std::string &s);

    static std::shared_ptr<Node> buildTrie(const std::vector<int> &freq);

    static void writeTrie(const std::shared_ptr<Node> &x);

    static std::shared_ptr<Node> readTrie();

public:
    // comparable std::shared_ptr<Node> wrapper
    class NodePtr {
    private:
        std::shared_ptr<Node> nodePtr;

    public:
        NodePtr(const std::shared_ptr<Node> &sp) : nodePtr(sp) {}

        operator std::shared_ptr<Node>() const { return nodePtr; }

        Node *operator->() { return nodePtr.operator->(); }

        const Node *operator->() const { return nodePtr.operator->(); }

        friend bool operator<(const NodePtr &l, const NodePtr &r) { return *l.nodePtr < *r.nodePtr; }

        friend bool operator>(const NodePtr &l, const NodePtr &r) { return r < l; }
    };

    static void compress();

    static void expand();
};


#endif //ALGS4_HUFFMAN_H