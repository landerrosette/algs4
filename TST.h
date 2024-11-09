#ifndef TST_H
#define TST_H


#include "StringST.h"
#include <memory>
#include <optional>

template<typename Value>
class TST : public StringST<Value> {
private:
    int N = 0;

    struct Node {
        char c;
        std::shared_ptr<Node> left, mid, right;
        std::optional<Value> val;

        Node(char c) : c(c) {}
    };

    std::shared_ptr<Node> root;

    std::shared_ptr<Node> get(std::shared_ptr<Node> x, const std::string &key, int d) const;

    std::shared_ptr<Node> put(std::shared_ptr<Node> x, const std::string &key, const Value &val, int d);

    std::shared_ptr<Node> remove(std::shared_ptr<Node> x, const std::string &key, int d);

    void collect(std::shared_ptr<Node> x, const std::string &pre, std::list<std::string> &q) const;

    void collect(std::shared_ptr<Node> x, const std::string &pre, const std::string &pat,
                 std::list<std::string> &q) const;

    int search(std::shared_ptr<Node> x, const std::string &s, int d, int length) const;

    std::shared_ptr<Node> min(std::shared_ptr<Node> x) const;

    std::shared_ptr<Node> removeMin(std::shared_ptr<Node> x);

public:
    std::optional<Value> get(const std::string &key) const override;

    void put(const std::string &key, const Value &val) override { root = put(root, key, val, 0); }

    void remove(const std::string &key) override { root = remove(root, key, 0); }

    int size() const override { return N; }

    std::list<std::string> keys() const override { return keysWithPrefix(""); }

    std::string longestPrefixOf(const std::string &s) const override;

    std::list<std::string> keysWithPrefix(const std::string &pre) const override;

    std::list<std::string> keysThatMatch(const std::string &pat) const override;
};

template<typename Value>
std::shared_ptr<typename TST<Value>::Node> TST<
    Value>::get(std::shared_ptr<Node> x, const std::string &key, int d) const {
    if (!x) return nullptr;
    if (key.empty()) {
        auto preRoot = std::make_shared<Node>('\0');
        preRoot->mid = root;
        return preRoot;
    }
    char c = key[d];
    if (c < x->c) return get(x->left, key, d);
    else if (c > x->c) return get(x->right, key, d);
    else if (d < key.length() - 1) return get(x->mid, key, d + 1);
    else return x;
}

template<typename Value>
std::shared_ptr<typename TST<Value>::Node> TST<Value>::put(std::shared_ptr<Node> x, const std::string &key,
                                                           const Value &val, int d) {
    char c = key[d];
    if (!x) x = std::make_shared<Node>(c);
    if (c < x->c) x->left = put(x->left, key, val, d);
    else if (c > x->c) x->right = put(x->right, key, val, d);
    else if (d < key.length() - 1) x->mid = put(x->mid, key, val, d + 1);
    else {
        if (!x->val) ++N;
        x->val = val;
    }
    return x;
}

template<typename Value>
std::shared_ptr<typename TST<Value>::Node> TST<Value>::remove(std::shared_ptr<Node> x, const std::string &key, int d) {
    if (!x) return nullptr;
    char c = key[d];
    if (c < x->c) x->left = remove(x->left, key, d);
    else if (c > x->c) x->right = remove(x->right, key, d);
    else if (d < key.length() - 1) x->mid = remove(x->mid, key, d + 1);
    else {
        if (x->val) --N;
        x->val = std::nullopt;
    }

    if (!x->mid && !x->val) {
        if (!x->right) return x->left;
        if (!x->left) return x->right;
        auto t = x;
        x = min(t->right);
        x->right = removeMin(t->right);
        x->left = t->left;
    }
    return x;
}

template<typename Value>
void TST<Value>::collect(std::shared_ptr<Node> x, const std::string &pre, std::list<std::string> &q) const {
    if (!x) return;
    collect(x->left, pre, q);
    if (x->val) q.push_back(pre + x->c);
    collect(x->mid, pre + x->c, q);
    collect(x->right, pre, q);
}

template<typename Value>
void TST<Value>::collect(std::shared_ptr<Node> x, const std::string &pre, const std::string &pat,
                         std::list<std::string> &q) const {
    if (!x) return;
    int d = pre.length();
    char next = pat[d];
    if (next == '.' || next < x->c) collect(x->left, pre, pat, q);
    if (next == '.' || next == x->c) {
        if (d == pat.length() - 1 && x->val) q.push_back(pre + x->c);
        if (d < pat.length() - 1) collect(x->mid, pre + x->c, pat, q);
    }
    if (next == '.' || next > x->c) collect(x->right, pre, pat, q);
}

template<typename Value>
int TST<Value>::search(std::shared_ptr<Node> x, const std::string &s, int d, int length) const {
    if (!x) return length;
    char c = s[d];
    if (c < x->c) return search(x->left, s, d, length);
    else if (c > x->c) return search(x->right, s, d, length);
    else {
        if (x->val) length = d + 1;
        if (d == s.length() - 1) return length;
        return search(x->mid, s, d + 1, length);
    }
}

template<typename Value>
std::shared_ptr<typename TST<Value>::Node> TST<Value>::min(std::shared_ptr<Node> x) const {
    if (!x) return nullptr;
    if (!x->left) return x;
    return min(x->left);
}

template<typename Value>
std::shared_ptr<typename TST<Value>::Node> TST<Value>::removeMin(std::shared_ptr<Node> x) {
    if (!x) return nullptr;
    if (!x->left) return x->right;
    x->left = removeMin(x->left);
    return x;
}

template<typename Value>
std::optional<Value> TST<Value>::get(const std::string &key) const {
    auto x = get(root, key, 0);
    if (!x) return std::nullopt;
    return x->val;
}

template<typename Value>
std::string TST<Value>::longestPrefixOf(const std::string &s) const {
    int length = search(root, s, 0, 0);
    return s.substr(0, length);
}

template<typename Value>
std::list<std::string> TST<Value>::keysWithPrefix(const std::string &pre) const {
    std::list<std::string> q;
    auto x = get(root, pre, 0);
    if (x) {
        if (x->val) q.push_back(pre);
        collect(x->mid, pre, q);
    }
    return q;
}

template<typename Value>
std::list<std::string> TST<Value>::keysThatMatch(const std::string &pat) const {
    std::list<std::string> q;
    collect(root, "", pat, q);
    return q;
}


#endif //TST_H
