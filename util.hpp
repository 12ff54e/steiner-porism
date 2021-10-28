#pragma once

#include <array>
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

/**
 * @brief levi-civita symbol
 *
 * @tparam Args
 * @param args any combination of int 0,...,N-1 (N is the size of Args)
 * @return constexpr int
 */
template <typename... Args>
constexpr int leviCivita(Args... args) {
    std::array<int, sizeof...(Args)> arr{args...};
    int lc = 1;

    for (int i = 0; i < arr.size(); ++i) {
        while (arr[i] != i) {
            if (arr[i] == arr[arr[i]]) { return 0; }
            int tmp = arr[i];
            arr[i] = arr[tmp];
            arr[tmp] = tmp;
            lc = -lc;
        }
    }
    return lc;
}

/**
 * @brief Kronecker delta symbol, evaluate to true if all parameters are the
 * same.
 *
 * @tparam T Type of 1st parameter
 * @tparam Args Types of rest parameters, should be convertable to T, or at
 * least can be comparable to T
 * @param v 1st paremeter
 * @param args other parameters
 * @return constexpr bool
 */
template <typename T, typename... Args>
constexpr bool kroneckerDelta(T v, Args... args) {
    return (... && (v == args));
}
