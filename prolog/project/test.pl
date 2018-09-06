elem(X, [X|L]).
elem(X, [Y|L]) :- elem(X, L).

concat([], Y, Y).
concat([U|X], Y, [U|Z]) :- concat(X, Y, Z).

common(X, Y) :- elem(U, X), elem(U, Y).