#include <iostream>

using namespace std;

template <typename value_type>
class Coord
{
public:
    value_type row, col;
    Coord(value_type r = value_type(), value_type c = value_type()) : row(r), col(c) {}
};

template <typename value_type>
value_type dist(Coord<value_type> &size, Coord<value_type> &from, Coord<value_type> &to)
{
    value_type dr, dc, newdr, newdc;
    dr = from.row - to.row;
    dr = dr < 0 ? dr + size.row : dr;

    newdr = to.row - from.row;
    newdr = newdr < 0 ? newdr + size.row : newdr;

    dr = min(newdr, dr);

    dc = from.col - to.col;
    dc = dc < 0 ? dc + size.col : dc;

    newdc = to.col - from.col;
    newdc = newdc < 0 ? newdc + size.col : newdc;

    dc = min(newdc, dc);

    return max(dc, dr);
}
