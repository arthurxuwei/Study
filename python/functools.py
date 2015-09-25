import functools

#partial
def add(a, b):
    return a + b
    
plus3 = functools.partial(add, 3)
print plus3(4)
