
// E -> E+T | E-T | T
// T -> T*F | T/F | F
// F -> n | i | '('E')''

// return EOF + - * / ( ) num id
// изменяем для правой рекурии
// E -> T+E | T-E | T
// E -> TEE
// EE -> +E|-E|_

// правая рекурсивная грамматика имеет неправильую ассоциативность
// заменяем рукурсию на итерации
// {} - повторено 0 или более раз и [] - может быть может не быть
// A ->alpha{betta}gamma.
// A -> alphaAAgamma
// AA -> bettaAA | _

// A ->alpha[betta]gamma.
// A -> alphaAAgamma
// AA -> betta | _

// в итоге
// E -> T{(+|-)T}
// T -> F{(*|/)F}


// Добавляем унарные операции
// F -> {+|-}P
// или
// F -> +F|-F|P

// добавляем составные операторы
// Z-> E; | '{'{Z}'}'| "if" '('E')' Z ["else" Z]
#include <iostream>

using namespace std;

enum class Token
{
    EEOF,
    NUM,
    ID,
    PLUS,
    MINUS,
    MUL,
    DIV,
    LBR,
    RBR,
    LBRC,
    RBRC,
    SEMICOLON,
    IF
};

class Scanner
{
    istream &in;
    int c;
    string value;

public:
    Scanner(istream &in) :in(in) { c = in.get(); }
    Token get()
    {
        while(isspace(c)) c = in.get();
        if (c == EOF) return Token::EEOF;
        if (c == '+') {
            c = in.get();
            return Token::PLUS;
        } else if (c == '-') {
            c = in.get();
            return Token::MINUS;
        } else if (c == '*') {
            c = in.get();
            return Token::MUL;
        } else if (c == '/') {
            c = in.get();
            return Token::DIV;
        } else if (c == '(') {
            c = in.get();
            return Token::LBR;
        } else if (c == ')') {
            c = in.get();
            return Token::RBR;
        } else if (c == '{') {
            c = in.get();
            return Token::LBRC;
        } else if (c == '}') {
            c = in.get();
            return Token::RBRC;
        } else if (c == ';') {
            c = in.get();
            return Token::SEMICOLON;
        } else if (isdigit(c)) {
            value.clear();
            while(isdigit(c)) {
                value.append(1, char(c));
                c = in.get();
            }
            return Token::NUM;
        } else if (isalpha(c)) {
            value.clear();
            while(isalnum(c)) {
                value.append(1, c);
                 c = in.get();
            }
            if (value == "if") return Token::IF;
            throw string("Token not supported ") + value;
        } else {
            throw string("Invalid char: ") + char(c);
        }
    }
    const string &get_value() const { return value; }
};

class Parser
{
    Scanner &scan;
    Token t;
public:
    Parser(Scanner &scan) : scan(scan) {}
    void parse_E(int & r)
    {
        parse_T(r);
        while(t == Token::PLUS || t == Token::MINUS) {
            auto op = t;
            t = scan.get();
            int rr = 0;
            parse_T(rr);
            if (op == Token::PLUS) {
                r += rr;
            } else if (op == Token::MINUS) {
                r -= rr;
            }
        }
    }
    void parse_T(int & r)
    {
        parse_F(r);
        while(t == Token::MUL || t == Token::DIV) {
            auto op = t;
            t = scan.get();
            int rr = 0;
            parse_T(rr);
            if (op == Token::MUL) {
                r *= rr;
            } else if (op == Token::DIV) {
                r /= rr;
            }
        }
    }
    void parse_Z(int & r)
    {
        if (t == Token::LBRC) {
            t = scan.get();
            while(t != Token::RBRC && t != Token::EEOF) {
                parse_Z(r);
                cout << "Res: " << r << endl;
            }
            if (t != Token::RBRC) {
                throw string("} expected");
            }
            t = scan.get();
        } else if ( t == Token::IF) {

        } else {
            parse_E(r);
            if (t != Token::SEMICOLON)
                throw string("Expexted ;");
            t = scan.get();
        }
    }
    void parse_F(int & r)
    {
        if (t == Token::PLUS) {
            t = scan.get();
            parse_F(r);
        } else if (t == Token::MINUS) {
            t = scan.get();
            parse_F(r);
            r = -r;
        } else {
            parse_P(r);
        }
    }
    void parse_P(int & r)
    {
        if (t == Token::NUM) {
            r = stoi(scan.get_value());
            t = scan.get();
        } else if (t == Token::ID) {
            t = scan.get();
        } else if (t == Token::LBR) {
            t = scan.get();
            parse_E(r);
            if (t != Token::RBR) {
                throw string("Expected )");
            }
            t = scan.get();
        } else {
            throw string("parse error before") + to_string(int(t));
            // если убрать ошибку то будет можно юзать пустую альтернативу
        }
    }
    void parse(int & r)
    {
        t = scan.get();
        parse_E(r);
        if (t != Token::EEOF) {
            throw string("EOF expected");
        }
    }
};

int main(int argc, char const *argv[]) {
    Scanner scan(cin);
    Parser parser(scan);

    try {
        int r;
        parser.parse(r);
        cout << "Result: " << r << endl;
    } catch(const string &s) {
            cerr << "error: " << s << endl;
    }
    // try {
    //     while ((t = scan.get())!= Token::EEOF) {
    //         cout << int(t) << endl;
    //     }
    // } catch(const string &s) {
    //     cerr << "error: " << s << endl;
    // }
    return 0;
}
