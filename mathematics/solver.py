from sympy import *
init_printing(use_unicode=True)
x = Symbol('x', real=True)

print(diff(sin(x)*exp(x), x))
t = Symbol('t', real=True)
print(solve(Eq(x**2 - 1, 0), x))
print(solve(x**2 > 4))

print(expand((x + 1)**2))

y = Function('y')
print(dsolve(Eq(y(t).diff(t, t) - y(t), exp(t)), y(t)))
