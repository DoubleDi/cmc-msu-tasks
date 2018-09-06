# file: sieve.il
# data $fmt = { b "%d\n", b 0 }  # fmt = "%d\n";
# data $arr = { z 100 }

# function w $printloop(w %n, l %arr) {
# @start
#     %ind =l add 0, 0         # for loop
# @condloop1
#     %cond =w csgtw %n, %ind
#     jnz %cond, @loop1, @endloop1
# @loop1
#     %elem =l add %arr, %ind
#     %r =w loadub %elem
#     %t =w call $printf(l $fmt, w %r)
#     %ind =l add %ind, 1
#     jmp @condloop1
# @endloop1
#     ret 0
# }

# export function w $main() {
# @start
#     call $sieve(w 10, l $arr)
#     call $printloop(w 10, l $arr)
#     ret 0
# }


export function $sieve(w %n, l %prime) {
@start
    %cond =w csgtw %n, 0
    jnz %cond, @c1true, @c1false
@c1true
    storeb 0, %prime
@c1false

    %cond =w csgtw %n, 1
    jnz %cond, @c2true, @c2false
@c2true
    %offset =l add %prime, 1
    storeb 0, %offset
@c2false

    %i =l add 0, 2 
@loop1 
    %cond =w csltw %i, %n
    jnz %cond, @continueloop1, @endloop1
@continueloop1
    %offset =l add %prime, %i
    storeb 1, %offset
    %i =l add %i, 1
    jmp @loop1
@endloop1

    %i =l add 0, 2 
@loop2 
    %cond =w csltw %i, %n
    jnz %cond, @continueloop2, @endloop2
@continueloop2
    %offset =l add %prime, %i
    %elem =w loadub %offset
    %cond =w cnew %elem, 0
    jnz %cond, @c3true, @c3false
@c3true

    %j =l mul %i, %i 
@loop3
    %cond =w csltw %j, %n
    jnz %cond, @continueloop3, @endloop3
@continueloop3
    %offset =l add %prime, %j
    storeb 0, %offset
    %j =l add %j, %i
    jmp @loop3
@endloop3

@c3false
    %i =l add %i, 1
    jmp @loop2
@endloop2
    ret
}