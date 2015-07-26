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

# imap(pow, (2,3,10), (5,2,3)) --> 32 9 1000
for i in imap(lambda x:2*x, xrange(5)):
    print i

for i in imap(lambda x,y:(x, y, x*y), xrange(5), xrange(5,10)):
    print '%d * %d = %d' % i
	
# starmap(pow, [(2,5), (3,2), (10,3)]) --> 32 9 1000
values = [(0, 5), (1, 6), (2, 7), (3, 8), (4, 9)]
for i in starmap(lambda x,y:(x, y, x*y), values):
    print '%d * %d = %d' % i

# like linux tee
r = islice(count(), 5)
i1, i2 = tee(r)

for i in i1:
    print 'i1:', i
for i in i2:
    print 'i2:', i
	
# takewhile(lambda x: x<5, [1,4,6,4,1]) --> 1 4
def should_take(x):
    print 'Testing:', x
    return (x<2)

for i in takewhile(should_take, [ -1, 0, 1, 2, 3, 4, 1, -2 ]):
    print 'Yielding:', i
	
# izip('ABCD', 'xy') --> Ax By
for i in izip([1, 2, 3], ['a', 'b', 'c']):
    print i

# izip_longest('ABCD', 'xy', fillvalue='-') --> Ax By C- D-

#part three
# product('ABCD', 'xy') --> Ax Ay Bx By Cx Cy Dx Dy
# product(range(2), repeat=3) --> 000 001 010 011 100 101 110 111
a = (1, 2, 3)
b = ('A', 'B', 'C')
c = itertools.product(a,b)
for elem in c:
    print elem

# permutations('ABCD', 2) --> AB AC AD BA BC BD CA CB CD DA DB DC
# permutations(range(3)) --> 012 021 102 120 201 210
itertools.permutations(range(3))

# combinations('ABCD', 2) --> AB AC AD BC BD CD
# combinations(range(4), 3) --> 012 013 023 123
# combinations_with_replacement('ABC', 2) --> AA AB AC BB BC CC

#part four : extention
 