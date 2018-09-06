


:- module(pce_hsv_browser,
          [ hsv_browser/0
          ]).
:- use_module(library(pce)).

hsv_browser :-
    send(new(hsv_browser), open).


:- pce_begin_class(hsv_browser, dialog, "Browse colours in HSV model").

variable(current_colour, colour, get, "Current colour value").


initialise(D, Init:[colour]) :->
    send_super(D, initialise, 'Demonstrate HSV'),
    send(D, append, new(Box, box(100, 20))),
    send(Box, attribute, hor_stretch, 100),
    send(D, current_colour, colour(@default, 255 * 257, 125 * 0 , 125 * 0, rgb)).


current_colour(D, C:colour, From:[rgb]) :->
    "Set the current colour, updating all items"::
    send(D, slot, current_colour, C),
    get(D, member, box, Box),
    send(Box, fill_pattern, C).



rgb(R,G,B, colour(@default, Red, Green, Blue)) :-
    Red is R * 257,
    Green is G * 257,
    Blue is B * 257.

:- pce_end_class(hsv_browser).
