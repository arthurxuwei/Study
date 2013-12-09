import urllib
import re

s = urllib.urlopen('http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing=63579').read()
m = re.search('\d+', s)
while True:
    url = 'http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing='+m.group()
    s = urllib.urlopen(url).read()
    print s
    m = re.search('\d+', s)
    
