f = open('mass1.data')
import re


def pickchar():
    result = ''
    for line in f:
        m = re.findall("[a-z][A-Z]{3}[a-z][A-Z]{3}[a-z]", line)
        if len(m) == 0:
            pass
        else:
            for s in m:
                result += s[4]
    print result
    
pickchar()
f.close()
