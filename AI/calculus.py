import numpy as np
from matplotlib import pyplot as plt
import sympy

x = sympy.Symbol('x')
exp = np.e**x

sums = 0
for i in range(10):
    numerator = exp.diff(x, i)
    numerator = numerator.evalf(subs={x:0})
    denominator = np.math.factorial(i)
    sums += numerator / denominator * x**i

print(exp.evalf(subs={x:0}) - sums.evalf(subs={x:0}))
xvals = np.linspace(0, 10, 100)

for xval in xvals:
    plt.plot(xval, exp.evalf(subs={x: xval}), 'bo', \
             xval, sums.evalf(subs={x: xval}), 'ro')

plt.show()
