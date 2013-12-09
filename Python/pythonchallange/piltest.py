from PIL import Image
im = Image.open('oxygen.png')
def pilTest():
    print im.format, im.size, im.mode
    
pilTest()
pix = im.load()
s =  ''
for i in range(629):
    s += chr(pix[i, 47][0])

print s
