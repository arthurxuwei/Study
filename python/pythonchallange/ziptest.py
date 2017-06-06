import zipfile
import re
 
z = zipfile.ZipFile( 'channel.zip', 'r' )
r = re.compile( ' (\d*)$' )
nothing = 90052
cm = ''
 
for i in range( 1000 ):
    str = z.read( '%s.txt' % nothing )
    rslt = r.findall( str )
    cm += z.getinfo( '%s.txt' % nothing ).comment
    
    try:
        nothing = int( rslt[0] )
    except:
        break;
    print cm
