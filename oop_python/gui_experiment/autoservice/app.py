import toga
from toga.style.pack import *
from toga.style import Pack
from toga.color import RED, BLUE
from toga.constants import COLUMN, ROW

import json
import random

# Графический интерфейс
class AutoserviceExperimentGUI(toga.App):
    # Отрисовка основного интерфейса
    def startup(self):
        self.main_window = toga.MainWindow(self.name, size=(800, 800))

        l1 = toga.Label('Эксперимент Автосервис', style=Pack(text_align=CENTER, width=800, height=25))

        lelf_label1 = toga.Label('Число рабочих К', style=Pack(text_align=LEFT, width=300, height=25))
        self.left_input1 = toga.TextInput(style=Pack(text_align=LEFT, width=250, height=25), placeholder='3')
        lelf_label2 = toga.Label('Шаг времени М (в часах)', style=Pack(text_align=LEFT, width=300, height=25))
        self.left_input2 = toga.TextInput(style=Pack(text_align=LEFT, width=250, height=25), placeholder='1')
        lelf_label3 = toga.Label('Вероятность появления авто (от 0 до 1)', style=Pack(text_align=LEFT, width=300, height=25))
        self.left_input3 = toga.TextInput(style=Pack(text_align=LEFT, width=250, height=25), placeholder='0.5')
        self.left_button1 = toga.Button('Шаг', style=Pack(text_align=CENTER,width=83,height=25), on_press=self.make_step)
        self.left_button2 = toga.Button('До конца', style=Pack(text_align=CENTER,width=83,height=25), on_press=self.to_end)
        self.left_button3 = toga.Button('Сначала', style=Pack(text_align=CENTER,width=83,height=25), on_press=self.restart)

        button_box = toga.Box(
            style=Pack(direction=ROW, width=250, height=25),
            children=[
                self.left_button1,
                self.left_button2,
                self.left_button3,
            ]
        )

        left1 = toga.Box(
            style=Pack(direction=COLUMN, width=300,height=200),
            children=[
                lelf_label1,
                self.left_input1,
                lelf_label2,
                self.left_input2,
                lelf_label3,
                self.left_input3,
                button_box,
            ]
        )

        self.right_label1 = toga.Label('Общая прибыль на текущий момент   0', style=Pack(text_align=LEFT, width=500, height=40))
        self.right_label2 = toga.Label('День   Понедельник', style=Pack(text_align=LEFT, width=500, height=40))
        self.right_label3 = toga.Label('Время   8:00', style=Pack(text_align=LEFT, width=500, height=40))
        self.right_label4 = toga.Label('Число свободных рабочих    0', style=Pack(text_align=LEFT, width=500, height=40))
        right1 = toga.Box(
            style=Pack(direction=COLUMN, width=300,height=200),
            children=[
                self.right_label1,
                self.right_label2,
                self.right_label3,
                self.right_label4
            ]
        )

        inner_box1 = toga.Box(
            style=Pack(direction=ROW, width=600),
            children=[
                left1,
                right1,
            ]
        )

        headings = ['id', 'Поломка', 'Осталось', 'Люди']
        self.table1 = toga.Table(
            headings=headings,
            data=[],
            style=Pack(width=250, height=150),
            # on_select=self.on_select_handler
        )

        self.table2 = toga.Table(
            headings=headings,
            data=[],
            style=Pack(padding_left=25, width=250, height=150),
            # on_select=self.on_select_handler
        )

        self.table3 = toga.Table(
            headings=headings,
            data=[],
            style=Pack(padding_left=25, width=250, height=150),
            # on_select=self.on_select_handler
        )

        inner_box3 = toga.Box(
            style=Pack(direction=ROW, width=800),
            children=[
                self.table1,
                self.table2,
                self.table3,
            ]
        )

        inner_box2 = toga.Box(
            style=Pack(direction=ROW, width=800),
            children=[
                toga.Label('Цех 1 (покрасочная)', style=Pack(text_align=CENTER, width=250, height=25)),
                toga.Label('Цех 2 (ремонт)', style=Pack(padding_left=25, text_align=CENTER, width=250, height=25)),
                toga.Label('Цех 3 (замена)', style=Pack(padding_left=25, text_align=CENTER, width=250, height=25))
            ]
        )


        self.workers1 = toga.Label('Число свободных рабочих: ', style=Pack(text_align=LEFT, width=250, height=25))
        self.workers2 = toga.Label('Число свободных рабочих: ', style=Pack(padding_left=25,text_align=LEFT, width=250, height=25))
        self.workers3 = toga.Label('Число свободных рабочих: ', style=Pack(padding_left=25,text_align=LEFT, width=250, height=25))
        inner_box4 = toga.Box(
            style=Pack(direction=ROW, width=800),
            children=[
                self.workers1,
                self.workers2,
                self.workers3,
            ]
        )

        self.profit1 = toga.Label('Прибыль:   0', style=Pack(text_align=LEFT, width=250, height=25))
        self.profit2 = toga.Label('Прибыль:   0', style=Pack(padding_left=25,text_align=LEFT, width=250, height=25))
        self.profit3 = toga.Label('Прибыль:   0', style=Pack(padding_left=25,text_align=LEFT, width=250, height=25))
        inner_box5 = toga.Box(
            style=Pack(direction=ROW, width=800),
            children=[
                self.profit1,
                self.profit2,
                self.profit3,
            ]
        )

        l2 = toga.Label('Очередь заявок', style=Pack(padding_top=25, text_align=CENTER, width=800, height=25))
        self.tree = toga.Tree(
            headings=['id', 'Марка авто', 'Цех', 'Поломка/Работа', 'Стоимость', 'Люди', 'Время работы (в часах)'],
            data=[ ],
            style=Pack(width=800, height=300),
            # on_select=self.on_select_handler
        )
        #  Create the outer box with 2 rows
        outer_box = toga.Box(
            style=Pack(direction=COLUMN, height=10, padding=25),
            children=[l1, inner_box1, inner_box2, inner_box3, inner_box4, inner_box5, l2, self.tree]
        )

        self.world = World()
        self.main_window.content = outer_box
        self.main_window.show()

    # Отрисовать новый шаг в интерфейсе
    def make_step(self, button, **args):
        self.left_input1.enabled = False
        self.left_input3.enabled = False
        while len(self.tree.data):
            self.tree.data.remove(self.tree.data[0])
        self.world.make_corrections(self.left_input1.value, self.left_input2.value, self.left_input3.value)
        if not args.get('nostep', False):
            self.world.make_step()

        for car in self.world.autoservice.waiting_cars:
            cc = self.tree.data.append(None, car.id, car.type, car.atelier, '', '', '', 'done' if car.is_done() else '')
            for r in car.requests:
                self.tree.data.append(cc, '', '', '', r.crash, r.cost, r.worker_need, r.time_need if r.time_need > 0 else 'done')

        self.table1.data.clear()
        for r in self.world.autoservice.design_atelier.work_list:
            self.table1.data.append(r.id, r.crash, r.time_need if r.time_need > 0 else 'done', r.worker_need)

        self.table2.data.clear()
        for r in self.world.autoservice.fix_atelier.work_list:
            self.table2.data.append(r.id, r.crash, r.time_need if r.time_need > 0 else 'done', r.worker_need)

        self.table3.data.clear()
        for r in self.world.autoservice.change_atelier.work_list:
            self.table3.data.append(r.id, r.crash, r.time_need if r.time_need > 0 else 'done', r.worker_need)

        self.right_label1.text = 'Общая прибыль на текущий момент   ' + str(self.world.autoservice.design_atelier.profit + \
            self.world.autoservice.fix_atelier.profit + self.world.autoservice.change_atelier.profit)
        self.right_label2.text = 'День   ' + self.world.day_map[str(self.world.day % 7)]
        self.right_label3.text = 'Время   ' + str(self.world.time + 8) +':00'
        self.right_label4.text = 'Число свободных рабочих    ' + ('0' if len(self.world.mid_free_master) == 0 else str(round(sum(self.world.mid_free_master) / float(len(self.world.mid_free_master)), 2)))
        
        self.profit1.text = 'Прибыль:   ' + str(self.world.autoservice.design_atelier.profit)
        self.profit2.text = 'Прибыль:   ' + str(self.world.autoservice.fix_atelier.profit)
        self.profit3.text = 'Прибыль:   ' + str(self.world.autoservice.change_atelier.profit)
        
        self.workers1.text = 'Число свободных рабочих: ' + str(len(list(filter(lambda w: w.is_free(), self.world.autoservice.workers[0]))))
        self.workers2.text = 'Число свободных рабочих: ' + str(len(list(filter(lambda w: w.is_free(), self.world.autoservice.workers[1]))))
        self.workers3.text = 'Число свободных рабочих: ' + str(len(list(filter(lambda w: w.is_free(), self.world.autoservice.workers[2]))))

        if self.world.day == 6 and self.world.time == 14 or self.world.day > 6:
            self.left_button1.enabled = False
            self.left_button2.enabled = False

    # Отрисовать конец эксперимента
    def to_end(self, button):
        self.world.make_corrections(self.left_input1.value, self.left_input2.value, self.left_input3.value)
        
        while self.world.day != 6 or self.world.time < 14:
            self.world.make_step()

        self.make_step(button)
        self.left_button1.enabled = False
        self.left_button2.enabled = False
    # Отрисовать эксперимент заново
    def restart(self, button):
        self.world = World()
        self.make_step(None, nostep=True)
        self.left_input1.enabled = True
        self.left_input3.enabled = True
        self.left_button1.enabled = True
        self.left_button2.enabled = True

# Мир
class World:
    
    def __init__(self, k = 3, m = 1, p = 0.5):
        self.time = 0 
        self.day = 0
        self.step = m
        self.mid_free_master = []

        with open('config.json', 'r+') as f:
            cfg = f.read()
            self.config = json.loads(cfg)
            self.day_map = self.config['day']

        self.autoservice = Autoservice(k, self.config)
        self.event_generator = EventGenerator(self.config, p)

    # Внести изменения внешних конфигурационных параметров
    def make_corrections(self, k, m, p):
        if k.isnumeric():
            self.autoservice.change_master_count(int(k))
        if m.isnumeric():
            self.step = int(m)
        if p.isnumeric():
            self.event_generator.rnd = int(p)

    # Сделать шаг в M часов
    def make_step(self):
        for _ in range(self.step):
            car = self.event_generator.generate_event()
            if not car is None:
                car = self.autoservice.get_price(car)
                self.autoservice.waiting_cars.append(car)
            
            self.autoservice.work()

            self.mid_free_master.append(len(list(filter(lambda w: w.is_free(), self.autoservice.workers[0]))))
            self.mid_free_master.append(len(list(filter(lambda w: w.is_free(), self.autoservice.workers[1]))))
            self.mid_free_master.append(len(list(filter(lambda w: w.is_free(), self.autoservice.workers[2]))))

        self.time += self.step
        if self.time > 14: # 8:00 - 22:00 = 14
            self.time = 0
            self.day += 1

# Автосервис
class Autoservice:

    def __init__(self, master_count = 3, config = {}):
        self.master_count = master_count
        self.price = config['price']
        self.cars = config['cars_price']

        self.design_atelier = Atelier(master_count, list(filter(lambda r: config['price'][r]['type'] == 'design', config['price'].keys())))
        self.fix_atelier = Atelier(master_count, list(filter(lambda r: config['price'][r]['type'] == 'fix', config['price'].keys())))
        self.change_atelier = Atelier(master_count, list(filter(lambda r: config['price'][r]['type'] == 'change', config['price'].keys())))
        self.waiting_cars = []
        self.workers = [ [  Master(self.design_atelier) for x in range(self.master_count) ], \
            [ Master(self.fix_atelier) for x in range(self.master_count) ], \
            [ Master(self.change_atelier) for x in range(self.master_count) ] ]

    # Получить цену 
    def get_price(self, car):
        for r in car.requests:
            r.cost = self.price[r.crash]['cost'] * self.cars[car.type]
            r.time_need = self.price[r.crash]['time_need']
            r.worker_need = self.price[r.crash]['worker_need']

        car.atelier = 0
        return car

    # Изменить число мастеров в каждом цеху 
    def change_master_count(self, k):
        if k == self.master_count:
            return
        elif k > self.master_count:
            for w in self.workers:
                for i in range(k - self.master_count):
                    w.append(Master(w[0].atelier))
        elif k < self.master_count:
            for w in self.workers:
                free_w = list(filter(lambda w: w.is_free(), w))[self.master_count - k]
                # TODO: not free delete
                w.remove(free_w)
        self.master_count = k

    # Выполнение всех работ в автосервисе 
    def work(self):
        self.get_new_jobs()
        for r in self.design_atelier.work_list:
            if r.is_done():
                self.design_atelier.work_list.remove(r)
                continue
            r.work()
            if r.is_done():
                workers = list(filter(lambda w: w.work == r, self.workers[0]))
                for w in workers:
                    w.sallary += r.cost * 0.1
                    w.work = None
            
                self.design_atelier.profit += r.cost * (1 - 0.1) 
        
                for car in self.waiting_cars:
                    if r in car.requests:
                        car.atelier = 0
                        break


        for r in self.fix_atelier.work_list:
            if r.is_done():
                self.fix_atelier.work_list.remove(r)
                continue
            r.work()
            if r.is_done():
                workers = list(filter(lambda w: w.work == r, self.workers[1]))
                for w in workers:
                    w.sallary += r.cost * 0.1
                    w.work = None

                self.fix_atelier.profit += r.cost * (1 - 0.1) 

                for car in self.waiting_cars:
                    if r in car.requests:
                        car.atelier = 0
                        break

        for r in self.change_atelier.work_list:
            if r.is_done():
                self.change_atelier.work_list.remove(r)
                continue
            r.work()
            if r.is_done():
                workers = list(filter(lambda w: w.work == r, self.workers[2]))
                for w in workers:
                    w.sallary += r.cost * 0.1
                    w.work = None

                self.change_atelier.profit += r.cost * (1 - 0.1)

                for car in self.waiting_cars:
                    if r in car.requests:
                        car.atelier = 0
                        break

    # Закончить выполненные работы 
    def finish_jobs(self):
        for car in self.waiting_cars:
            if car.atelier != 0:
                for r in car.requests:
                    if r.is_done() and car.atelier == 1:
                        self.design_atelier.profit += r.cost * (1 - 0.1) 
                        car.atelier = 0
                    if r.is_done() and car.atelier == 2:
                        self.fix_atelier.profit += r.cost * (1 - 0.1) 
                        car.atelier = 0
                    if r.is_done() and car.atelier == 3:
                        self.change_atelier.profit += r.cost * (1 - 0.1)
                        car.atelier = 0
        
    # Распределить новые заявки по своболным мастерам
    def get_new_jobs(self):
        for car in self.waiting_cars:
            free_design_workers = list(filter(lambda w: w.is_free(), self.workers[0]))
            free_fix_workers = list(filter(lambda w: w.is_free(), self.workers[1]))
            free_change_workers = list(filter(lambda w: w.is_free(), self.workers[2]))
            if car.atelier != 0:
                continue

            for r in car.requests:
                if r.is_done():
                    continue

                if r.crash in self.design_atelier.can_do and len(free_design_workers) >= r.worker_need:
                    self.design_atelier.work_list.append(r)   
                    for w in free_design_workers[:r.worker_need]:
                        w.work = r
                    car.atelier = 1
                    break

                elif r.crash in self.fix_atelier.can_do and len(free_fix_workers) >= r.worker_need:
                    self.fix_atelier.work_list.append(r)                    
                    for w in free_fix_workers[:r.worker_need]:
                        w.work = r
                    car.atelier = 2
                    break

                elif r.crash in self.change_atelier.can_do and len(free_change_workers) >= r.worker_need:
                    self.change_atelier.work_list.append(r)         
                    for w in free_change_workers[:r.worker_need]:
                        w.work = r
                    car.atelier = 3
                    break

# Цех
class Atelier:

    def __init__(self, master_count = 3, can_do = []):
        self.master_count = master_count
        self.can_do = can_do
        self.profit = 0

        self.work_list = []

# Рабочий
class Master:

    def __init__(self, atelier = None):
        self.sallary = 0
        self.work = None
        self.atelier = atelier

    # Свободен ли рабочий
    def is_free(self):
        return self.work is None


# Генератор событий (авто)
class EventGenerator:

    def __init__(self, config, p = 0.5):
        self.cars = list(config['cars_price'].keys())
        self.crashes = list(config['price'].keys())
        self.id = 1
        self.rnd = p

    # С некоторой вероятностью создать поломанную авто
    def generate_event(self):
        if random.random() <= self.rnd:
            return self.create_car()
        else:
            return None

    # Создать авто    
    def create_car(self):
        car_type = random.choice(self.cars)
        car_crashes_count = random.randint(1,3)
        car_crashes = set()

        while (len(car_crashes) < car_crashes_count):
            car_crashes.add(random.choice(self.crashes))

        car = Car(self.id, car_type, list(car_crashes))
        self.id += 1
        return car

# авто
class Car:

    def __init__(self, id, car_type = None, car_crashes = []):
        self.type = car_type
        self.requests = [ Request(id, x) for x in car_crashes ]
        self.id = id
    
    # Выполнены ли все работы над авто 
    def is_done(self):
        return len(list(filter(lambda r: not r.is_done(), self.requests))) == 0
        

# Заявка (Поломка авто)
class Request:

    def __init__(self, id, crash):
        self.crash = crash
        self.cost = 0
        self.time_need = 0
        self.worker_need = 0
        self.id = id
    
    # Выполнена ли поломка? 
    def is_done(self):
        return self.time_need <= 0

    # Работа над заявкой
    def work(self):
        if self.time_need >= 1:
            self.time_need -= 1

def main():
    app = AutoserviceExperimentGUI('Autoservice', 'org.pybee.widgets.buttons')
    return app
