#ifndef TST_H
#define TST_H


#include <memory>
#include <optional>

#include "StringST.h"

template<typename Value>
class TST : public StringST<Value> {
private:
    int N = 0;

    struct Node {
        char c;
        std::unique_ptr<Node> left, mid, right;
        std::optional<Value> val;

        explicit Node(char c) : c(c) {}
    };

    std::unique_ptr<Node> root;

    const Node *get(const Node *x, std::string_view key, int d) const;

    std::unique_ptr<Node> put(std::unique_ptr<Node> &x, std::string_view key, const Value &val, int d);

    std::unique_ptr<Node> remove(std::unique_ptr<Node> &x, std::string_view key, int d);

    void collect(const Node *x, const std::string &pre, std::list<std::string> &q) const;

    void collect(const Node *x, const std::string &pre, std::string_view pat, std::list<std::string> &q) const;

    int search(const Node *x, std::string_view s, int d, int length) const;

    std::unique_ptr<Node> min(std::unique_ptr<Node> &x);

public:
    std::optional<Value> get(const std::string &key) const override;

    void put(const std::string &key, const Value &val) override { root = put(root, key, val, 0); }

    void remove(const std::string &key) override { root = remove(root, key, 0); }

    int size() const override { return N; }

    std::list<std::string> keys() const override;

    std::string longestPrefixOf(std::string_view s) const override;

    std::list<std::string> keysWithPrefix(const std::string &pre) const override;

    std::list<std::string> keysThatMatch(std::string_view pat) const override;
};

template<typename Value>
const typename TST<Value>::Node *TST<Value>::get(const Node *x, std::string_view key, int d) const {
    if (!x) return nullptr;
    char c = key[d];
    if (c < x->c) return get(x->left.get(), key, d);
    else if (c > x->c) return get(x->right.get(), key, d);
    else if (d < key.length() - 1) return get(x->mid.get(), key, d + 1);
    else return x;
}

template<typename Value>
std::unique_ptr<typename TST<Value>::Node> TST<Value>::put(std::unique_ptr<Node> &x, std::string_view key,
                                                           const Value &val, int d) {
    char c = key[d];
    if (!x) x = std::make_unique<Node>(c);
    if (c < x->c) x->left = put(x->left, key, val, d);
    else if (c > x->c) x->right = put(x->right, key, val, d);
    else if (d < key.length() - 1) x->mid = put(x->mid, key, val, d + 1);
    else {
        if (!x->val) ++N;
        x->val = val;
    }
    return std::move(x);
}

template<typename Value>
std::unique_ptr<typename TST<Value>::Node> TST<Value>::remove(std::unique_ptr<Node> &x, std::string_view key, int d) {
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
        if (!x->right) return std::move(x->left);
        if (!x->left) return std::move(x->right);
        auto t = std::move(x);
        x = min(t->right);
        x->right = std::move(t->right);
        x->left = std::move(t->left);
    }
    return std::move(x);
}

template<typename Value>
void TST<Value>::collect(const Node *x, const std::string &pre, std::list<std::string> &q) const {
    if (!x) return;
    collect(x->left.get(), pre, q);
    if (x->val) q.push_back(pre + x->c);
    collect(x->mid.get(), pre + x->c, q);
    collect(x->right.get(), pre, q);
}

template<typename Value>
void TST<Value>::collect(const Node *x, const std::string &pre, std::string_view pat, std::list<std::string> &q) const {
    if (!x) return;
    int d = pre.length();
    char next = pat[d];
    if (next == '.' || next < x->c) collect(x->left.get(), pre, pat, q);
    if (next == '.' || next == x->c) {
        if (d == pat.length() - 1 && x->val) q.push_back(pre + x->c);
        if (d < pat.length() - 1) collect(x->mid.get(), pre + x->c, pat, q);
    }
    if (next == '.' || next > x->c) collect(x->right.get(), pre, pat, q);
}

template<typename Value>
int TST<Value>::search(const Node *x, std::string_view s, int d, int length) const {
    if (!x) return length;
    char c = s[d];
    if (c < x->c) return search(x->left.get(), s, d, length);
    else if (c > x->c) return search(x->right.get(), s, d, length);
    else {
        if (x->val) length = d + 1;
        if (d == s.length() - 1) return length;
        return search(x->mid.get(), s, d + 1, length);
    }
}

template<typename Value>
std::unique_ptr<typename TST<Value>::Node> TST<Value>::min(std::unique_ptr<Node> &x) {
    if (!x) return nullptr;
    if (!x->left) {
        auto min = std::move(x);
        x = std::move(min->right);
        return min;
    }
    return min(x->left);
}

template<typename Value>
std::optional<Value> TST<Value>::get(const std::string &key) const {
    const Node *x = get(root.get(), key, 0);
    if (!x) return std::nullopt;
    return x->val;
}

template<typename Value>
std::list<std::string> TST<Value>::keys() const {
    // return keysWithPrefix(""); // Passing an empty key to get() is undefined.
    std::list<std::string> q;
    collect(root.get(), "", q);
    return q;
}

template<typename Value>
std::string TST<Value>::longestPrefixOf(std::string_view s) const {
    int length = search(root.get(), s, 0, 0);
    return std::string(s.substr(0, length));
}

template<typename Value>
std::list<std::string> TST<Value>::keysWithPrefix(const std::string &pre) const {
    std::list<std::string> q;
    if (const Node *x = get(root.get(), pre, 0)) {
        if (x->val) q.push_back(pre);
        collect(x->mid.get(), pre, q);
    }
    return q;
}

template<typename Value>
std::list<std::string> TST<Value>::keysThatMatch(std::string_view pat) const {
    std::list<std::string> q;
    collect(root.get(), "", pat, q);
    return q;
}


#endif //TST_H
