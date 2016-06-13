#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>

using namespace std;

namespace numbers {

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
}
