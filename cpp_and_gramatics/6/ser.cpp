#include <algorithm>

template <class CoordType>
class Coord
{
public:
    typedef CoordType value_type;
    CoordType row, col;
    Coord(CoordType row=CoordType(), CoordType col=CoordType()): row(row), col(col) {}
};

template <class CoordType>
CoordType dist1(CoordType size, CoordType v1, CoordType v2)
{
    // can't use it as CoordType can be unsigned
    // auto res = v1 - v2;
    // if (res < 0) {
    //     res = -res;
    // }
    auto res = std::max(v1, v2) - std::min(v1, v2);
    return std::min(res, size - res);
}

template <class CoordType>
CoordType dist(
                Coord<CoordType> size,
                Coord<CoordType> p1,
                Coord<CoordType> p2)
{
    return dist1(size.row, p1.row, p2.row) + dist1(size.col, p1.col, p2.col);
}

#include <iostream>
int main()
{
    Coord<long long> size;
    std::cin >> size.row >> size.col;
    Coord<long long> p1, p2;
    while (std::cin >> p1.row >> p1.col >> p2.row >> p2.col) {
        std::cout << dist(size, p1, p2) << std::endl;
    }
}
