#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Person
{
public:
    string filename;
    string name;
    string nums;
    double average;
    Person(string f, string n, string ns, double a) : filename(f), name(n), nums(ns), average(a) {}
};

int main(int argc, char const *argv[]) {
    double sum = 0, total_sum = 0;
    int num = 0, total_num = 0;
    vector<Person> v;
    for(int i = 0; i < argc; i++) {
        ifstream myfile;
        myfile.open(argv[i]);
        string name = "";
        while (myfile >> name) {
            sum = 0;
            num = 0;
            string marks = "";
            int mark = 0;
            while (myfile >> mark && mark != 0) {
                if (marks.size()) {
                    marks += " ";
                }
                sum += mark;
                if (mark) {
                    num++;
                }
                marks += to_string(mark);
            }
            if (sum / num > 0) {
                v.push_back(Person(argv[i], name, marks, sum / num));
            }
        }
        myfile.close();
    }
    ofstream out;
    out.open("result.txt");
    total_sum = 0;
    total_num = 0;
    for (auto vv : v) {
        total_sum += vv.average;
        total_num++;
    }
    total_sum /= total_num;
    for (auto vv : v) {
        if (vv.average >= total_sum) {
            out << vv.filename << " " << vv.name << " " << vv.nums << endl;
        }
    }
    out.close();
    return 0;
}
