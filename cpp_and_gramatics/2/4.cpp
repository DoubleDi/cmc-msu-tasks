#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>

using namespace std;

namespace numbers {
    class complex {
        double re;
        double im;
    public:
        complex(double r = 0.0, double i = 0.0) :
            re(r), im(i) {}
        explicit complex(const char * comp)
        {
            sscanf(comp, "(%lf,%lf)", &re, &im);
        }
        double get_re() const
        {
            return re;
        }
        double get_im() const
        {
            return im;
        }
        double abs() const
        {
            return sqrt(im * im + re * re);
        }
        double abs2() const
        {
            return abs() * abs();
        }
        void to_string(char *buf, size_t size) const
        {
            snprintf(buf, size, "(%.10g,%.10g)", re, im);
        }
        friend complex operator + (complex &first, const complex &other)
        {
            complex res(first.get_re() + other.get_re(), first.get_im() + other.get_im());
            return res;
        }
        friend complex operator - (complex &first, const complex &other)
        {
            complex res(first.get_re() - other.get_re(), first.get_im() - other.get_im());
            return res;
        }
        friend complex operator * (complex &first, const complex &other)
        {
            complex res(other.get_re() * first.get_re() - first.get_im() * other.get_im(),
            first.get_re() * other.get_im() + other.get_re() * first.get_im());
            return res;
        }
        friend complex operator / (complex &first, const complex &other)
        {
            complex res((other.get_re() * first.get_re() + first.get_im() * other.get_im()) /
            (other.get_re() * other.get_re() + other.get_im() * other.get_im()),
            (- first.get_re() * other.get_im() + other.get_re() * first.get_im()) /
            (other.get_re() * other.get_re() + other.get_im() * other.get_im()));
            return res;
        }

        friend complex operator ~ (complex &other)
        {
            complex res(other.get_re(), -other.get_im());
            return res;
        }

        friend complex operator - (complex &other)
        {
            complex res(-other.get_re(), -other.get_im());
            return res;
        }
    };


    class complex_stack {
        complex * head_pointer = nullptr;
        size_t sz = 0;
        size_t current = 0;

        void push(const complex &new_element)
        {
            if (sz - 1  == current) {
                sz *= 2;
                complex * new_head_pointer = new complex [sz];
                memcpy(new_head_pointer, this->head_pointer, (current + 1) * sizeof(complex));
                delete [] this->head_pointer;
                this->head_pointer = new_head_pointer;
            }
            head_pointer[current++] = new_element;
        }

    public:
        complex_stack() : sz(10), current(0)
        {
            head_pointer = new complex [sz];
        }

        complex_stack(const complex_stack &stack) : sz(stack.sz),
        current(stack.current)
        {
            complex * new_head = new complex [sz];
            memcpy(new_head, stack.head_pointer, sizeof(complex) * (current + 1));
            this->head_pointer = new_head;
        }

        complex_stack(complex_stack &&stack) : head_pointer(stack.head_pointer),
        sz(stack.sz), current(stack.current)
        {
            stack.head_pointer = nullptr;
        }

        size_t size() const
        {
            return current;
        }

        complex operator [] (const size_t index) const
        {
            return head_pointer[index];
        }

        complex operator [] (const size_t index)
        {
            return head_pointer[index];
        }

        ~complex_stack()
        {
            if (head_pointer != nullptr) {
                delete [] head_pointer;
            }
        }

        complex_stack &operator = (complex_stack &stack)
        {
            sz = stack.sz;
            current = stack.current;
            delete [] head_pointer;
            head_pointer = new complex [sz];
            memcpy(head_pointer, stack.head_pointer, sizeof(complex) * (current + 1));
            return *this;
        }

        complex_stack &operator = (complex_stack &&stack)
        {
            sz = stack.sz;
            current = stack.current;
            delete [] head_pointer;
            head_pointer = stack.head_pointer;
            stack.head_pointer = nullptr;
            return *this;
        }

        friend complex_stack operator ~ (const complex_stack &stack)
        {
            complex_stack new_stack{stack};
            if (new_stack.current) {
                new_stack.current--;
            }
            return new_stack;
        }

        friend complex_stack operator ~ (complex_stack &&stack)
        {
            complex_stack new_stack = move(stack);
            if (new_stack.current) {
                new_stack.current--;
            }
            return new_stack;
        }

        friend complex_stack operator<< (const complex_stack &stack, const complex &new_elem)
        {
            complex_stack new_stack{stack};
            new_stack.push(new_elem);
            return new_stack;
        }

        friend complex_stack operator<< (complex_stack &&stack, const complex &new_elem)
        {
            complex_stack new_stack = move(stack);
            new_stack.push(new_elem);
            return new_stack;
        }
        friend complex operator + (const complex_stack &stack)
        {
            return stack[stack.current - 1];
        }
    };


    complex eval(char **args, const complex &z)
    {
        int i = 0;
        complex_stack stack;
        complex num1;
        complex num2;
        while(args[i] != nullptr) {
            if (args[i][0] == 'z') {
                stack = stack << z;
            } else if (args[i][0] == '+') {
                num2 = +stack;
                stack = ~stack;
                num1 = +stack;
                stack = ~stack;
                stack = stack << num1 + num2;
            } else if (args[i][0] == '-') {
                num2 = +stack;
                stack = ~stack;
                num1 = +stack;
                stack = ~stack;
                stack = stack << num1 - num2;
            } else if (args[i][0] == '*') {
                num2 = +stack;
                stack = ~stack;
                num1 = +stack;
                stack = ~stack;
                stack = stack << num1 * num2;
            } else if (args[i][0] == '/') {
                num2 = +stack;
                stack = ~stack;
                num1 = +stack;
                stack = ~stack;
                stack = stack << num1 / num2;
            } else if (args[i][0] == '!') {
                num1 = +stack;
                stack = stack << num1;
            } else if (args[i][0] == ';') {
                stack = ~stack;
            } else if (args[i][0] == '~') {
                num1 = +stack;
                stack = ~stack;
                num1 = ~num1;
                stack = stack << num1;
            } else if (args[i][0] == '#') {
                num1 = +stack;
                stack = ~stack;
                num1 = -num1;
                stack = stack << num1;
            } else if (args[i][0] == '(') {
                complex num3{args[i]};
                stack = stack << num3;
            }
            i++;
        }
        return +stack;
    }

}


using namespace numbers;

int
main(int argc, char *argv[])
{
    complex c{argv[1]};
    double r = atof(argv[2]);
    int n = atoi(argv[3]);
    double angle = 2*M_PI / n;
    char result[50] = {};

    complex prev{r};
    prev = prev + c;
    complex now, middle, len, res;

    for (int i = 0; i < n; i++) {
        now = complex{r * cos(angle * (i + 1)), r * sin(angle * (i + 1))};
        now = now + c;
        middle = now + prev;
        middle = middle / 2.0;
        len = eval(&argv[4], middle);
        res = res + (len * (now - prev));
        prev = now;
    }
    res.to_string(result, sizeof(result));
    cout << result << endl;
    return 0;
}
