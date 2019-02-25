[i for i in range(20) if i&1!=0]

def get():
	yield 0
	yield 1
	yield 2

generator = get();
print generator.next()
print generator.next()
print generator.next()


def fibonacci():
	a = b = 1
	yield a
	yield b
	while True:
		a, b = b, a+b
		yield b
		
		
for num in fibonacci():
	if num > 100: break
	print num,
