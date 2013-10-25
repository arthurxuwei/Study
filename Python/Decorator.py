import time

def timeit(func):
	def wrapper():
		start = time.clock()
		func()
		end = time.clock()
		print 'Time Elapse: ', end - start
	return wrapper
	
@timeit
def foo():
	print 'in foo()'
	for i in range(1, 100000):
		i = i * i;
foo()
