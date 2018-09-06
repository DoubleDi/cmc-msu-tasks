# -*- coding: utf-8 -*-
from flexx import app, event, ui
import sys


class Panel(ui.Label):
    CSS = """
        .flx-Panel {background: #000000;color: #FFF; padding: 1px;}
        body {background: #fff68f;}
    """

class GraphicsApp(app.PyComponent):
    def init(self):
        View()



class View(ui.Widget):

    dd = 0

    def init(self):
        with ui.HBox():
            with ui.VBox(flex=10, orientation='vertical'):
                ui.Label(text='<center><b>Эксперимент автосервис</b></center>')
                # ui.Label(text='flex: 1, sub-flexes: 1, 2')
                with ui.HBox(flex=10, orientation='horizontal'):
                    with ui.VBox(flex=2, orientation='vertical'):
                        Panel(text='Число рабочих К:', flex=0.5)
                        self.k = ui.LineEdit(flex=0.5, placeholder_text='K',text='')
                        Panel(text='Шаг времени M:', flex=0.5)
                        self.m = ui.LineEdit(flex=0.5, placeholder_text='M', text='')
                        self.step = ui.Button(text='Шаг', flex=0.5)
                        self.end = ui.Button(text='До конца', flex=0.5)
                        self.exit = ui.Button(text='Выход', flex=0.5)
                    with ui.VBox(flex=8, orientation='vertical'):
                        self.profit = Panel(text='Общая прибыль на текущий момент:', flex=0.5)
                        self.day = Panel(text='День:', flex=0.5)
                        self.time = Panel(text='Время:', flex=0.5)
                        self.count = Panel(text='Среднее число свободных рабочих', flex=0.5)
                with ui.HBox(flex=10, orientation='horizontal'):
                        Panel(text='Цех1', flex=1)
                        Panel(text='', flex=2)
                        Panel(text='', flex=2)
                        Panel(text='', flex=2)
                        Panel(text='', flex=2)
                        Panel(text='', flex=2)
                        Panel(text='', flex=2)
                        Panel(text='', flex=2)
                        Panel(text='', flex=2)
                        Panel(text='', flex=2)
                        Panel(text='', flex=2)
                with ui.HBox(flex=0, orientation='horizontal'):
                        self.one_count = Panel(text='Число свободных рабочих:', flex=10)
                        self.one_profit = Panel(text='Прибыль:', flex=10)
                with ui.HBox(flex=10, orientation='horizontal'):
                        Panel(text='Цех2', flex=1)
                        Panel(text='', flex=2)
                        Panel(text='', flex=2)
                        Panel(text='', flex=2)
                        Panel(text='', flex=2)
                        Panel(text='', flex=2)
                        Panel(text='', flex=2)
                        Panel(text='', flex=2)
                        Panel(text='', flex=2)
                        Panel(text='', flex=2)
                        Panel(text='', flex=2)
                with ui.HBox(flex=0, orientation='horizontal'):
                        self.two_count = Panel(text='Число свободных рабочих:', flex=10)
                        self.two_profit = Panel(text='Прибыль:', flex=10)
                with ui.HBox(flex=10, orientation='horizontal'):
                        Panel(text='Цех3', flex=1)
                        Panel(text='', flex=2)
                        Panel(text='', flex=2)
                        Panel(text='', flex=2)
                        Panel(text='', flex=2)
                        Panel(text='', flex=2)
                        Panel(text='', flex=2)
                        Panel(text='', flex=2)
                        Panel(text='', flex=2)
                        Panel(text='', flex=2)
                        Panel(text='', flex=2)
                with ui.HBox(flex=0, orientation='horizontal'):
                        self.three_count = Panel(text='Число свободных рабочих:', flex=10)
                        self.three_profit = Panel(text='Прибыль:', flex=10)
                with ui.HBox(flex=0, orientation='horizontal'):
                        Panel(text='<center>Очередь необработанных заявок</center>', flex=10)
                with ui.HBox(flex=10, orientation='horizontal'):
                        Panel(text='A', flex=10)

    @event.reaction('step.mouse_click',)
    def make_step(self):
        print(self.world)
        if self.m.text.isnumeric():
            self.world += int(self.m.text)
        self.day.set_text('День:' + self.world)



def update_class():
    sys.exit(0)
        
class World:

    a = 1
    def __init__(self):
        pass



if __name__ == "__main__":
    sys.path.append('./flexx')
    application = app.launch(GraphicsApp)
    application.world = 1
    app.run()
