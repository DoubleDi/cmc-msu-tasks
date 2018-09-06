#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>

using namespace std;
namespace numbers {
    class complex {
        double re;
        double im;
    public:
        complex(double r = 0.0, double i = 0.0) :
            re(r), im(i) {}
        explicit complex(const char * comp) {
            sscanf(comp, "(%lf,%lf)", &re, &im);
        }
        double get_re() const {
            return re;
        }
        double get_im() const {
            return im;
        }
        double abs() const {
            return sqrt(im * im + re * re);
        }
        double abs2() const {
            return abs() * abs();
        }
        void to_string(char *buf, size_t size) const {
            snprintf(buf, size, "(%.10g,%.10g)", re, im);
        }
        friend complex operator + (complex &first, const complex &other);
        friend complex operator - (complex &first, const complex &other);
        friend complex operator * (complex &first, const complex &other);
        friend complex operator / (complex &first, const complex &other);
        friend complex operator ~ (complex &other);
        friend complex operator - (complex &other);
    };
        complex operator - (const complex &other) {
            complex res(-other.get_re(), -other.get_im());
            return res;
        }
        complex operator ~ (const complex &other) {
            complex res(other.get_re(), -other.get_im());
            return res;
        }
        complex operator + (const complex &first, const complex &other) {
            complex res(first.get_re() + other.get_re(), first.get_im() + other.get_im());
            return res;
        }
        complex operator - (const complex &first, const complex &other) {
            complex res(first.get_re() - other.get_re(), first.get_im() - other.get_im());
            return res;
        }
        complex operator * (const complex &first, const complex &other) {
            complex res(other.get_re() * first.get_re() - first.get_im() * other.get_im(),
            first.get_re() * other.get_im() + other.get_re() * first.get_im());
            return res;
        }
        complex operator / (const complex &first, const complex &other) {
            complex res((other.get_re() * first.get_re() + first.get_im() * other.get_im()) /
            (other.get_re() * other.get_re() + other.get_im() * other.get_im()),
            (- first.get_re() * other.get_im() + other.get_re() * first.get_im()) /
            (other.get_re() * other.get_re() + other.get_im() * other.get_im()));
            return res;
        }
}
