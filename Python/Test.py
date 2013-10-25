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
