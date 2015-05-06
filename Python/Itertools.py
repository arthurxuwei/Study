import itertools

#first partition
# count(start=0, step=1) -> 0,1,2,3....
for i in itertools.izip(itertools.count(1), ['a', 'b', 'c']):
	print i

# cycle('ABCD') -> A B C D A B C D...
i=0
for item in itertools.cycle(['a','b','c']):
	i+=1
	if i == 10:
		break
	print item
	
#repeat(10, 3) -> 10, 10, 10
for i in repeat('again', 5):
	print i

#second partition
#chain('ABC', 'DEF') -> A B C D E F
for i in itertools.chain('ABC', 'DEFG'):
	print i
	
#compress('ABCDEF', [1,0,1,0,1,1]) --> A C E F
for i in itertools.compress('ABCDEF', [1,0,1,0,1,1]):
	print i

# dropwhile(lambda x: x<5, [1,4,6,4,1]) --> 6 4 1
def should_drop(x):
    print 'Testing:', x
    return (x<1)

for i in itertools.dropwhile(should_drop, [ -1, 0, 1, 2, 3, 4, 1, -2 ]):
    print 'Yielding:', i

itertools.product(range(2), repeat=3)

itertools.permutations(range(3))

