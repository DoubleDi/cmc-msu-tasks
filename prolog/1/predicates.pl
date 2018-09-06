%%% Дорожкин Денис, 425 группа %%%
%%% 9 %%%
mySort([], []).        
mySort([X], [X]).        
mySort([X | T], R) :- mySort(T, R1), insert(X, R1, R).
            
insert(X, [], [X]).
insert(X, [Y | T], [Y | R]) :- Y < X, !, insert(X, T, R).
insert(X, [Y | T], [X, Y | T]).

edge(a, b, 4).
edge(b, c, 3).
edge(b, e, 1).
edge(c, d, 5).
edge(d, e, 4).
edge(a, k, 1).
edge(k, e, 3).
edge(l, e, 1).

edge1(X, Y, L) :- edge(X, Y, L); edge(Y, X, L).


%%% 16 %%%
path(X, Y, L2) :- pathVisit(X, Y, L, [X]), L1 = [X | L], append(L1, [Y], L2).

pathVisit(X, Y, [], V) :- edge1(X, Y, _), not(member(Y, V)).
pathVisit(X, Y, [Z | R], V) :- edge1(X, Z, _), not(member(Z, V)), pathVisit(Z, Y, R, [Z | V]).


%%% 17 %%%
minPath(X, Y, L) :- findall(C1/L1, minPathVisit(X, Y, L1, [X], C1), Res), minimal(Res, Res, L).

minPathVisit(X, X, [], _, _) :- !.
minPathVisit(X, Y, [], _, C) :- edge1(X, Y, C), !.
minPathVisit(X, Y, [Z | R], V, C) :- edge1(X, Z, C1), not(member(Z, V)), minPathVisit(Z, Y, R, [Z | V], C2), C is C1 + C2.

minimal([C / L | _], L2, L) :- isMin(C, L2).
minimal([ _ | T], L2, L1) :- minimal(T, L2, L1).

isMin(C, [C1 / _]) :- C =< C1, !.
isMin(C, [C1 / _ | T]) :- C =< C1, isMin(C, T).

%%% 18 %%%
shortPath(X, Y, L) :- bfs(X, [[Y]], L).

bfs(X, [[X | T] | T1], [Y | TT]) :- X = Y, T = TT, length([[X | T] | T1], C), shortPathWithLength([[X | T] | T1], C).
bfs(X, [[Y | T] | T1], L) :- findall(R, getNewV(Y, T, R), TT),
    append(T1, TT, T2), bfs(X, T2, L).

shortPathWithLength([L | T], C) :- length(L, C), !.
shortPathWithLength([L | T], C) :- shortPathWithLength(T, C).

getNewV(X, T, [Y, X | T]) :- edge1(X, Y, _), not(member(Y, T)).


%%% 19 %%%
cyclic :- path(X, Y, L1), path(X, Y, L2), dif(L1, L2), !.


%%% 20 %%%
isConnected(X, Y) :- not((edge1(X, _, _), edge1(_, Y, _), dif(X, Y), not(path(X, Y, L)))).
