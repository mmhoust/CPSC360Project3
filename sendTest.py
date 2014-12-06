import socket
import sys
import time

try:
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
except socket.error:
    print 'failed to create socket'
    sys.exit()

host = '127.0.0.1'
flag = True
msg = 'GPS\0'
port = 5000
try:
    s.sendto(msg,(host,port))
    msg = 'DGPS\0'
    msg.rstrip()
    s.sendto(msg,(host,port))
    msg = 'MOVE\0'
    msg.rstrip()
    s.sendto(msg,(host,port))
    time.sleep(5)
    msg = 'STOP\0'
    msg.rstrip()
    s.sendto(msg,(host,port))
    time.sleep(1)
    msg = 'GPS\0'
    msg.rstrip()
    s.sendto(msg,(host,port))
    msg = 'DGPS\0'
    msg.rstrip()
    s.sendto(msg,(host,port))
    msg = 'TURN\0'
    msg.rstrip()
    s.sendto(msg,(host,port))
    time.sleep(1)
    msg = 'GPS\0'
    msg.rstrip()
    s.sendto(msg,(host,port))
    msg = 'DGPS\0'
    msg.rstrip()
    s.sendto(msg,(host,port))
    msg = 'STOP\0'
    msg.rstrip()
    s.sendto(msg,(host,port))
    time.sleep(1)
    msg = 'GPS\0'
    msg.rstrip()
    s.sendto(msg,(host,port))
    msg = 'DGPS\0'
    msg.rstrip()
    s.sendto(msg,(host,port))         
    msg = 'STOP\0'
    msg.rstrip()
    s.sendto(msg,(host,port))         
    time.sleep(1)
    msg = 'GPS\0'
    msg.rstrip()
    s.sendto(msg,(host,port))         
    msg = 'DGPS\0'
    msg.rstrip()
    s.sendto(msg,(host,port))
except socket.error:
        print 'fail'
        s.close()
        sys.exit()


