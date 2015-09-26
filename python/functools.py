import functools

#partial
def add(a, b):
    return a + b
    
plus3 = functools.partial(add, 3)
print plus3(4)


from functools import update_wrapper
def wrap(func):
    def call_it(*args, **kwargs):
        """wrap func: call_it"""
        print 'before call'
        return func(*args, **kwargs)
    return call_it
    
@wrap
def hello():
    """say hello"""
    print 'hello, world'
    
from functools import update_wrapper
def wrap2(func):
    def call_it(*args, **kwargs):
        """wrap func: call_it2"""
        print 'before call'
        return func(*args, **kwargs)
    return update_wrapper(call_it, func)
    
@wrap2
def hello2():
    """test hello"""
    print 'hello world 2'
    
from functools import wraps
def wrap3(func):
    @wraps(func)
    def call_it(*args, **kwargs):
        """wrap func: call_it2"""
        print 'before call'
        return func(*args, **kwargs)
    return call_it

@wrap3
def hello3():
    """test hello 3"""
    print 'hello world 3'
    
hello()
print hello.__name__
print hello.__doc__

print 
hello2()
print hello2.__name__
print hello2.__doc__

print
hello3()  
print
import locale
sorted(['1','3','4','6','2'], key=functools.cmp_to_key(locale.strcoll))

@functools.total_ordering
class Num:
    def __eq__(self, other):
        return self.num == other.num
    def __lt__(self, other):
        return self.num < other.num
        
print dir(Num)
    

