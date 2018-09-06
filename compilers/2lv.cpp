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

vector<Blk *> blocks;
vector<string> blockNames;
vector< vector<string> > defs;
vector< vector<string> > uses;
vector< vector<string> > ins;
vector< vector<string> > outs;

static void readfn(Fn *fn)
{
    for (Blk *blk = fn->start; blk; blk = blk->link)
    {
        vector<string> def{};
        vector<string> use{};
        blockNames.push_back(blk->name);
        blocks.push_back(blk);

        for (auto i = blk->ins; i < &blk->ins[blk->nins]; ++i)
        {
            if (fn->tmp[i->arg[0].val].name[0] != '\0' &&
                std::find(use.begin(), use.end(), fn->tmp[i->arg[0].val].name) == use.end() &&
                std::find(def.begin(), def.end(), fn->tmp[i->arg[0].val].name) == def.end())
            {
                use.push_back(fn->tmp[i->arg[0].val].name);
            }

            if (fn->tmp[i->arg[1].val].name[0] != '\0' &&
                std::find(use.begin(), use.end(), fn->tmp[i->arg[1].val].name) == use.end() &&
                std::find(def.begin(), def.end(), fn->tmp[i->arg[1].val].name) == def.end())
            {
                use.push_back(fn->tmp[i->arg[1].val].name);
            }

            if (fn->tmp[i->to.val].name[0] != '\0' &&
                std::find(def.begin(), def.end(), fn->tmp[i->to.val].name) == def.end())
            {
                def.push_back(fn->tmp[i->to.val].name);
            }
        }

        if (blk->s1 == nullptr && blk->s2 == nullptr && fn->tmp[blk->jmp.arg.val].name[0] != '\0' &&
            std::find(def.begin(), def.end(), fn->tmp[blk->jmp.arg.val].name) == def.end())
        {
            use.push_back(fn->tmp[blk->jmp.arg.val].name);
        }

        defs.push_back(def);
        uses.push_back(use);
    }
    for (auto i = 0; i < blocks.size(); i++) {
        ins.push_back(std::vector<string>());
        outs.push_back(std::vector<string>());
    }

    // cout << "GENS:" << endl;
    // for (auto ii : gens) {
    //     cout << endl;
    //     for (auto iii : ii) {
    //         cout << iii << endl;
    //     }
    // }

    // cout << "KILLS:" << endl;
    // for (auto ii : kills) {
    //     cout << endl;
    //     for (auto iii : ii) {
    //         cout << iii << endl;
    //     }
    // }
    // cout << "-------------------" << endl;
    // for (auto i = 0; i < blocks.size(); i++) {
    //     cout << "BLOCK:" << blocks[i] << endl;
        
    bool changed = true;
    while (changed) {
        changed = false;
        for (auto i = 0; i < blocks.size(); i++) {
            outs[i] = {};
            auto left = blocks[i]->s1;
            if (left) {
                auto name = string(left->name);
                auto it = std::find(blockNames.begin(), blockNames.end(), name);
                int index = std::distance(blockNames.begin(), it); 
                for (auto& ii : ins[index]) {
                    if (std::find(outs[i].begin(), outs[i].end(), ii) == outs[i].end()) {
                        outs[i].push_back(ii);
                    }
                }
            }

            auto right = blocks[i]->s2;
            if (right) {
                auto name = string(right->name);
                auto it = std::find(blockNames.begin(), blockNames.end(), name);
                int index = std::distance(blockNames.begin(), it); 
                for (auto& ii : ins[index]) {
                    if (std::find(outs[i].begin(), outs[i].end(), ii) == outs[i].end()) {
                        outs[i].push_back(ii);
                    }
                }
            }

            // cout << "INS:" << i << endl;
            // for (auto iii : ins[i])
            // {
            //         cout << iii << endl;
            // }

            auto newIn = std::vector<string>(uses[i].begin(), uses[i].end());
            vector<string> diff(outs[i].begin(), outs[i].end());

            for (auto dd : defs[i]) {
                auto it = std::find(diff.begin(), diff.end(), dd);
                if (it != diff.end()) {
                    diff.erase(it);
                }
            }
            for (auto dd : diff) {
                if (std::find(newIn.begin(), newIn.end(), dd) == newIn.end()) {
                    newIn.push_back(dd);
                }
            }

            std::set<string> s1(newIn.begin(), newIn.end());
            std::set<string> s2(ins[i].begin(), ins[i].end());
            if (!std::equal(s1.begin(), s1.end(), s2.begin())) {
                // cout << "NEWOUTS:" << i<< endl;
                // for (auto oo : newOut)
                // {
                //     cout << oo << endl;
                // }
                // cout << "OUTS:"<< i << endl;
                // for (auto oo : outs[i])
                // {
                //     cout << oo << endl;
                // }
                ins[i] = vector<string>(newIn.begin(), newIn.end());
                changed = true;
            }
            // cout << endl;
        }
    }
    // cout << "=============================="  << endl;
    // }
    for (auto i = 0; i < blocks.size(); i++) {
        printf("@%s", blocks[i]->name);

        printf("\n\tlv_out = ");
        for (auto ii : outs[i]) {
            cout << "%" <<  ii << " ";
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

