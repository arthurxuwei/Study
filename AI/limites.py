import sympy

x = sympy.Symbol('x', real = True)
f = lambda x: x**2-2*x-6
y = f(x)

print(y.limit(x, 1))
print(y.limit(x, sympy.oo))
