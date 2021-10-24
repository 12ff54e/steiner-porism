#include <algorithm>
#include <iostream>
#include <iterator>

#include "../GeometricTransform.hpp"
#include "../Point.hpp"

using namespace std;
int main() {
    Point pt{6., 2., 7.};
    cout << "Components of " << pt.dim() << "D Point " << pt << " are:\n";
    for (auto&& x : pt) { cout << x << '\n'; };

    GeometricTransform<3> t1;
    GeometricTransform<3> t2;
    t1(0, 0) = 1.;
    t1(1, 1) = 2.;
    t1(2, 2) = 4.;
    t1(3, 3) = 1.;

    t2(0, 0) = t2(1, 1) = t2(2, 2) = t2(3, 3) = 1.;
    t2(0, 3) = 3.;
    t2(1, 3) = 4.;
    t2(2, 3) = 5.;

    auto pp = t1(pt);
    copy(pp.begin(), pp.end(), ostream_iterator<double>(cout, ", "));
    cout << '\n';
    pp = t2(pt);
    copy(pp.begin(), pp.end(), ostream_iterator<double>(cout, ", "));

    return 0;
}