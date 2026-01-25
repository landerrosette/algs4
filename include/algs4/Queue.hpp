/*
 * Copyright (C) 2026  landerrosette <57791410+landerrosette@users.noreply.github.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef ALGS4_QUEUE_HPP
#define ALGS4_QUEUE_HPP

#include <cassert>
#include <concepts>
#include <deque>
#include <utility>

#include "MonodirectionalIterator.hpp"

namespace algs4 {
template <std::movable T>
class Queue {
private:
    std::deque<T> a_;

public:
    using iterator = detail::MonodirectionalIterator<typename std::deque<T>::iterator>;
    using const_iterator = detail::MonodirectionalIterator<typename std::deque<T>::const_iterator>;

    bool isEmpty() const { return a_.empty(); }
    std::ptrdiff_t size() const { return std::ssize(a_); }

    template <std::convertible_to<T> U>
    void enqueue(U&& item) {
        a_.emplace_back(std::forward<U>(item));
    }

    T dequeue() {
        assert(!isEmpty());
        T item = std::move(a_.front());
        a_.pop_front();
        return item;
    }

    iterator begin() { return iterator(a_.begin()); }
    iterator end() { return iterator(a_.end()); }
    const_iterator begin() const { return const_iterator(a_.begin()); }
    const_iterator end() const { return const_iterator(a_.end()); }
    const_iterator cbegin() const { return const_iterator(a_.cbegin()); }
    const_iterator cend() const { return const_iterator(a_.cend()); }
};
}  // namespace algs4

#endif  // ALGS4_QUEUE_HPP
