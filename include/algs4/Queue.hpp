/*
 * Copyright (C) 2026 landerrosette
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

#include "IteratorWrapper.hpp"

namespace algs4 {
    template<typename T>
    class Queue {
    private:
        std::deque<T> a_;

    public:
        using iterator = internal::IteratorWrapper<std::deque<T>, false, false>;
        using const_iterator = internal::IteratorWrapper<std::deque<T>, false, true>;

        bool isEmpty() const { return a_.empty(); }
        std::ptrdiff_t size() const { return std::ssize(a_); }

        template<typename U> requires std::constructible_from<T, U>
        void enqueue(U &&item) { a_.emplace_back(std::forward<U>(item)); }

        T dequeue();
        iterator begin() { return iterator(a_.begin()); }
        iterator end() { return iterator(a_.end()); }
        const_iterator begin() const { return const_iterator(a_.begin()); }
        const_iterator end() const { return const_iterator(a_.end()); }
        const_iterator cbegin() const { return const_iterator(a_.cbegin()); }
        const_iterator cend() const { return const_iterator(a_.cend()); }
    };
}

template<typename T>
T algs4::Queue<T>::dequeue() {
    assert(!isEmpty());
    T item = std::move(a_.front());
    a_.pop_front();
    return item;
}

#endif // ALGS4_QUEUE_HPP
