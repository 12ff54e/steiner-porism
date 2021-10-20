#pragma once

#include <array>
#include <iostream>

template <unsigned n>
class Point {
   private:
    std::array<double, n> coords;
    unsigned const _dim = n;

   public:
    template <typename... Ts>
    Point(Ts... vals) : coords{vals...} {}

    unsigned dim() const { return _dim; }

    // element access

    double& operator[](unsigned i) { return coords[i]; }

    auto begin() { return coords.begin(); }
    auto end() { return coords.end(); }
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