#!/usr/bin/python

import time
import socket
import sys
import shlex
import subprocess
import random

print " - Launching Server"

command = "../zappy -c 1005 -x 100 -y 100"
f = open("./log_server", "w")
p = subprocess.Popen(shlex.split(command), stdout=f)

print ">> Server OK"
time.sleep(5)
print " - Launching Clients"

i = 0
clients = []
while i < 1000:
  host = '127.0.0.1'
  port = 4242
  s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  clients.append(s)
  try:
    s.connect((host, port))
  except socket.error as e:
    print "- Socket {0} error({1}): {2}".format(i, e.errno, e.strerror)
    clients.pop()
  clients[i].send("Poney\n")
  i += 1 

j = 0
while 1:
  j += 1
  i = 0
  time.sleep(2)
  print "- Send", j, "broadcast JE SUIS UN PONEY FRINGUANT!"
  while i < len(clients):
    clients[i].send("broadcast JE SUIS UN PONEY FRINGUANT!\n")
    i += 1

p.communicate()
time.sleep(20)
p.terminate()
