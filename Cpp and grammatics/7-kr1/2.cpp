#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <stdexcept>
#include <limits>


class Range
{
    int low, high;
public:
    int get_low() const
    {
        return low;
    }
    int get_high() const
    {
        return high;
    }
    Range(int l = 0, int h = 0)
    {
        if (l > h) {
            throw std::invalid_argument("low > high");
        } else {
            low = l;
            high = h;
        }
    }
    explicit Range(const std::string &s)
    {
        long long ll, hh;
        char dmb;
        std::istringstream iss(s);
        iss >> dmb;
        if (dmb != '(') {
            throw std::invalid_argument("wrong format in string");
        }
        iss >> ll;
        iss >> dmb;
        if (dmb != ',') {
            throw std::invalid_argument("wrong format in string");
        }
        iss >> hh;
        iss >> dmb;
        if (dmb != ')') {
            throw std::invalid_argument("wrong format in string");
        }
        if (iss >> dmb) {
            throw std::invalid_argument("wrong format in string");
        }

        if (ll > hh || check_range(ll) || check_range(hh)) {
            throw std::invalid_argument("overflow or underflow in string");
        } else {
            low = static_cast<int>(ll);
            high = static_cast<int>(hh);
        }
    }
    static int check_range(long long a)
    {
        if (a > std::numeric_limits<int>::max() || a < std::numeric_limits<int>::min()) {
            return 1;
        } else {
            return 0;
        }
    }
    std::string to_string() const
    {
        std::string s = "(" + std::to_string(low) + "," + std::to_string(high) + ")";
        return s;
    }
    friend Range operator + (const Range &mine, const Range &other)
    {
        long long ll = mine.get_low(), hh = mine.get_high();
        ll += other.get_low();
        hh += other.get_high();
        if (Range::check_range(ll) || Range::check_range(hh)) {
            throw std::range_error("overflow or underflow in + or -");
        }
        return Range(mine.get_low() + other.get_low(), mine.get_high() + other.get_high());
    }
    friend Range operator - (const Range &mine, const Range &other)
    {
        return mine + (-other);
    }
    friend Range operator * (const Range &mine, const Range &other)
    {
        int ll, hh;
        long long lh1, lh2, lh3, lh4;
        lh1 = static_cast<long long>(mine.get_low()) * other.get_low();
        lh2 = static_cast<long long>(mine.get_high()) * other.get_low();
        lh3 = static_cast<long long>(mine.get_high()) * other.get_high();
        lh4 = static_cast<long long>(mine.get_low()) * other.get_high();
        if (Range::check_range(lh1) || Range::check_range(lh2) || Range::check_range(lh3) || Range::check_range(lh4)){
            throw std::range_error("overflow or underflow in *");
        }
        ll = std::min(mine.get_low() * other.get_low(),
            std::min(mine.get_low() * other.get_high(),
            std::min(mine.get_high() * other.get_high(),
            mine.get_high() * other.get_low())));
        hh = std::max(mine.get_low() * other.get_low(),
            std::max(mine.get_low() * other.get_high(),
            std::max(mine.get_high() * other.get_high(),
            mine.get_high() * other.get_low())));
        return Range(ll, hh);
    }
    Range operator -() const
    {
        long long ll, hh;
        ll = -static_cast<long long>(high);
        hh = -static_cast<long long>(low);
        if (check_range(ll) || check_range(hh)) {
            throw std::range_error("overflow or underflow in u-");
        }
        return Range(-high, -low);
    }
};
