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
	
# [k for k, g in groupby('AAAABBBCCDAABBB')] --> A B C D A B
# [list(g) for k, g in groupby('AAAABBBCCD')] --> AAAA BBB CC D
for i, k in itertools.groupby(a, len):
    print i, list(k)

# ifilter(lambda x: x%2, range(10)) --> 1 3 5 7 9
def check_item(x):
    print 'Testing:', x
    return (x<1)

for i in ifilter(check_item, [ -1, 0, 1, 2, 3, 4, 1, -2 ]):
    print 'Yielding:', i
# ifilterfalse(lambda x: x%2, range(10)) --> 0 2 4 6 8

# islice('ABCDEFG', 2) --> A B
# islice('ABCDEFG', 2, 4) --> C D
# islice('ABCDEFG', 2, None) --> C D E F G
# islice('ABCDEFG', 0, None, 2) --> A C E G	
print 'Stop at 5:'
for i in islice(count(), 5):
    print i

print 'Start at 5, Stop at 10:'
for i in islice(count(), 5, 10):
    print i

print 'By tens to 100:'
for i in islice(count(), 0, 100, 10):
    print i
	
itertools.product(range(2), repeat=3)

itertools.permutations(range(3))

