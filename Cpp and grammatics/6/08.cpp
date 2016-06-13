#include <iostream>
#include <string>
#include <vector>

using namespace std;

class String;

struct StringBuffer
{
    string buf;
    unsigned long long ref_count;

    StringBuffer (string my_str):
        buf (my_str),
        ref_count (1)
    {
    }

    ~StringBuffer ()
    {
    }
};

class String
{
public:
    StringBuffer* my_buf;

    String (const char* str_i="");
    String (const String& copy);
    String (String&& rval);
    ~String ();

    String& operator= (const String& copy);
    String& operator= (String&& rval);
    String& operator+= (const String& plus);
    operator string ();

    char& operator[] (int ind);
    char  operator[] (int ind) const;

    void detach();
};

String::String (const char* str_i)
{
    my_buf = new StringBuffer(str_i);
}

String::String (const String& copy) :
    my_buf (copy.my_buf)
{
    (my_buf->ref_count)++;
}

String::String (String&& rval):
    my_buf(rval.my_buf)
{
    (my_buf->ref_count)++;
}

String::~String ()
{
    detach();
}

String& String::operator= (const String& copy)
{
    if (&copy == this) {
        return *this;
    }
    detach();

    my_buf = copy.my_buf;
    (my_buf->ref_count)++;
    return (*this);
}

String& String::operator= (String&& rval)
{
    if (&rval == this) {
        return *this;
    }

    detach();
    my_buf = rval.my_buf;
    (my_buf->ref_count)++;

    return (*this);
}

String::operator string ()
{
    return my_buf->buf;
}

String& String::operator+= (const String& plus)
{
    string tmp = my_buf->buf;
    detach();
    tmp += plus.my_buf->buf;

    my_buf = new StringBuffer(tmp);
    return (*this);
}

char& String::operator[] (int ind)
{
    string tmp = my_buf->buf;
    detach();

    my_buf = new StringBuffer(tmp);
    return (my_buf->buf)[ind];
}

char String::operator[] (int ind) const
{
    return (my_buf->buf)[ind];
}

void String::detach()
{
    if (my_buf != nullptr) {
        (my_buf->ref_count)--;
        if (my_buf->ref_count == 0) {
            delete my_buf;
            my_buf = nullptr;
        }
    }
}

int main (void)
{
    String c, a = "abc";
    String b = a; // в памяти хранится "abc" в одном экземпляре
    c = a;
    b += "aaa"; // для b создался новый "массив" символов.
    c[1] = 'f'; // a не изменилось
    a = b;
    b += "c";
    cout << string(a) << endl;
    cout << string(b) << endl;
    cout << string(c) << endl;
}
