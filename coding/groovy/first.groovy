println 'Hello, wrold!'

def collect = ['a','b','c']

collect << 'come on'

println collect
println collect - collect[0..2]

def map = ['name':'arthur', 'age':'3']

map.each({key, value-> println "$key:$value"})

def say = {word-> println "Hi, $word"}

say('groovy')