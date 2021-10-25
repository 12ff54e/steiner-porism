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

    return 0;
}