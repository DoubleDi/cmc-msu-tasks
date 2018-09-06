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
vector< vector<string> > defs;
vector< vector<string> > uses;

static void readfn(Fn *fn)
{
    for (Blk *blk = fn->start; blk; blk = blk->link) {
        vector<string> def{};
        vector<string> use{};
        blocks.push_back(blk->name);

        for (auto i = blk->ins; i < &blk->ins[blk->nins]; ++i) {
            if (fn->tmp[i->arg[0].val].name[0] != '\0' &&
            std::find(use.begin(), use.end(), fn->tmp[i->arg[0].val].name) == use.end() &&
            std::find(def.begin(), def.end(), fn->tmp[i->arg[0].val].name) == def.end()) {
                use.push_back(fn->tmp[i->arg[0].val].name);
            }

            if (fn->tmp[i->arg[1].val].name[0] != '\0' &&
            std::find(use.begin(), use.end(), fn->tmp[i->arg[1].val].name) == use.end() &&
            std::find(def.begin(), def.end(), fn->tmp[i->arg[1].val].name) == def.end()) {
                    use.push_back(fn->tmp[i->arg[1].val].name);
            } 

            if (fn->tmp[i->to.val].name[0] != '\0' &&
            std::find(def.begin(), def.end(), fn->tmp[i->to.val].name) == def.end()) {
                def.push_back(fn->tmp[i->to.val].name);
            }
        }

        if (blk->s1 == nullptr && blk->s2 == nullptr && fn->tmp[blk->jmp.arg.val].name[0] != '\0' &&
        std::find(def.begin(), def.end(), fn->tmp[blk->jmp.arg.val].name) == def.end()) {
            use.push_back(fn->tmp[blk->jmp.arg.val].name);
        }

        defs.push_back(def);
        uses.push_back(use);
    }

    for (auto i = 0; i < defs.size(); i++) {
        cout << "@" << blocks[i];
        printf("\n\tdef = ");
        for (auto dd : defs[i]) {
            cout << "%" << dd << " ";
        }

        printf("\n\tuse = ");
        for (auto uu : uses[i]) {
            cout << "%" << uu << " ";
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

