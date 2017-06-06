/**
 * Created by arthur.xw on 2015/5/15.
 */

def out = new BufferedOutputStream(new FileOutputStream('text'))
out << new URL('http://www.baidu.com').openStream()
out.close()