#include <algorithm>
#include <iostream>
#include <iterator>

#include "../GeometricTransform.hpp"
#include "../Point.hpp"
#include "../util.hpp"

using namespace std;
int main() {
    Point pt{6., 2., 7.};
    cout << "A " << pt.dim() << "D Point " << pt << "\n";

    auto t1 = scalingTransform(1., 2., 4.);
    auto t2 = translationTransform(3., 4., 5.);

    cout << "...After scaling: ";
    for (auto&& x : t1(pt)) { cout << x << ' '; };
    cout << '\n';
    cout << "...After translate-scale-translate transfrom: ";
    for (auto&& x : composite(t2, t1, t2)(pt)) { cout << x << ' '; };
    cout << '\n';

    // Random generated tests for Levi-Civita symbol and Kronecker delta

    static_assert(leviCivita(2, 4, 5, 7, 3, 1, 0, 6) == -1);
    static_assert(leviCivita(7, 4, 2, 3, 5, 0, 6, 1) == 1);
    static_assert(leviCivita(3, 6, 5, 1, 2, 7, 4, 0) == -1);
    static_assert(leviCivita(0, 5, 4, 1, 6, 7, 3, 2) == 1);
    static_assert(leviCivita(1, 0, 7, 5, 4, 7, 6, 2) == 0);

    static_assert(kroneckerDelta(1, 1, 1) == true);
    static_assert(kroneckerDelta(1, 0, 1) == false);
    static_assert(kroneckerDelta(9, 9, 9, 9) == true);

    return 0;
}