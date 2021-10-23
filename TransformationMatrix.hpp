#pragma once

#include <array>
#include <utility>
#include "Point.hpp"

template <unsigned n>
class TransformationMatrix {
   private:
    const static unsigned _dim = n + 1;
    // This array will be zero-initialized, when the class has trivial
    // implicitly-defined or defaulted default constructor.
    std::array<double, (n + 1) * (n + 1)> _mat_elems;

   public:
    TransformationMatrix() { _mat_elems.fill(0.); }

    inline unsigned dim() const { return _dim; }

    // element access

    double& operator()(unsigned row, unsigned col) {
        return _mat_elems[row * _dim + col];
    }

    Coord<n> operator*(Coord<n> coord) {
        unsigned last_row = _dim * (_dim - 1);
        for (unsigned i = 0; i < _dim - 1; ++i) {
            for (unsigned j = 0; j < _dim; ++j) {
                // buffer the product in last row of matrix, which is of no use.
                _mat_elems[last_row] += operator()(i, j) *
                                        (j < _dim - 1 ? coord[j] : 1.);
            }
            ++last_row;
        }
        last_row = _dim * (_dim - 1);
        for (unsigned i = 0; i < _dim - 1; ++i) {
            coord[i] = std::exchange(_mat_elems[last_row++], 0.);
        }
        return coord;
    }
};

template <unsigned n>
TransformationMatrix<n> operator*(TransformationMatrix<n> t1,
                                  TransformationMatrix<n> t2) {
    TransformationMatrix<n> t{};
    for (unsigned i = 0; i < t.dim(); ++i) {
        for (unsigned j = 0; j < t.dim(); ++j) {
            for (unsigned k = 0; k < t.dim(); ++k) {
                t(i, j) += t1(i, k) * t2(k, j);
            }
        }
    }
    return t;
}