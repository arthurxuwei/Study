from sympy import *

x = Symbol('x')
exp_x = exp(x)

sums = x
for i in range(10):
    numerator = exp_x.diff(x, i)
    numerator = numerator.evalf(subs={x: 0})
    denominator = factorial(i)
    sums += numerator / denominator * x**i

print(exp_x.evalf(subs={x: 0}) - sums.evalf(subs={x: 0}))

print(diff(cos(x), x))

print(integrate(cos(x), x))

print(integrate(exp(-x), (x, 0, oo)))
