#pragma once

#include <cstddef>
#include <type_traits>
#include <utility>

template <typename T, std::size_t N, T C, T... Cs>
struct const_integer_seq_impl : const_integer_seq_impl<T, N - 1, C, C, Cs...> {
};
template <typename T, T C, T... Cs>
struct const_integer_seq_impl<T, 0, C, Cs...> {
    using type = std::integer_sequence<T, Cs...>;
};

template <typename T, std::size_t N, T C = T{0}>
using const_integer_sequence = typename const_integer_seq_impl<T, N, C>::type;

template <std::size_t N, std::size_t C = std::size_t{0}>
using const_index_sequence = const_integer_sequence<std::size_t, N, C>;
