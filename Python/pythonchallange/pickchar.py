
def charpick(s):
    t = ''
    for c in s:
        if c.isalpha():
            t += c
    print t

def doFile():
    fp = open('mass.data');
    for line in fp:
        for c in line:
            if c.isalpha():
                print c
    fp.close()

doFile()
