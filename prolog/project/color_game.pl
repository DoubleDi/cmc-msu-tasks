% Дорожкин Денис Сергеевич 425 группа
% Игра в цвета 
% Запускать при помощи команды start().

:- use_module(library(pce)).
:- use_module(library(random)).


% Как создать произвольный rgb цвет
% colour(@default, R * 257, G * 257 , B * 257, rgb))


% Начать игру
start() :- 
    show_window(), start_new_game().


% Отрисовка главного окна
show_window() :- 
    new(@win,dialog('color game')),
    send(@win, append, new(@window,box(650,400))),
    send(@window, fill_pattern, colour(white)),    
    
    send(@win, open),
    send(@win, display, new(@UA, text_item(answer)), point(385,320)),
    send(@win, display, new(@enter, button(enter,  message(@win, return, @UA?selection))), point(435,350)),
    send(@win, display, new(@exit, button(exit,  message(@win, return, 'EXIT'))), point(435,380)),
    send(@win, display, new(@text, bitmap("text.jpg")), point(385,250)),   
    send(@win, display, new(@before, bitmap("before.jpg")), point(60, 220)),   
    send(@win, display, new(@after, bitmap("after.jpg")), point(215,223)),   
    send(@win, display, new(@ans, bitmap("ans.jpg")), point(145,340)),   
    send(@win, display, new(@info, bitmap("info.jpg")), point(20,30)),   

    send(@win, default_button, enter).


% Старт новой игры
start_new_game() :-
    random_between(1, 127, RAND_R_1), random_between(1, 127, RAND_G_1), random_between(1, 127, RAND_B_1),
    random_between(128, 255, RAND_R_2), random_between(128, 255, RAND_G_2), random_between(128, 255, RAND_B_2),
    
    min(RAND_R_1, RAND_R_2, MIN_R), max(RAND_R_1, RAND_R_2, MAX_R),
    min(RAND_G_1, RAND_G_2, MIN_G), max(RAND_G_1, RAND_G_2, MAX_G),
    min(RAND_B_1, RAND_B_2, MIN_B), max(RAND_B_1, RAND_B_2, MAX_B),

    generate_list(MIN_R, MAX_R, RS, 7),
    generate_list(MIN_G, MAX_G, GS, 7),
    generate_list(MIN_B, MAX_B, BS, 7),

    start_game(MIN_R, MIN_G, MIN_B, MAX_R, MAX_G, MAX_B, RS, GS, BS).


% Список произвольных значений цветов
generate_list(MIN, MAX, [], 0).
generate_list(MIN, MAX, [V|L], X) :- random_between(MIN, MAX, V), Z is X - 1, generate_list(MIN, MAX, L, Z).


% Начать игру со сгенерированными цветовыми параметрами
start_game(R_1, G_1, B_1, R_2, G_2, B_2, RS, GS, BS) :- 
    % отображение игрового поля
    send(@win, display, new(@box, box(30, 30)), point(435,200)),
    send(@box, fill_pattern,colour(@default, R_1 * 257, G_1 * 257, B_1 * 257, rgb)),    
    send(@win, display, new(@box2, box(30, 30)), point(470,200)),
    send(@box2, fill_pattern,colour(white)),    
    send(@win, display, new(@box3, box(30, 30)), point(505,200)),
    send(@box3, fill_pattern,colour(white)),    
    send(@win, display, new(@box4, box(30, 30)), point(540,200)),
    send(@box4, fill_pattern,colour(white)),    
    send(@win, display, new(@box5, box(30, 30)), point(575,200)),
    send(@box5, fill_pattern,colour(@default, R_2 * 257, G_2 * 257, B_2 * 257, rgb)),    
    
    nth1(1, RS, RAND_1_R), nth1(1, GS, RAND_1_G), nth1(1, BS, RAND_1_B),
    nth1(2, RS, RAND_2_R), nth1(2, GS, RAND_2_G), nth1(2, BS, RAND_2_B),
    nth1(3, RS, RAND_3_R), nth1(3, GS, RAND_3_G), nth1(3, BS, RAND_3_B),
    nth1(4, RS, RAND_4_R), nth1(4, GS, RAND_4_G), nth1(4, BS, RAND_4_B),
    nth1(5, RS, RAND_5_R), nth1(5, GS, RAND_5_G), nth1(5, BS, RAND_5_B),
    nth1(6, RS, RAND_6_R), nth1(6, GS, RAND_6_G), nth1(6, BS, RAND_6_B),
    nth1(7, RS, RAND_7_R), nth1(7, GS, RAND_7_G), nth1(7, BS, RAND_7_B),
    
    send(@win, display, new(@ans_box1, box(30, 30)), point(395,50)),
    send(@ans_box1, fill_pattern,colour(@default, RAND_1_R * 257, RAND_1_G * 257 , RAND_1_B * 257, rgb)),
    send(@win, display, new(@one, bitmap("1.jpg")), point(400,85)),    
    send(@win, display, new(@ans_box2, box(30, 30)), point(430,50)),
    send(@ans_box2, fill_pattern,colour(@default, RAND_2_R * 257, RAND_2_G * 257 , RAND_2_B * 257, rgb)),    
    send(@win, display, new(@two, bitmap("2.jpg")), point(435,85)),    
    send(@win, display, new(@ans_box3, box(30, 30)), point(465,50)),
    send(@ans_box3, fill_pattern,colour(@default, RAND_3_R * 257, RAND_3_G * 257 , RAND_3_B * 257, rgb)),    
    send(@win, display, new(@three, bitmap("3.jpg")), point(470,85)),    
    send(@win, display, new(@ans_box4, box(30, 30)), point(500,50)),
    send(@ans_box4, fill_pattern,colour(@default, RAND_4_R * 257, RAND_4_G * 257 , RAND_4_B * 257, rgb)),    
    send(@win, display, new(@four, bitmap("4.jpg")), point(505,85)),    
    send(@win, display, new(@ans_box5, box(30, 30)), point(535,50)),
    send(@ans_box5, fill_pattern,colour(@default, RAND_5_R * 257, RAND_5_G * 257 , RAND_5_B * 257, rgb)),    
    send(@win, display, new(@five, bitmap("5.jpg")), point(540,85)),    
    send(@win, display, new(@ans_box6, box(30, 30)), point(570,50)),
    send(@ans_box6, fill_pattern,colour(@default, RAND_6_R * 257, RAND_6_G * 257 , RAND_6_B * 257, rgb)),    
    send(@win, display, new(@six, bitmap("6.jpg")), point(575,85)),    
    send(@win, display, new(@ans_box7, box(30, 30)), point(605,50)),
    send(@ans_box7, fill_pattern,colour(@default, RAND_7_R * 257, RAND_7_G * 257 , RAND_7_B * 257, rgb)),  
    send(@win, display, new(@seven, bitmap("7.jpg")), point(610,85)),    
     
    % Получение и обработка ответа
    get(@win, confirm, Answer),
    (
        Answer = 'EXIT', exit; true
    ),
    split_string(Answer, ",", ",", Strings),
    make_int_list(Strings, Ints),

    % Проверка ответа
    make_list_by_index_list(Ints, RS, R_SORTED),
    make_list_by_index_list(Ints, GS, G_SORTED),
    make_list_by_index_list(Ints, BS, B_SORTED),
    length(R_SORTED, SHORT_LEN),
    show_answer(R_SORTED, G_SORTED, B_SORTED), 
    
    send(@win, display, new(@next, button(next,  message(@win, return, 'NEXT'))), point(550,350)),
    send(@win, display, new(@try_again, button(try_again, message(@win, return, 'TRYAGAIN'))), point(550, 380)),
    check_answer(R_SORTED, G_SORTED, B_SORTED, SHORT_LEN),
    
    % Переход к новому уровню или к тому же уровню сначала
    get(@win, confirm, WhatToDo),
    send(@ok, destroy),
    delete_old_objects,
    (
        WhatToDo = 'TRYAGAIN', 
        start_game(R_1, G_1, B_1, R_2, G_2, B_2, RS, GS, BS);
        WhatToDo = 'EXIT',
        exit;
        start_new_game

    ).


min(X, Y, X) :- X < Y, !.
min(_, Y, Y).


max(X, Y, Y) :- X < Y, !.
max(X, _, X).


% Обработать входной поток
make_int_list([], []).
make_int_list([X|T], [Z|Y]) :- number_string(Z, X), make_int_list(T, Y).


% По входным значениям сформировать список цветов
make_list_by_index_list([], _, []).
make_list_by_index_list([X|T], L, [Z|Y]) :- nth1(X, L, Z), make_list_by_index_list(T, L, Y).


% Проверить правильность ответа
check_answer(R, G, B, LEN) :- length(R, LEN), (is_ordered(R); is_ordered(G); is_ordered(B)), !, 
    send(@win, display, new(@ok, bitmap("ok_2.jpg")), point(500,130)).
check_answer(R, G, B, LEN) :-  
    send(@win, display, new(@ok, bitmap("wrong_2.jpg")), point(500,130)).


% Проверка на упорядоченность
is_ordered([]).
is_ordered([_]).
is_ordered([X,Y|T]) :- X =< Y, is_ordered([Y|T]).


% Очистка старой игры при переходе к новой
delete_old_objects() :-
    send(@box, destroy), send(@box2, destroy), send(@box3, destroy), send(@box4, destroy), send(@box5, destroy), 
    
    send(@ans_box1, destroy), send(@ans_box2, destroy), send(@ans_box3, destroy), send(@ans_box4, destroy), 
    send(@ans_box5, destroy), send(@ans_box6, destroy), send(@ans_box7, destroy), 
    
    send(@one, destroy), send(@two, destroy), send(@three, destroy), send(@four, destroy), 
    send(@five, destroy), send(@six, destroy), send(@seven, destroy),

    send(@try_again, destroy), send(@next, destroy).


% Показать введенный ответ
show_answer(R_SORTED, G_SORTED, B_SORTED) :-
    nth1(1, R_SORTED, ANS_R_1), nth1(1, G_SORTED, ANS_G_1), nth1(1, B_SORTED, ANS_B_1),
    nth1(2, R_SORTED, ANS_R_2), nth1(2, G_SORTED, ANS_G_2), nth1(2, B_SORTED, ANS_B_2),
    nth1(3, R_SORTED, ANS_R_3), nth1(3, G_SORTED, ANS_G_3), nth1(3, B_SORTED, ANS_B_3),
    send(@box2, fill_pattern,colour(@default, ANS_R_1 * 257, ANS_G_1 * 257 , ANS_B_1 * 257, rgb)),    
    send(@box3, fill_pattern,colour(@default, ANS_R_2 * 257, ANS_G_2 * 257 , ANS_B_2 * 257, rgb)),    
    send(@box4, fill_pattern,colour(@default, ANS_R_3 * 257, ANS_G_3 * 257 , ANS_B_3 * 257, rgb)).  


% Выход из игры
exit() :- send(@win, destroy), halt.