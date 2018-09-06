#include <stdio.h>
#include <stdlib.h>


struct RandomOperations;


typedef struct RandomGenerator
{
    int rand;
    unsigned a, c, mod;
    const struct RandomOperations *ops;
}RandomGenerator;


int
nextfunc(RandomGenerator *rr) 
{
    int rand = rr->rand;
    rand = rand * rr->a % rr->mod;
    rand = (rand + rr->c) % rr->mod;
    rr->rand = rand;
    return rr->rand;
}


void
destroyfunc(RandomGenerator *rr) 
{
    free(rr);
}


struct RandomOperations
{
    void(*destroy)(struct RandomGenerator *);
    int(*next)(struct RandomGenerator *);
};


const struct RandomOperations randop =
{
    .destroy = destroyfunc,
    .next = nextfunc
};


RandomGenerator *random_create(int seed) 
{
    RandomGenerator *rr = calloc(1, sizeof(*rr));
    rr->ops = &randop;
    rr->rand = seed;
    rr->a = 1103515245;
    rr->c = 12345;
    rr->mod = 2147483648;
    return rr;
}


#ifdef DEBUG
int
main(void)
{
    RandomGenerator *rr = random_create(1234);
    for (int j = 0; j < 100; ++j) {
        printf("%d\n", rr->ops->next(rr));
    }
    rr->ops->destroy(rr);
    return 0;
}
#endif