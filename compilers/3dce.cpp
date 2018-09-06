#ifdef __cplusplus
#define export exports
extern "C" {
    #include <qbe/all.h>
}
#undef export
#else
#include <qbe/all.h>
#endif

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

map< string, set<string> > doms;
map< string, set<string> > dfs;
map< string, set<string> > defs;
set<Ins *> marks;
set<Ins *> workList = set<Ins *>();
Blk *revStart;
set<string> blockNames;

static int useful(Ins* i) {
    return isstore(i->op) || isret(i->op) || isext(i->op);
}

//  174 #define isstore(o) (Ostoreb <= o && o <= Ostored)
//  175 #define isload(o) (Oloadsb <= o && o <= Oload)
//  176 #define isext(o) (Oextsb <= o && o <= Oextuw)
//  177 #define ispar(o) (Opar <= o && o <= Opare)
//  178 #define isarg(o) (Oarg <= o && o <= Oarge)
//  179 #define isret(j) (Jret0 <= j && j <= Jretc)
static void mark(Fn *fn) {
    for (Blk *blk = fn->start; blk; blk = blk->link) {
        for (Ins *i = blk->ins; i < &blk->ins[blk->nins]; ++i) {
            marks.erase(i);
            if (!useful(i)) {
                marks.insert(i);
                workList.insert(i);
            }
            
            while (workList.size()) {
                workList.erase(i);
                auto y = i->arg[0];
                auto z = i->arg[1];
                
                if 

            }
        }

    }

}

static void readfn (Fn *fn) {
    fillrpo(fn); // Traverses the CFG in reverse post-order, filling blk->id.
    fillpreds(fn);
    filluse(fn);
    ssa(fn);

    // ...
    Blk *rev = fn->start;
    Blk *predRev = nullptr;
    while (rev) {
        auto tmp = rev->link;
        rev->link = predRev;
        predRev = rev;
        rev = tmp;
    }
    revStart = predRev;

    // defs start
    for (Blk *blk = fn->start; blk; blk = blk->link) {
        set<string> def{};
        blocks.push_back(blk->name);

        for (auto i = blk->ins; i < &blk->ins[blk->nins]; ++i) {
            if (fn->tmp[i->to.val].name[0] != '\0' &&
            std::find(def.begin(), def.end(), fn->tmp[i->to.val].name) == def.end()) {
                def.insert(fn->tmp[i->to.val]);
            }
        }

        defs[blk->name] = def;
    }
    // defs end

    // dfs start
    for (Blk *blk = revStart; blk; blk = blk->link) {
        blockNames.insert(blk->name);
    }

    for (Blk *blk = revStart; blk; blk = blk->link) {
        if (blk == revStart) {
            doms[blk->name] = set<string>{blk->name};
        } else {
            doms[blk->name] = blockNames;
        }
    }

    bool changed = true;
    while (changed) {
        changed = false;
        map<string, set<string> > newdoms;
        for (Blk *blk = revStart; blk; blk = blk->link) {
            if (blk == revStart) {
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

    map<string, string> idom;
    for (auto block : doms) {
        block.second.erase(block.first);
        for (auto dom : block.second) {
            if (doms[dom] == block.second) {
                idom[block.first] = dom;
                break;
            }
        }
    }

    for (Blk *blk = revStart; blk; blk = blk->link) {
        dfs[blk->name];
        if (blk->npred > 1) {
            for (auto l = 0; l < blk->npred; l++) {
                auto r = string(blk->pred[l]->name);
                while (r != idom[blk->name]) {
                    dfs[r].insert(blk->name);
                    r = idom[r];
                }
            }
        }
    }
    // dfs end



    for (Blk *blk = fn->start; blk; blk = blk->link) {
        for (Ins *i = blk->ins; i < &blk->ins[blk->nins]; ++i) {
            if (!useful(i)) {
                i->op = Onop;
                i->to = R;
                i->arg[0] = R;
                i->arg[1] = R;
            }
        }
        // ...
    }

    fillpreds(fn); // Either call this, or keep track of preds manually when rewriting branches.
    fillrpo(fn); // As a side effect, fillrpo removes any unreachable blocks.
    printfn(fn, stdout);
}

static void readdat (Dat *dat) {
  (void) dat;
}

int main () {
  parse(stdin, "<stdin>", readdat, readfn);
  freeall();
}
