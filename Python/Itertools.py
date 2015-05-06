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

itertools.product(range(2), repeat=3)

itertools.permutations(range(3))

