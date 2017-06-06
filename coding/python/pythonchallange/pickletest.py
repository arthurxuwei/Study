import pickle
import sys

f = open(r'banner.p', 'r')

m = pickle.Unpickler(f).load()
for x in m:
    for (a, b) in x:
        sys.stdout.write(a * b)

f.close()
