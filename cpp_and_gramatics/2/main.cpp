#include <iostream>
#include <stdio.h>
#include <cstring>
#include <stdio.h>
#include <cmath>

/*
namespace numbers {
    class complex {
        double x;
        double y;
    public:
        complex(double x = 0, double y = 0)
        {
            this->x = x;
            this->y = y;
        }
        explicit complex(char const* str)
        {
            sscanf(str, "(%lf,%lf)", &x, &y);
        }
        double get_re(void) const
        {
            return x;
        }
        double get_im(void) const
        {
            return y;
        }
        double abs2(void) const
        {
            return x * x + y * y;
        }
        double abs(void) const
        {
            return sqrt(x * x + y * y);
        }
        void to_string(char *buf, size_t size) const
        {
            snprintf(buf, size, "(%.10g,%.10g)", x, y);
        }


        complex operator~ (void) const
        {
            return complex(x, -y);
        }
        complex operator- (void) const
        {
            return complex(-x, -y);
        }

        friend complex operator+ (const complex &c1, const complex &c2);
        friend complex operator- (const complex &c1, const complex &c2);
        friend complex operator* (const complex &c1, const complex &c2);
        friend complex operator/ (const complex &c1, const complex &c2);
    };
    complex operator+ (const complex &c1, const complex &c2)
    {
        return complex(c1.x + c2.x, c1.y + c2.y);
    }
    complex operator- (const complex &c1, const complex &c2)
    {
        return complex(c1.x - c2.x, c1.y - c2.y);
    }

    complex operator* (const complex &c1, const complex &c2)
    {
        return complex(c1.x * c2.x - c1.y * c2.y, c1.x * c2.y + c1.y * c2.x);
    }

    complex operator/ (const complex &c1, const complex &c2)
    {
        double zn = (c2 * complex(c2.x, -c2.y)).x;
        return complex((c1 * complex(c2.x, -c2.y)).x / zn, (c1 * complex(c2.x, -c2.y)).y / zn);
    }





    class complex_stack {
    public:
        size_t num;
        size_t realsize;
        complex *stack_ptr;


        complex_stack()
        : num(0), realsize(0), stack_ptr(nullptr)
        {
        }

        complex_stack(size_t n)
        : num(0), realsize(n * sizeof(complex))
        {
            stack_ptr = new complex [n];
        }

        complex_stack(const complex_stack &st)
        {
            stack_ptr = nullptr;
            num = st.num;
c            realsize = st.realsize;
            if (st.stack_ptr) {
                stack_ptr = new complex [realsize / sizeof(complex)];
                memcpy(stack_ptr, st.stack_ptr, realsize);
            }
        }
        complex_stack(complex_stack &&st)
        : num(st.num), realsize(st.realsize), stack_ptr(st.stack_ptr)
        {
            st.num = 0;
            st.realsize = 0;
            st.stack_ptr = nullptr;
        }
        ~complex_stack()
        {
            num = 0;
            realsize = 0;
            delete [] stack_ptr;
            stack_ptr = nullptr;
        }

        size_t size() const
        {
            return num;
        }

        complex& operator[] (size_t i)
        {
            return stack_ptr[i];
        }

        complex operator[] (size_t i) const
        {
            return stack_ptr[i];
        }

        complex_stack& operator= (const complex_stack &st)
        {
            if (this == &st) {
                return *this;
            }
            delete [] stack_ptr;
            stack_ptr = nullptr;
            num = st.num;
            realsize = st.realsize;
            if (st.stack_ptr) {
                stack_ptr = new complex [realsize / sizeof(complex)];
                memcpy(stack_ptr, st.stack_ptr, realsize);
            }
            return *this;
        }

        complex_stack& operator= (complex_stack &&st)
        {
            std::swap(num, st.num);
            std::swap(realsize, st.realsize);
            std::swap(stack_ptr, st.stack_ptr);

            return *this;
        }

        complex_stack operator<< (const complex &c) const
        {
            complex_stack st;
            if (!stack_ptr) {
                st = complex_stack(16);
            }
            else if (num == realsize / sizeof(complex)) {
                st.num = num;
                st.realsize = realsize * 2;
                st.stack_ptr = new complex [num * 2];
                memcpy(st.stack_ptr, stack_ptr, realsize);
            }
            else {
                st = *this;
            }
            st.stack_ptr[st.num] = c;
            st.num++;
            return st;
        }
        friend complex_stack operator<< (complex_stack &&st, const complex &c);

        complex operator+ () const
        {
            return stack_ptr[num - 1];
        }

        complex_stack operator~ () const
        {
            complex_stack st2 = (*this);
            st2.num--;
            return st2;
        }

        friend complex_stack operator~ (complex_stack &&st);


    };

    complex_stack operator<< (complex_stack &&st, const complex &c)
    {
        complex_stack st2;
        if (!st.stack_ptr) {
            st = complex_stack(16);
        }
        else if (st.num == st.realsize / sizeof(complex)) {
            st2.num = st.num;
            st2.realsize = st.realsize * 2;
            st2.stack_ptr = new complex [st.num * 2];
            memcpy(st2.stack_ptr, st.stack_ptr, st.realsize);
        }
        else {
            st2 = std::move(st);
        }

        st2.stack_ptr[st.num] = c;
        st2.num++;
        return st2;

    }

    complex_stack operator~ (complex_stack &&st)
    {
        complex_stack st2 = std::move(st);
        st2.num--;
        return st2;
    }

    complex eval(char **args, const complex &z)
    {
        complex_stack st;
        int i = 1;

        while (args[i]) {
            if (args[i][0] == '(') {
                st = st << complex(args[i]);
            }
            else if (args[i][0] == 'z') {
                st = st << z;
            }
            else {
                complex tmp;
                tmp = +st;
                if (args[i][0] != '!') {
                    st = ~st;
                }
                switch (args[i][0]) {
                    case '+':
                        tmp = tmp + (+st);
                        st = ~st;
                        break;
                    case '-':
                        tmp = (+st) - tmp;
                        st = ~st;
                        break;
                    case '*':
                        tmp = tmp * (+st);
                        st = ~st;
                        break;
                    case '/':
                        tmp = (+st) / tmp;
                        st = ~st;
                        break;
                    case '~':
                        tmp = ~tmp;
                        break;
                    case '#':
                        tmp = -tmp;
                        break;

                    default:
                        break;
                }
                if (args[i][0] != ';') {
                    st = st << tmp;
                }

            }
            i++;
        }

        return +st;
    }
}

using namespace numbers;

*/
using namespace std;

int main(int argc, char **argv)
{
    /*
    complex_stack st;
    cout << st.realsize << endl;
    st = st << complex(1,1);
    cout << st.realsize << endl;
    st = st << complex(1,1);
    cout << st.realsize << endl;
    complex tmp;
    tmp = +st;
    st = ~st;
    tmp = tmp + (+st);
    st = ~st;
    complex s1(5,5);

    cout << '(' << 0 << ',' << 9 << ')' << endl;
    */
    cout << 0.0 << endl;

    /*
    char c1[100];

    for (int i = 0; i < st.size(); i++) {

        //st[i].to_string(c1, sizeof(c1));
        printf("%s\n", c1);
    }

    printf("size = %zu\n", sizeof(st) * sizeof(complex));
    */

    //complex(1,1).to_string(c1, 100);

    //st = (st) << complex(1,1);

    /*
    for (int i = 0; i < st.size(); i++) {
        st[i].to_string(c1, sizeof(c1));
        printf("%s\n", c1);
    }
    printf("\n");

    complex_stack st2 = complex_stack(2);

    char c[100];
    st[0].to_string(c, sizeof(c));

    complex_stack st3 = st2 << complex(3,3);
    char c2[100];
    st3[2].to_string(c2, sizeof(c2));

    cout << c << '\n' << c2 << endl;
    */

    //char res[100];
    //result.to_string(res, sizeof(res));

    /*
    complex result = eval(argv, complex(1,1));
    std::cout << '(' << result.get_re() << ',' << result.get_im() << ')' << std::endl;
    */

    return 0;
}
