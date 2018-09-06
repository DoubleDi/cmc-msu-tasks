#include <iostream>
#include <string>

using namespace std;

class StringBuf
{
public:
    string buffer;
    int ref_counter;
    StringBuf(string s = "", int r = 1) : buffer(s), ref_counter(r) {}
};

class String
{
public:
    StringBuf * str;
    String(const char * s = "")
    {
        str = new StringBuf(s);
    }
    String(const String &s)
    {
        str = s.str;
        str->ref_counter++;
    }
    String(String &&s)
    {
        str = s.str;
        str->ref_counter++;
    }
    String & operator += (const String & other)
    {
        auto tmp = str->buffer;
        unlink();
        tmp += other.str->buffer;
        str = new StringBuf(tmp);
        return *this;
    }
    operator string()
    {
        return str->buffer;
    }
    String & operator = (const String & other)
    {
        if (this != &other) {
            unlink();
            str = other.str;
            str->ref_counter++;
        }
        return *this;
    }
    String & operator = (String && other)
    {
        if (this != &other) {
            unlink();
            str = other.str;
            str->ref_counter++;
        }
        return *this;
    }
    char &operator[] (int index)
    {
        auto tmp = str->buffer;
        unlink();
        str = new StringBuf(tmp);
        return str->buffer[index];
    }
    char &operator[] (int index) const
    {
        return str->buffer[index];
    }
    ~String()
    {
        unlink();
    }
    void unlink()
    {
        if (str) {
            str->ref_counter--;
            if(!str->ref_counter){
                delete str;
                str = nullptr;
            }
        }
    }
};
int main (void)
{
    String c, a = "abc";
    c = a;
    String b = a; // в памяти хранится "abc" в одном экземпляре
    b += "aaa"; // для b создался новый "массив" символов.
    c[1] = 'f'; // a не изменилось
    a = b;
    b += "c";
    cout << string(a) << endl;
    cout << string(b) << endl;
    cout << string(c) << endl;
}
