import time

def line(func):
	def wrapper():
		print '----------'
		func()
		print '----------'
	return wrapper

def timeit(func):
	def wrapper():
		start = time.clock()
		func()
		end = time.clock()
		print 'Time Elapse: ', end - start
	return wrapper
	
@line
@timeit
def foo():
	print 'in foo()'
	for i in range(1, 100000):
		i = i * i;
foo()
