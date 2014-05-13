#Python looks up the variable name at the time the function is called
def create_multipliers():
	return [lambda x: i*x for i in range(5)]

for multiplier in create_multipliers():
	print multiplier(2)

print "-----"
#using a default argument works because default arguments are evaluated when the
#function is created, not when it is called
def create_multipliers_fixer():
	return [lambda x, i=i: i*x for i in range(5)]

for multiplier in create_multipliers_fixer():
	print multiplier(2)



print "-----"
#Consider
x = "before foo defined"
def foo():
	print x
x = "after foo was defined"

foo()

print "-----"
x = "before foo defined"
def foo(x=x):
	print x
x = "after foo was defined"

foo()
foo()
