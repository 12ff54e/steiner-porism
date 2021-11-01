#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>

#include "../GeometricTransform.hpp"
#include "../Point.hpp"
#include "../util.hpp"

using namespace std;
int main() {
    constexpr Point pt{6., 2., 7.};
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

    static_assert(leviCivita(2u, 4u, 5u, 7u, 3u, 1u, 0u, 6u) == -1);
    static_assert(leviCivita(7u, 4u, 2u, 3u, 5u, 0u, 6u, 1u) == 1);
    static_assert(leviCivita(3u, 6u, 5u, 1u, 2u, 7u, 4u, 0u) == -1);
    static_assert(leviCivita(0u, 5u, 4u, 1u, 6u, 7u, 3u, 2u) == 1);
    static_assert(leviCivita(1u, 0u, 7u, 5u, 4u, 7u, 6u, 2u) == 0);

    static_assert(kroneckerDelta(1, 1, 1) == true);
    static_assert(kroneckerDelta(1, 0, 1) == false);
    static_assert(kroneckerDelta(9, 9, 9, 9) == true);

    // Testing rotation in 3D

    auto rt1 = rotationTransform3D(M_PI / 3, {1, 1, 1});
    auto rt2 = rotationTransform3D(M_PI / 3, M_PI / 4, M_PI / 6);
    cout << "...After rotation pi/3 around (1, 1, 1): ";
    for (auto&& x : rt1(pt)) { cout << x << ' '; };
    cout << '\n';
    cout << "...After rotation {yaw:pi/3, pitch:pi/4, rolling:pi/6}: ";
    for (auto&& x : rt2(pt)) { cout << x << ' '; };
    cout << '\n';

    // Stereographic projection

    auto ptn = static_cast<const decltype(pt)>(pt).normalize();
    cout << "...Normalized: ";
    for (auto&& x : ptn) { cout << x << ' '; }
    cout << '\n';

    auto pt2 = stereographicProjection<3>(ptn);

    cout << "...Stereographic projection: ";
    for (auto&& x : pt2) { cout << x << ' '; }
    cout << '\n';
    cout << "...And its invers: ";
    for (auto&& x : stereographicProjection<3>(pt2)) { cout << x << ' '; }
    cout << '\n';

    return 0;
}