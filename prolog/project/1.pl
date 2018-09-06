start :- /* создаём диалоговое окно */
         new(DW, dialog('Окно моей программы')),
/* создаём поле Picture для вывода графических
фигур и задаём его размеры */
         new(Picture, picture),
         send(Picture, width(350)),
         send(Picture, height(350)),
/*добавляем в это диалоговое окно список
объектов*/send_list(DW,append, /*графическое поле*/
            [Picture,
/*поле для ввода ширины фигуры: заданы имя поля,
значение по умолчанию и min и мах ограничения */
            new(Width, int_item(width, low := 10,
                   high := 300, default := 150)),
/* аналогичное поле для высоты фигуры */
            new(Height,int_item(height, low := 10,
                  high := 300, default := 150))]).