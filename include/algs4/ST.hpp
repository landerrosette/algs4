#ifndef ALGS4_ST_HPP
#define ALGS4_ST_HPP


#include <cstddef>
#include <vector>

namespace algs4 {
    template<typename Key, typename Value>
    class ST {
    protected:
        ST() = default;
        ST(const ST &) = default;
        ST &operator=(const ST &) = default;
        ST(ST &&) noexcept = default;
        ST &operator=(ST &&) noexcept = default;

    public:
        virtual ~ST() = default;

        virtual const Value *get(const Key &key) const = 0;
        Value *get(const Key &key) { return const_cast<Value *>(std::as_const(*this).get(key)); }
        virtual void put(Key key, Value val) = 0;
        virtual void remove(const Key &key) = 0;
        bool contains(const Key &key) const { return get(key) != nullptr; }
        bool isEmpty() const { return size() == 0; }
        virtual std::ptrdiff_t size() const = 0;
        virtual std::vector<Key> keys() const = 0;
    };
}


#endif //ALGS4_ST_HPP
