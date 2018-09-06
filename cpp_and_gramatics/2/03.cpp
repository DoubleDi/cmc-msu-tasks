#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>


using namespace std;

namespace numbers {

class complex
{
    double re, im;

public:
    complex (double real = 0.00, double imag = 0.00) :
        re (real),
        im (imag)
    {
    }

    explicit complex (const char *format)
    {
        sscanf (format, "(%lg,%lg)", &re, &im);
    }

    double get_re () const
    {
        return re;
    }

    double get_im () const
    {
        return im;
    }

    double abs2 () const
    {
        return re*re+im*im;
    }

    double abs () const
    {
        return sqrt(abs2());
    }

    void to_string (char *buf, size_t size) const
    {
        snprintf (buf, size, "(%.10g,%.10g)", re, im);
    }

    // void print_out()
    // {
    //     cout << "(" << re << "," << im << ")" << endl;
    // }

    friend complex operator~ (const complex& c1);
    friend complex operator- (const complex& c1);
    friend complex operator+ (const complex& c1, const complex& c2);
    friend complex operator- (const complex& c1, const complex& c2);
    friend complex operator* (const complex& c1, const complex& c2);
    friend complex operator/ (const complex& c1, const complex& c2);
};


complex operator~ (const complex& c1)
{
    complex res{c1.get_re(), -c1.get_im()};
    return res;
}

complex operator- (const complex& c1)
{
    complex res{-c1.get_re(), -c1.get_im()};
    return res;
}

complex operator+ (const complex& c1, const complex& c2)
{
    double res_re = c1.get_re() + c2.get_re();
    double res_im = c1.get_im() + c2.get_im();
    complex res{res_re, res_im};

    return res;
}

complex operator- (const complex& c1, const complex& c2)
{
    double res_re = c1.get_re() - c2.get_re();
    double res_im = c1.get_im() - c2.get_im();
    complex res{res_re, res_im};

    return res;
}

complex operator* (const complex& c1, const complex& c2)
{
    double res_re = c1.get_re()*c2.get_re() - c1.get_im()*c2.get_im();
    double res_im = c1.get_im()*c2.get_re() + c1.get_re()*c2.get_im();
    complex res{res_re, res_im};

    return res;
}
complex operator/ (const complex& c1, const complex& c2)
{
        double abs2c2 = c2.abs2();
        double res_re = (c1.get_re()*c2.get_re() + c1.get_im()*c2.get_im())/abs2c2;
        double res_im = (c1.get_im()*c2.get_re() - c1.get_re()*c2.get_im())/abs2c2;
        complex res{res_re, res_im};

        return res;
}

template< typename T>
void myswap(T& fst, T& sec)
{
    T tmp = fst;
    fst = sec;
    sec = tmp;
}

// complex *operator new[] (size_t sz, complex* p, int am)
// {
//
//     cout << "placement new[] was summoned" << endl;
//     cout << "size_t" << sz << endl;
//
//     complex* new_ptr = new complex[sz];
//
//     for (int i = 0; i < am; i++) {
//         new_ptr[i] = p[i];
//     }
// }

class complex_stack
{
    complex* stack_arr;
    size_t occup_sz;
    size_t alloc_sz;

public:
    complex_stack(size_t start_sz=10) :  // usual constructor
        occup_sz (0),
        alloc_sz (start_sz)
    {
        // cout << "UC was summoned!" << endl;

        if (start_sz <= 0) {
            stack_arr = NULL;
        } else {
            stack_arr = new complex [start_sz];
        }
    }
    complex_stack(const complex_stack& s) :  // copying constructor
        occup_sz (s.occup_sz),
        alloc_sz (s.alloc_sz)
    {
        // cout << "CC was summoned!" << endl;
        stack_arr = new complex [alloc_sz];

        for (size_t i = 0; i < occup_sz; i++) {
            stack_arr[i] = s[i];
        }


    }
    complex_stack(complex_stack&& s) :  // move constructor
        occup_sz(s.occup_sz),
        alloc_sz(s.alloc_sz)
    {
        // cout << "MC was summoned!" << endl;
        stack_arr = s.stack_arr;
        s.stack_arr = NULL;
    }

    ~complex_stack()
    {
        // cout << "D was summoned!" << endl;
        delete[] stack_arr;
    }

    size_t size() const
    {
        return occup_sz;
    }

    complex operator[] (int ind) const
    {
        return stack_arr[ind];
    }

    complex& operator[] (int ind)
    {
        return stack_arr[ind];
    }

    complex_stack& operator= (const complex_stack& s)
    {
        complex* tmp_ptr = stack_arr;
        occup_sz = s.occup_sz;
        alloc_sz = s.alloc_sz;

        stack_arr = new complex[s.alloc_sz];
        for (size_t i = 0; i < occup_sz; i++) {
            stack_arr[i] = s.stack_arr[i];
        }

        delete [] tmp_ptr;

        return *this;
    }

    complex_stack& operator= (complex_stack&& s)
    {
        // cout << "operator= was summoned!" << endl;
        // cout << "Transmitted rvalue" << endl;
        // s.print_out();

        occup_sz = s.occup_sz;
        alloc_sz = s.alloc_sz;
        myswap<complex*> (stack_arr, s.stack_arr);

        // cout << "Target stack" << endl;
        // print_out ();
        // cout << "Rvalue after transmission" << endl;
        // s.print_out();

        return *this;
    }

    // void print_out()
    // {
    //     // cout << occup_sz << "/" << alloc_sz << endl;
    //     for (size_t i = 0; i < occup_sz; i++) {
    //         stack_arr[i].print_out();
    //     }
    // }

    friend complex_stack operator<< (const complex_stack& s, const complex& c);
    friend complex_stack operator<< (complex_stack&& s, const complex& c);
    friend complex_stack operator~  (const complex_stack& s);
    friend complex_stack operator~  (complex_stack&& s);
    friend complex       operator+  (const complex_stack& s);

};

complex_stack operator<< (const complex_stack& s, const complex& c)
{
    // cout << "op<< with const&" << endl;
    complex_stack new_stack = s;
    // new_stack.print_out();
    if (new_stack.occup_sz >= new_stack.alloc_sz) {
        complex *tmp = new complex [new_stack.alloc_sz*2];

        for (size_t i = 0; i < new_stack.occup_sz; i++) {
            tmp[i] = new_stack[i];
        }
        myswap<complex*> (new_stack.stack_arr, tmp);
        new_stack.alloc_sz *= 2;
        delete tmp;
    }
    new_stack.stack_arr[new_stack.occup_sz] = c;
    new_stack.occup_sz++;

    // cout << "New stack at the end of <<" << endl;
    // new_stack.print_out();

    return new_stack;
}

complex_stack operator<< (complex_stack&& s, const complex& c)
{
    // cout << "op<< with &&" << endl;
    complex_stack new_stack = std::move(s);
    if (new_stack.occup_sz >= new_stack.alloc_sz) {
        complex *tmp = new complex [new_stack.alloc_sz*2];

        for (size_t i = 0; i < new_stack.occup_sz; i++) {
            tmp[i] = new_stack[i];
        }
        myswap<complex*> (new_stack.stack_arr, tmp);
        new_stack.alloc_sz *= 2;
        delete tmp;

    }
    new_stack.stack_arr[new_stack.occup_sz] = c;
    new_stack.occup_sz++;

    // cout << "New stack at the end of <<" << endl;
    // new_stack.print_out();
    return new_stack;
}

complex operator+ (const complex_stack& s)
{
    return s.stack_arr[s.occup_sz-1];
}

complex_stack operator~ (const complex_stack& s)
{
    complex_stack new_stack = s;
    new_stack.occup_sz--;
    return new_stack;
}

complex_stack operator~ (complex_stack&& s)
{
    complex_stack new_stack = std::move(s);
    new_stack.occup_sz--;
    return new_stack;
}

complex eval(char** args, const complex& z)
{
    complex_stack op_stack{50};
    complex fst, sec;

    for (long long curr_arg = 0; args[curr_arg] != nullptr; curr_arg++) {
        switch (args[curr_arg][0]) {
            case '(':
                op_stack = op_stack << complex(args[curr_arg]);
                break;

            case 'z':
                op_stack = op_stack << z;
                break;

            case '+':
                fst = +op_stack;
                op_stack = ~op_stack;
                sec = +op_stack;
                op_stack = ~op_stack;
                op_stack = op_stack << (sec + fst);
                break;

            case '-':
                fst = +op_stack;
                op_stack = ~op_stack;
                sec = +op_stack;
                op_stack = ~op_stack;
                op_stack = op_stack << (sec - fst);
                break;

            case '*':
                fst = +op_stack;
                op_stack = ~op_stack;
                sec = +op_stack;
                op_stack = ~op_stack;
                op_stack = op_stack << (sec * fst);
                break;

            case '/':
                fst = +op_stack;
                op_stack = ~op_stack;
                sec = +op_stack;
                op_stack = ~op_stack;
                op_stack = op_stack << (sec / fst);
                break;

            case '!':
                op_stack = op_stack << (+op_stack);
                break;

            case ';':
                op_stack = (~op_stack);
                break;

            case '~':
                fst = +op_stack;
                op_stack = ~op_stack;
                op_stack = op_stack << (~fst);
                break;

            case '#':
                fst = +op_stack;
                op_stack = ~op_stack;
                op_stack = op_stack << (-fst);
                break;


        }
        // cout << "Command:" << args[curr_arg] << endl;
        // op_stack.print_out();
    }

    return +op_stack;
}

}

// int main (void)
// {
//     numbers::complex z{5.0, 6.0};
//
//     const int command_num = 7;
//     const int command_len = 20;
//
//     char** commands = new char* [command_num+1];
//
//     for (int i = 0; i < command_num; i++) {
//         commands[i] = new char [command_len];
//     }
//     strcpy(commands[0], "(0, 1)");
//     strcpy(commands[1], "!");
//     strcpy(commands[3], "z");
//     strcpy(commands[4], "#");
//     strcpy(commands[5], "+");
//     strcpy(commands[6], "*");
//     commands[command_num] = nullptr;
//
//     numbers::complex res = numbers::eval (commands, z);
//
//     for (int i = 0; i < command_num; i++) {
//         if (commands[i] != nullptr) {
//             delete[] commands[i];
//         }
//     }
//     cout << "Return value:" << endl;
//     res.print_out();
//
//     return 0;
// }
using namespace numbers;

int
main(int argc, char *argv[]) {
    int z = 1;
    char **words = (char **)malloc(10 * sizeof(char *));
    words[0] = strdup("z");
    words[1] = strdup(";");
    complex res = eval(words, z);
    cout << res.get_re() << " " << res.get_im() << endl;
    return 0;
}
