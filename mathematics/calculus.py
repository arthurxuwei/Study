from matplotlib import pyplot as plt
import sympy

x = sympy.Symbol('x')
exp = sympy.exp(x)

sums = x
for i in range(10):
    numerator = exp.diff(x, i)
    numerator = numerator.evalf(subs={x: 0})
    denominator = sympy.factorial(i)
    sums += numerator / denominator * x**i

print(exp.evalf(subs={x: 0}) - sums.evalf(subs={x: 0}))


for xval in range(0, 20, 1):
    plt.plot(xval, exp.evalf(subs={x: xval}), 'bo', xval, sums.evalf(subs={x: xval}), 'ro')

plt.show()
