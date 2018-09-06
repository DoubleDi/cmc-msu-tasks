// g++ -I/qbe/ 2gk.cpp qbe/obj/libqbe.a

#define export exports
extern "C" {
    #include "qbe/all.h"
}
#undef export
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

Target T;

vector<string> blocks;
vector< vector<string> > gens;
vector< vector<string> > kills;

static void readfn(Fn *fn)
{
    for (Blk *blk = fn->start; blk; blk = blk->link) {
        vector<string> gen{};

        blocks.push_back(blk->name);
        for (auto i = blk->ins; i < &blk->ins[blk->nins]; ++i) {
            if (fn->tmp[i->to.val].name[0] != '\0' &&
            std::find(gen.begin(), gen.end(), fn->tmp[i->to.val].name) == gen.end()) {
                gen.push_back(fn->tmp[i->to.val].name);
            }
        }

        gens.push_back(gen);
    }

    for (auto j = 0; j < gens.size(); j++) {
        vector<string> kill;
        for (int k = 0; k < gens[j].size(); k++) {
            for (auto i = 0; i < gens.size(); i++) {
                if (i == j) {
                    continue;
                }
                if (std::find(gens[i].begin(), gens[i].end(), gens[j][k]) != gens[i].end()) {
                    string str = "@"+string(blocks[i])+"%"+string(gens[j][k]);
                    if (std::find(kill.begin(), kill.end(), str) == kill.end()) {
                        kill.push_back(str.c_str());
                    }
                    break;
                }
            }
        }
        kills.push_back(kill);
    }


    for (auto i = 0; i < blocks.size(); i++) {
        printf("@%s", blocks[i].c_str());
        
        printf("\n\tgen = ");
        for (auto gg : gens[i]) {
            printf("@%s%%%s ", blocks[i].c_str(), gg.c_str());
        }

        printf("\n\tkill = ");
        for (auto kk : kills[i]) {
            printf("%s ", kk.c_str());
        }
        printf("\n\n");
    }
}

static void readdat(Dat *dat)
{
    (void)dat;
}

int main()
{
    parse(stdin, "<stdin>", readdat, readfn);
    freeall();
}

