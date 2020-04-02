from sympy import solve, sqrt, lambdify, nonlinsolve
from sympy.abc import v, x, y, z
import matplotlib.pyplot as plt
from matplotlib.patches import Ellipse, Circle, Rectangle
import numpy
import math


l = 240.0
h = 180.0
figure = plt.subplot(111, aspect="equal")
rectangle = Rectangle(xy=numpy.array([-0.5 * l, -0.5 * h]), width=l, height=h)

print("Ellipse")
solution = solve(-1.0 * (0.5 * h) ** 2 + (2 * sqrt((0.5 * l) ** 2 + x ** 2) - 0.5 * h) ** 2 - l ** 2)
b = solution[1]
print(f"b = {solution}")
solution = solve((0.5 * l) ** 2 - x ** 2 + b ** 2)
a = solution[1]
print(f"a = {solution}")
solution = solve(x ** 2 - a ** 2 + b ** 2)
print(f"m = {solution}")
ellipse = Ellipse(xy=numpy.zeros(2), width=2 * a, height=2 * b)
ellipse.set_alpha(0.5)


# a = x
# b = y
solution = solve(
    [
        (2 * x - sqrt((0.5 * z + l) ** 2 + (0.5 * h) ** 2)) ** 2 - (0.5 * z) ** 2 - (0.5 * h) ** 2,
        x ** 2 - y ** 2 - (0.5 * l + 0.5 * z) ** 2,
    ],
    [x, y, z],
    dict=True,
)
print(solution)
for s in solution:
    print("--")
    print(s[x].subs(z, 0))
    print(s[y].subs(z, 0))
print()

# Solution 3 is equal to ellipsis above, when z equals 0
fx = lambdify(z, solution[2][x], "numpy")
fy = lambdify(z, solution[2][y], "numpy")
values = numpy.arange(start=-100.0, stop=200.0, step=10.0)
es = []
for v in values:
    es.append(Ellipse(xy=numpy.zeros(2), width=2 * math.fabs(fx(v)), height=2 * math.fabs(fy(v)), fill=False,))


print("Circle")
r = math.sqrt((0.5 * l) ** 2 + (0.5 * h) ** 2)
print(f"r = {r}")
circle = Circle(xy=numpy.zeros(2), radius=r)
circle.set_alpha(0.5)

figure.add_artist(ellipse)
figure.add_artist(circle)
figure.add_artist(rectangle)
for e in es:
    figure.add_artist(e)

plt.xlim(-l, l)
plt.ylim(-l, l)
plt.show()
