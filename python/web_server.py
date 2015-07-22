# -*- coding: utf-8 -*-    
from BaseHTTPServer import HTTPServer, BaseHTTPRequestHandler
from log import logger
from utils.util import *
import shutil
import nqpconf
import os
import json
from subprocess import Popen

class ScanException(Exception):
    pass

def controller(func):
    def replacement(req):
        func(req)
    return replacement
    
class Router(object):
    def __init__(self):
        self.routers = {}
        
    def add_route(self, path, controller):
        self.routers[path] = controller
        
    def __call__(self, req):
        path = req.path.strip('/')
        logger.info('request path: %s' % path)
        if path in self.routers:
            return self.routers[path](req)
        raise ScanException("Path not found")

def copyfile(source, outputfile):
    """¿½±´ÎÄ¼þ
    """
    shutil.copyfileobj(source, outputfile)
        
def get_file_header(req):
    f = None
    try:
        # Always read in binary mode. Opening files in text mode may cause
        # newline translations, making the actual size of the content
        # transmitted *less* than the content-length!
        f = open(nqpconf.ZONE, 'rb')
    except IOError:
        raise ScanException("file not found")
        return
    req.send_response(200)
    req.send_header("Content-type", 'application/json')
    fs = os.fstat(f.fileno())
    #req.send_header("Content-Length", str(fs[6]))
    req.send_header("Last-Modified", req.date_time_string(fs.st_mtime))
    
    return f
    
@controller
def get_file(req):
    file = get_file_header(req)
    if file:
        #copyfile(file, req.wfile)
        ret = {'success':True, 
           'error': '',
           'result':{'zone':nqpconf.ZONE, 'ips':''}
           }
            
        ret['result']['ips'] = file.read().replace('\n', ';')
        req.wfile.write(json.dumps(ret))
        file.close()
        
@controller
def do_task(req):
    try:
        p = Popen(['./scanner.py'])
        if p.pid:
            ret = {'success':True, 
               'error': '',
               'result':p.pid
               }
            req.send_response(200)
            req.end_headers()
            req.wfile.write(json.dumps(ret))
    except Exception as e:
        raise ScanException("Execute command error")


class TestHTTPHandler(BaseHTTPRequestHandler):
    def __init__(self, router, *args):
        self.router = router
        BaseHTTPRequestHandler.__init__(self, *args)
        
    def do_GET(self):
        ret = {'success':True, 
           'error': '',
           'result': ''
           }
        try:
            router(self)
        except Exception as e:
            import traceback
            print traceback.format_exc()
            self.send_response(200)
            self.end_headers()
            ret['success'] = False
            ret['error'] = '%s'%e
            self.wfile.write(json.dumps(ret))

class ScanHTTPServer:
    def __init__(self, (ip, port), router):
        def handler(*args):
            TestHTTPHandler(router, *args)
        server = HTTPServer((ip, port), handler)
        server.serve_forever()

class main:
    def __init__(self, (ip, port), router):
        self.server = ScanHTTPServer((ip, port), router)
    
if __name__ == '__main__':
    logger.info('server start')
    router = Router()
    router.add_route('getfile', controller=get_file)
    router.add_route('dotask', controller=do_task)
    m = main(('', 19999), router)