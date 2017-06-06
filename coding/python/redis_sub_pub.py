import redis
import uuid
import sys
import threading
import os

r = redis.Redis()

user = None

def login():
    global user
    nickname = raw_input('Enter your nickname: ')
    if nickname is None or nickname == '':
        nickname = 'unknown'
    uid = uuid.uuid1().hex
    user = (nickname, uid)

def talk():
    global user
    msg_body = raw_input()
    msg = user[0] + ' says: ' + msg_body
    r.publish('room:pub', msg)

def inbox():
    x = r.pubsub()
    x.subscribe('room:pub')
    for msg in x.listen():
        print msg['data']

def main():
    global user
    login()
    r.set('room:user(%s)' % user[0], user[1])

    inbox_thread = threading.Thread(target=inbox)
    inbox_thread.start()

    try:
        while True:
            talk()
    except KeyboardInterrupt, e:
        print '\nbye!'
        r.delete('room:user(%s)' %user[0])
        os._exit(1)

if __name__ == '__main__':
    main()
