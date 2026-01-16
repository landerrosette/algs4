#ifndef ALGS4_ST_HPP
#define ALGS4_ST_HPP

#include <cstddef>
#include <utility>
#include <vector>

namespace algs4 {
    template<typename Key, typename Value>
    class ST {
    protected:
        constexpr ST() = default;
        constexpr ST(const ST &) = default;
        constexpr ST &operator=(const ST &) = default;
        constexpr ST(ST &&) noexcept = default;
        constexpr ST &operator=(ST &&) noexcept = default;

    public:
        virtual constexpr ~ST() = default;

        virtual constexpr const Value *get(const Key &key) const = 0;
        constexpr Value *get(const Key &key) { return const_cast<Value *>(std::as_const(*this).get(key)); }
        virtual constexpr void put(Key key, Value val) = 0;
        virtual constexpr void remove(const Key &key) = 0;
        constexpr bool contains(const Key &key) const { return get(key) != nullptr; }
        constexpr bool isEmpty() const { return size() == 0; }
        virtual constexpr std::ptrdiff_t size() const = 0;
        virtual constexpr std::vector<Key> keys() const = 0;
    };
}

#endif // ALGS4_ST_HPP
