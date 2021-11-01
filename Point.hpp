#pragma once

#include <array>
#include <cmath>
#include <iostream>

template <unsigned n>
using Coord = std::array<double, n>;

template <unsigned n>
class GeometricTransform;

template <unsigned n>
class Point {
   private:
    const static unsigned _dim = n;
    Coord<n> _coords;

   public:
    template <typename... Ts>
    constexpr Point(Ts... vals) : _coords{vals...} {}

    constexpr unsigned dim() const { return _dim; }

    //

    constexpr double norm() const {
        double ss = 0;
        for (auto&& x : _coords) { ss += x * x; }
        return sqrt(ss);
    }

    constexpr Point& normalize() {
        auto l2n = norm();
        for (auto&& x : _coords) { x /= l2n; }
        return *this;
    }

    constexpr Point normalize() const {
        auto pt = *this;
        pt.normalize();
        return pt;
    }

    // element access

    constexpr double& operator[](unsigned i) { return _coords[i]; }
    constexpr double operator[](unsigned i) const { return _coords[i]; }

    auto begin() { return _coords.begin(); }
    auto begin() const { return _coords.begin(); }
    auto end() { return _coords.end(); }
    auto end() const { return _coords.end(); }

    friend Point GeometricTransform<n>::operator()(Point);
};

template <typename... Ts>
Point(Ts...) -> Point<sizeof...(Ts)>;

template <unsigned n>
std::ostream& operator<<(std::ostream& os, Point<n> pt) {
    os << "(";
    for (unsigned i = 0; i < pt.dim(); ++i) {
        os << pt[i] << (i == pt.dim() - 1 ? ")" : ", ");
    }
    return os;
}