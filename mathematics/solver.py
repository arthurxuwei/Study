from sympy import solve, Eq, Symbol
x = Symbol('x', real=True)
v = solve(Eq(x**2 - 1, 0), x)
print(v)
