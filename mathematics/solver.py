from sympy import *
x = Symbol('x', real=True)
print(solve(Eq(x**2 - 1, 0), x))
print(solve(x**2 > 4))

print(expand((x + 1)**2))


