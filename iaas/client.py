from kazoo.client import KazooClient, KazooState

import logging
logging.basicConfig()

zk = KazooClient(hosts='10.69.82.234:2181')

@zk.add_listener
def connect_listener(state):
    if state == KazooState.LOST:
        print 'connect lost'
    elif state == KazooState.SUSPENDED:
        print 'being disconnected'
    else:
        print 'connected'

def watch_func(event):
    print 'Event:', event

def init_queue():
    print 'WATCH => /queue/start'
    
    if zk.exists('/queue') == None:
        print 'create /queue'
        zk.create('/queue', 'task-queue')
    else:
        print '/queue is exist'

def join_queue(x):
    print 'create /queue/x' + x + ' x' + x
    zk.create('/queue/x'+x, 'x'+x, ephemeral=True)
    is_completed()
    
def is_completed():
    size = 3
    length = len(zk.get_children('/queue'))
    print 'Queue complete: %s/%s' % (length,size)
    
    if length >= size:
        print 'create /queue/start'
        zk.create('/queue/start', 'start', ephemeral=True)
        
        
def do_one():
    print 'zk client start'
    zk.start()
    zk.exists('/queue/start', watch_func)
    print 'process'
    init_queue()
    join_queue('1')
    join_queue('2')
    join_queue('3')
    zk.stop()
    print 'zk client close'
    
do_one()