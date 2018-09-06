#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;


int main(int argc, char ** argv) 
{
    string line;
    int c1 = 0, c2 = 0, c3 = 0, w = 0;

    vector<map<char, int>> graph;
    for (auto i = 0; i <= 7; i++) {
        graph.push_back(map<char, int>());
    }
    graph[0]['('] = 1;
    graph[0]['/'] = 5;
    graph[0]['{'] = 4;
    graph[0]['\''] = 7;
    graph[1]['*'] = 2;
    graph[1]['('] = 1;
    graph[1]['/'] = 5;
    graph[1]['{'] = 4;
    graph[1]['\''] = 7;
    graph[2]['*'] = 3;
    graph[3][')'] = 0;
    graph[4]['}'] = 0;
    graph[5]['/'] = 6;
    graph[6]['\n'] = 0;
    graph[7]['\''] = 0;
    
    int state = 0;
    while (getline(cin, line)) {
        line += '\n';
        auto i = line.begin();
        while (i != line.end()) {
            if (graph[state].find(*i) != graph[state].end()) {
                if (state == 3 && *i == ')') {
                    c1++;
                }
                if (state == 4 && *i == '}') {
                    c2++;
                }
                if (state == 6 && *i == '\n') {
                    c3++;
                }
                if (state == 7 && *i == '\'') {
                    w++;
                }
                state = graph[state][*i];
            } else if (state == 3) {
                state = 2;
            } else if (!(state == 2 || state == 4 || state == 6 || state == 7)) {
                state = 0;
            }
            i++;
        }
    }

    cout << c1 << " " << c2 << " " << c3 << " " << w << endl;
    return 0;
}

// program test; (*just for testing *)
// var
// (* variables
// note that // here is not comment
// and (* here is not a begin of
// another comment *)
// x: integer; (* *)
// begin
// write('(* is not comment // ');
// write(' and (*here*) ' ,x // y);
// end. // It is comment
// and it is not a comment