import csv
import matplotlib.pyplot as plt
from itertools import cycle
import math


class Colors:
    colors = {"b", "g", "r", "c", "m", "y", "k"}

    def __init__(self):
        self.current = cycle(Colors.colors)

    def next(self):
        return next(self.current)


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def add(self, b):
        res = Point(self.x, self.y)
        res.x += b.x
        res.y += b.y
        return res

    def turn(self, angle):
        new_x = math.cos(angle) * self.x + math.sin(angle) * self.y
        new_y = -math.sin(angle) * self.x + math.cos(angle) * self.y
        return Point(new_x, new_y)

    def plot(self, color="b"):
        plt.plot([self.x], [self.y], marker="o", color=color)


class Line:
    def __init__(self, a, b):
        self.a = a
        self.b = b

    def plot(self, color="b"):
        plt.plot([self.a.x, self.b.x], [self.a.y, self.b.y], color=color)


class Snap:
    def __init__(self, point, lines):
        self.point = point
        self.lines = lines

    def plot(self, color):
        self.point.plot(color)
        for line in self.lines:
            line.plot(color)


with open("data.txt", newline="") as csvfile:
    reader = csv.DictReader(csvfile, delimiter=",", quoting=csv.QUOTE_NONNUMERIC)

    snaps = []
    last = Point(0.,0.)
    for row in reader:
        o = Point(row["x"], row["y"])
        angle = 0.
        if not (abs(o.x - last.x) < 0.00001):
            angle = math.atan((o.y - last.y)/(o.x - last.x))

        last = o
        a = Point(row["ax"], row["ay"])
        b = Point(row["bx"], row["by"])

        a = a.turn(-angle)
        b = b.turn(-angle)
        oa = o.add(a)
        ob = o.add(b)

        ar = Point(row["arx"], row["ary"])
        br = Point(row["brx"], row["bry"])
        oar = o.add(ar.turn(-angle))
        obr = o.add(br.turn(-angle))

        snaps.append(Snap(o, [Line(oa, ob), Line(oar, obr)]))

    color = Colors()
    for snap in snaps:
        snap.plot(color.next())
    plt.show()
