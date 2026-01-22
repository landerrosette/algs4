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

#ifndef ALGS4_MONODIRECTIONALITERATOR_HPP
#define ALGS4_MONODIRECTIONALITERATOR_HPP

#include <concepts>
#include <iterator>
#include <utility>

namespace algs4 {
    namespace detail {
        template<std::forward_iterator Iter>
        class MonodirectionalIterator {
            template<std::forward_iterator I>
            friend class MonodirectionalIterator;

        private:
            Iter current_;

        public:
            using iterator_type = Iter;
            using iterator_category = std::forward_iterator_tag;
            using iterator_concept = std::forward_iterator_tag;
            using value_type = std::iter_value_t<Iter>;
            using difference_type = std::iter_difference_t<Iter>;
            using pointer = std::iterator_traits<Iter>::pointer;
            using reference = std::iter_reference_t<Iter>;

            constexpr MonodirectionalIterator() = default;
            constexpr explicit MonodirectionalIterator(iterator_type i) : current_(std::move(i)) {}

            template<std::forward_iterator I>
                requires (!std::is_same_v<I, Iter> && std::convertible_to<const I &, Iter>)
            constexpr MonodirectionalIterator(const MonodirectionalIterator<I> &other) : current_(other.current_) {}

            constexpr iterator_type base() const { return current_; }
            constexpr reference operator*() const { return *current_; }
            constexpr decltype(auto) operator->() const
                requires std::is_pointer_v<Iter> || requires(const Iter i) { i.operator->(); };
            constexpr MonodirectionalIterator &operator++();
            constexpr MonodirectionalIterator operator++(int);

            template<std::sentinel_for<Iter> S>
            friend constexpr bool operator==(const MonodirectionalIterator &i, const S &s) { return i.base() == s; }
        };

        template<std::forward_iterator IterL, std::forward_iterator IterR>
            requires std::equality_comparable_with<IterL, IterR>
        constexpr bool operator==(const MonodirectionalIterator<IterL> &l, const MonodirectionalIterator<IterR> &r);

        template<std::forward_iterator Iter>
        constexpr decltype(auto) iter_move(const MonodirectionalIterator<Iter> &i)
            noexcept(noexcept(std::ranges::iter_move(i.base())));

        template<std::forward_iterator IterL, std::forward_iterator IterR>
            requires std::indirectly_swappable<IterL, IterR>
        constexpr void iter_swap(const MonodirectionalIterator<IterL> &l, const MonodirectionalIterator<IterR> &r)
            noexcept(noexcept(std::ranges::iter_swap(l.base(), r.base())));
    }
}

template<std::forward_iterator Iter>
constexpr decltype(auto) algs4::detail::MonodirectionalIterator<Iter>::operator->() const
    requires std::is_pointer_v<Iter> || requires(const Iter i) { i.operator->(); } {
    if constexpr (std::is_pointer_v<Iter>)
        return current_;
    else
        return current_.operator->();
}

template<std::forward_iterator Iter>
constexpr auto algs4::detail::MonodirectionalIterator<Iter>::operator++() -> MonodirectionalIterator & {
    ++current_;
    return *this;
}

template<std::forward_iterator Iter>
constexpr auto algs4::detail::MonodirectionalIterator<Iter>::operator++(int) -> MonodirectionalIterator {
    MonodirectionalIterator t = *this;
    ++*this;
    return t;
}

template<std::forward_iterator IterL, std::forward_iterator IterR>
    requires std::equality_comparable_with<IterL, IterR>
constexpr bool algs4::detail::operator==(const MonodirectionalIterator<IterL> &l,
                                         const MonodirectionalIterator<IterR> &r) {
    return l.base() == r.base();
}

template<std::forward_iterator Iter>
constexpr decltype(auto) algs4::detail::iter_move(const MonodirectionalIterator<Iter> &i)
    noexcept(noexcept(std::ranges::iter_move(i.base()))) {
    return std::ranges::iter_move(i.base());
}

template<std::forward_iterator IterL, std::forward_iterator IterR> requires std::indirectly_swappable<IterL, IterR>
constexpr void algs4::detail::iter_swap(const MonodirectionalIterator<IterL> &l,
                                        const MonodirectionalIterator<IterR> &r)
    noexcept(noexcept(std::ranges::iter_swap(l.base(), r.base()))) {
    std::ranges::iter_swap(l.base(), r.base());
}

#endif // ALGS4_MONODIRECTIONALITERATOR_HPP
