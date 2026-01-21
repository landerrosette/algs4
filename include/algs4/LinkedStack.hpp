/*
 * Copyright (C) 2026 landerrosette <57791410+landerrosette@users.noreply.github.com>
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

#ifndef ALGS4_LINKEDSTACK_HPP
#define ALGS4_LINKEDSTACK_HPP

#include <cassert>
#include <concepts>
#include <iterator>
#include <memory>
#include <type_traits>
#include <utility>

namespace algs4 {
    template<std::movable T>
    class LinkedStack {
    private:
        struct Node {
            T item_;
            std::unique_ptr<Node> next_;

            Node(T item, std::unique_ptr<Node> next) : item_(std::move(item)), next_(std::move(next)) {}
        };

        std::unique_ptr<Node> first_;
        std::ptrdiff_t N_ = 0;

        template<bool Const>
        class Iterator {
            friend class Iterator<!Const>;

        private:
            std::conditional_t<Const, const Node *, Node *> current_ = nullptr;

        public:
            using iterator_category = std::forward_iterator_tag;
            using iterator_concept = std::forward_iterator_tag;
            using value_type = std::remove_cv_t<T>;
            using difference_type = std::ptrdiff_t;
            using pointer = std::conditional_t<Const, const T *, T *>;
            using reference = std::conditional_t<Const, const T &, T &>;

            constexpr Iterator() = default;
            constexpr explicit Iterator(std::conditional_t<Const, const Node *, Node *> curr) : current_(curr) {}

            template<bool OtherConst> requires (Const && !OtherConst)
            constexpr Iterator(const Iterator<OtherConst> &other) : current_(other.current_) {}

            constexpr reference operator*() const { return current_->item_; }
            constexpr pointer operator->() const { return &current_->item_; }
            constexpr Iterator &operator++();
            constexpr Iterator operator++(int);
            friend constexpr bool operator==(const Iterator &l, const Iterator &r) { return l.current_ == r.current_; }
        };

    public:
        using iterator = Iterator<false>;
        using const_iterator = Iterator<true>;

        bool isEmpty() const { return N_ == 0; }
        std::ptrdiff_t size() const { return N_; }

        template<std::convertible_to<T> U>
        void push(U &&item);

        T pop();

        iterator begin() { return iterator(first_.get()); }
        iterator end() { return iterator(nullptr); }
        const_iterator begin() const { return const_iterator(first_.get()); }
        const_iterator end() const { return const_iterator(nullptr); }
        const_iterator cbegin() const { return const_iterator(first_.get()); }
        const_iterator cend() const { return const_iterator(nullptr); }
    };
}

template<std::movable T>
template<std::convertible_to<T> U>
void algs4::LinkedStack<T>::push(U &&item) {
    first_ = std::make_unique<Node>(std::forward<U>(item), std::move(first_));
    ++N_;
}

template<std::movable T>
T algs4::LinkedStack<T>::pop() {
    assert(!isEmpty());
    T item = std::move(first_->item_);
    first_ = std::move(first_->next_);
    --N_;
    return item;
}

template<std::movable T>
template<bool Const>
constexpr auto algs4::LinkedStack<T>::Iterator<Const>::operator++() -> Iterator & {
    current_ = current_->next_.get();
    return *this;
}

template<std::movable T>
template<bool Const>
constexpr auto algs4::LinkedStack<T>::Iterator<Const>::operator++(int) -> Iterator {
    Iterator t = *this;
    ++*this;
    return t;
}

#endif // ALGS4_LINKEDSTACK_HPP
