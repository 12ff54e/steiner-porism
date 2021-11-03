#pragma once

#include <array>
#include <cstddef>
#include <utility>

#include "GeometricTransform.hpp"
#include "Point.hpp"

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
    std::array<unsigned, sizeof...(Args)> arr{args...};
    int lc = 1;

    for (unsigned i = 0; i < arr.size(); ++i) {
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

/**
 * @brief Stereographic projection from nD point on unit sphere to (n-1)D plane
 *
 * @tparam n
 * @param pt
 * @return Point<n-1>
 */
template <unsigned n>
constexpr auto stereographicProjection(const Point<n>& pt) {
    Point<n - 1> proj{};
    const auto c = 1 / (1. - pt[n - 1]);
    for (unsigned i = 0; i < proj.dim(); ++i) { proj[i] = c * pt[i]; }
    return proj;
}

/**
 * @brief Inverse stereographic projection from (n-1)D plane to nD point on unit
 * sphere
 *
 * @tparam n
 * @param pt
 * @return Point<n>
 */
template <unsigned n>
constexpr auto stereographicProjection(const Point<n - 1>& pt) {
    double c = 1.;
    for (auto&& x : pt) { c += x * x; }
    c = 2. / c;

    Point<n> proj;
    for (unsigned i = 0; i < pt.dim(); ++i) { proj[i] = c * pt[i]; }
    proj[n - 1] = 1 - c;

    return proj;
}

auto circleThrough(const Point<2>& p1, const Point<2>& p2, const Point<2>& p3) {
    const double d1x = p2[0] - p3[0], d2x = p3[0] - p1[0], d3x = p1[0] - p2[0];
    const double d1y = p2[1] - p3[1], d2y = p3[1] - p1[1], d3y = p1[1] - p2[1];
    const double denom_inv = 0.5 / (p1[0] * d1y + p2[0] * d2y + p3[0] * d3y);

    const double x =
        0.5 * (p1[0] + p2[0]) - d3y * (d1x * d2x + d1y * d2y) * denom_inv;
    const double y =
        0.5 * (p1[1] + p2[1]) + d3x * (d1x * d2x + d1y * d2y) * denom_inv;
    const double r = sqrt((d1x * d1x + d1y * d1y) * (d2x * d2x + d2y * d2y) *
                          (d3x * d3x + d3y * d3y)) *
                     std::abs(denom_inv);

    return std::make_pair(Point<2>{x, y}, r);
}
