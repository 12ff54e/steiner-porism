#include <iostream>

#include "Point.hpp"

using namespace std;
int main() {
    Point pt{0., 1., 0.};
    cout << "Components of " << pt.dim() << "D Point " << pt << " are:\n";
    for (auto&& x : pt) { cout << x << '\n'; };
    return 0;
}