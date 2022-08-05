# coding: utf-8
import select
import socket
import queue
from time import sleep


server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.setblocking(False)

server_address = ('0.0.0.0', 20311)
print ('starting up on %s port %s' % server_address)
server.bind(server_address)
server.listen(5)
inputs = [server]
outputs = []
message_queues = {}

while inputs:
    print ('waiting for the next event')
    readable, writable, exceptional = select.select(inputs, outputs, inputs)

    for s in readable:
        if s is server:
            connection, client_address = s.accept()
            print ('connection from', client_address)
            connection.setblocking(0)
            inputs.append(connection)

            message_queues[connection] = queue.Queue()
        else:
            data = s.recv(1024)
            if data != '':
                print ('received "%s" from %s' % (data, s.getpeername()))
                message_queues[s].put(data)
                if s not in outputs:
                    outputs.append(s)
            else:
                print('closing', client_address)
                if s in outputs:
                    outputs.remove(s)
                inputs.remove(s)
                s.close()

                del message_queues[s]

    for s in exceptional:
        print('exception condition on', s.getpeername())
        # Stop listening for input on the connection
        inputs.remove(s)
        if s in outputs:
            outputs.remove(s)
        s.close()

        # Remove message queue
        del message_queues[s]

    sleep(1)