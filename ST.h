#ifndef ALGS4_ST_H
#define ALGS4_ST_H


#include <vector>

template<typename Key, typename Value>
class ST {
public:
    virtual Value get(Key key) = 0;

    virtual void put(Key key, Value val) = 0;

    virtual std::vector<Key> keys() = 0;

    virtual ~ST() = default;
};


#endif //ALGS4_ST_H
