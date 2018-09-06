edge(a,c,8).
edge(a,b,3).
edge(c,d,12).
edge(b,d,0).
edge(e,d,9).



edge1(X,Y,M) :- edge(X,Y,M); edge(Y,X,M).


reverse(T,L) :- reverse1(T,L,[]).

reverse1([], L , L).
reverse1([X|T], L1, L) :- reverse1(T,L1,[X|L]),!.


path(X,Y,L) :-  path1(X,Y,[],L).


path1(X,Y, Visit,[X,Y]) :- edge1(X,Y,_),not(member(Y, Visit)) .
path1(X,Y,Visit,[X|L]) :- edge1(X,Z,_), not(member(Z,Visit)), path1(Z,Y,[X|Visit],L).


min_path(X,Y,L) :-findall(Cost, min_path1(X,Y,[], L, Cost), [A|List_Costs]), min(List_Costs, A, B),min_path1(X,Y,[], L, B).

min([X|T], N, Min) :- N > X, !, min(T , X, Min).
min([], X, X).
min([_|T], N, Min) :- min(T, N, Min). 

min_path1(X, Y, Visit, [X,Y], M) :- edge1(X, Y, M),not(member(Y, Visit)) .
min_path1(X , Y, Visit,  [X|Path], Cost) :-
	edge1(X, Z, M), not(member(Z,Visit)), min_path1(Z, Y, [X|Visit], Path, Cost_Path), Cost is Cost_Path + M. 


cyclic :- path(X,Y,L), path(X,Y,L1), not(L = L1),!.

not_connected :-edge1(X, _, _), edge1(Y, _, _), not(X = Y), not(path(X,Y,_)).

is_connected :- not(not_connected).


short_path(X, Y, Ans) :- add_nodes([[X]], L), is_path(Y, L, L, Ans1), reverse(Ans1, Ans).

add_nodes([], []).
add_nodes([X|T], New) :- first(X, P), findall(A, edge1(P, A, _), List), add_path(X , List, [], New_paths), add_nodes(T, Paths),append(New_paths, Paths, New),! .

add_path(_, [], Res, Res) .
add_path(L, [X|T], Res, Path) :-  add_path(L, T, [[X|L]|Res], Path).

is_path(Y, [], List, Ans) :- not(member1(Y, List)), add_nodes(List, Path), is_path(Y, Path, Path, Ans).
is_path(Y, [X|_], _, X) :- first(X, P), (P = Y).
is_path(Y, [_|T], L, Ans) :- is_path(Y, T, L, Ans).

first([X|_], X).

member1(X, [H|_]) :- member(X, H), !.
member1(X, [_|T]) :- member1(X, T).