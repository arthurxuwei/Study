import itertools

l = itertools.chain('ABC', 'DEFG')

print list(l)

l = itertools.product(range(2), repeat=3)

print list(l)
