#ifndef ALGS4_ST_H
#define ALGS4_ST_H


#include <deque>
#include <optional>

template <typename Key, typename Value>
class ST {
public:
    virtual ~ST() = default;

    virtual std::optional<Value> get(const Key& key) const = 0;

    virtual void put(const Key& key, const Value& val) = 0;

    virtual void remove(const Key& key) = 0;

    bool contains(const Key& key) const { return get(key).has_value(); }

    bool isEmpty() const { return size() == 0; }

    virtual int size() const = 0;

    virtual std::deque<Key> keys() const = 0;
};


#endif //ALGS4_ST_H
