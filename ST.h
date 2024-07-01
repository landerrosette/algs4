#ifndef ALGS4_ST_H
#define ALGS4_ST_H


#include <deque>

template<typename Key, typename Value>
class ST {
public:
    virtual Value get(const Key &key) const = 0;

    virtual void put(const Key &key, const Value &val) = 0;

    virtual void remove(const Key &key) = 0;

    bool contains(const Key &key) const {
        return get(key) != Value();
    }

    bool isEmpty() const {
        return size() == 0;
    }

    virtual int size() const = 0;

    virtual std::deque<Key> getKeys() const = 0;
};


#endif //ALGS4_ST_H
