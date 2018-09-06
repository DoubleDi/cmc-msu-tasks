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
#include <map>

using namespace std;

Target T;

map<string, set<string> > doms;
set<string> blockNames; 

static void readfn(Fn *fn)
{
    for (Blk *blk = fn->start; blk; blk = blk->link) {
        blockNames.insert(blk->name);
    }

    for (Blk *blk = fn->start; blk; blk = blk->link) {
        if (blk == fn->start) {
            doms[blk->name] = set<string>{blk->name};
        } else {
            doms[blk->name] = blockNames;
        }
    }

    bool changed = true;
    while (changed) {
        changed = false;
        map<string, set<string> > newdoms;
        for (Blk *blk = fn->start; blk; blk = blk->link) {
            if (blk == fn->start) {
                newdoms[blk->name] = doms[blk->name];
                continue;
            } else {
                if (blk->npred) {
                    set<string> inters;
                    auto preds = blk->pred;
                    for (auto l = 0; l < blk->npred; l++) {
                        auto name = string(preds[l]->name);
                        if (!l) {
                            inters = doms[name];
                        } else {
                            std::set<string> tmp;
                            set_intersection(inters.begin(), inters.end(), doms[name].begin(),doms[name].end(),
                                std::inserter(tmp, tmp.begin()));
                            inters = tmp;
                        }
                    }
                    inters.insert(blk->name);
                    newdoms[blk->name] = inters;
                }
            }
        }

        if (newdoms != doms) {
            changed = true;
            doms = newdoms;
        }
    }

    map<string, set<string> > invertedDoms;

    for (auto dd : doms) {
        for (auto d : dd.second) {
            invertedDoms[d].insert(dd.first);
        }
    }

    for (auto dd : invertedDoms) {
        printf("@%s\t", dd.first.c_str());

        for (auto d : dd.second) {
            printf("@%s ", d.c_str());
        }
        printf("\n");
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
