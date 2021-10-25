#pragma once

#include <utility>

#include "Point.hpp"
#include "TransformationMatrix.hpp"
#include "util.hpp"

template <unsigned n>
class GeometricTransform {
   private:
    const static unsigned _dim = n;
    TransformationMatrix<n> _mat;

   public:
    GeometricTransform() : _mat{} { _mat(_dim, _dim) = 1.; }
    GeometricTransform(const TransformationMatrix<n>& mat) : _mat{mat} {
        _mat(_dim, _dim) = 1.;
    }
    GeometricTransform(TransformationMatrix<n>&& mat) : _mat{std::move(mat)} {
        _mat(_dim, _dim) = 1.;
    }

    double& operator()(unsigned row, unsigned col) { return _mat(row, col); }
    double operator()(unsigned row, unsigned col) const {
        return _mat(row, col);
    }

    Point<n> operator()(Point<n> pt) {
        pt._coords = _mat * (pt._coords);
        return pt;
    }

    GeometricTransform operator-() {
        // TODO
    }

    template <typename... Ts>
    friend GeometricTransform composite(Ts&&... ts) {
        return GeometricTransform{(... * ts._mat)};
    }
};

template <typename Matrix,
          std::size_t... RowInd,
          std::size_t... ColInd,
          typename... Vals>
void matrix_fill(Matrix& mat,
                 std::index_sequence<RowInd...>,
                 std::index_sequence<ColInd...>,
                 Vals... vals) {
    ((mat(RowInd, ColInd) = vals), ...);
}

// No ambiguity in this overload? Maybe due to SFINAE.
template <typename Matrix, std::size_t... RowInd, std::size_t... ColInd>
void matrix_fill(Matrix& mat,
                 std::index_sequence<RowInd...>,
                 std::index_sequence<ColInd...>,
                 double val) {
    ((mat(RowInd, ColInd) = val), ...);
}

template <typename... Args, typename Indices = std::index_sequence_for<Args...>>
auto scalingTransform(Args... args) {
    GeometricTransform<sizeof...(Args)> t{};
    matrix_fill(t, Indices{}, Indices{}, args...);
    return t;
}

template <typename... Args,
          typename Indices = std::index_sequence_for<Args...>,
          typename ConstIndices =
              const_index_sequence<sizeof...(Args), sizeof...(Args)>>
auto translationTransform(Args... args) {
    GeometricTransform<sizeof...(Args)> t{};
    matrix_fill(t, Indices{}, Indices{}, 1.);
    matrix_fill(t, Indices{}, ConstIndices{}, args...);
    return t;
}
