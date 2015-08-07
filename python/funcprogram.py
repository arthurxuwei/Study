def outer():
	i = 10
	def inner():
		return i
	return inner
		
print outer()()


def outer():
	i = 10
	return (lambda : i)
	
print outer()()


print map(lambda x : x**2, [1,2,3,4,5,6])

print map(lambda x,y: x + y, [1,2,3], [4,5,6])

print map(None, [1,2,3], [1,2,3])
#equal
print zip([1,2,3], [1,2,3])

print filter(lambda x: x&1 != 0, [1,2,3,4,5,6,7,8,9,10])

print reduce(lambda x,y: x * y, [1,2,3,4,5])

//currying
def f(a):
    def g(b, c, d):
        print a,b,c,d
    return g

f1 = f(1)
f1(2,3,4,5)
 