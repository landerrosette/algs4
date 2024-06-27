#ifndef ALGS4_ST_H
#define ALGS4_ST_H


#include <deque>

template<typename Key, typename Value>
class ST {
public:
    virtual Value get(Key key) = 0;

    virtual void put(Key key, Value val) = 0;

    virtual std::deque<Key> getKeys() = 0;

    virtual ~ST() = default;
};


#endif //ALGS4_ST_H
