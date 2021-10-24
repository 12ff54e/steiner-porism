#pragma once

#include "Point.hpp"
#include "TransformationMatrix.hpp"

template <unsigned n>
class GeometricTransform {
   private:
    const static unsigned _dim = n;
    TransformationMatrix<n> _mat;

   public:
    GeometricTransform() : _mat{} {}

    double& operator()(unsigned row, unsigned col) { return _mat(row, col); }
    double operator()(unsigned row, unsigned col) const {
        return _mat(row, col);
    }

    Point<n> operator()(Point<n> pt) {
        pt._coords = _mat * (pt._coords);
        return pt;
    }
};
