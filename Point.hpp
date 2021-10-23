#pragma once

#include <array>
#include <iostream>

template <unsigned n>
using Coord = std::array<double, n>;

template <unsigned n>
class Point {
   private:
    static unsigned const _dim = n;
    Coord<n> _coords;

   public:
    template <typename... Ts>
    Point(Ts... vals) : _coords{vals...} {}

    unsigned dim() const { return _dim; }

    // element access

    double& operator[](unsigned i) { return _coords[i]; }

    auto begin() { return _coords.begin(); }
    auto end() { return _coords.end(); }
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