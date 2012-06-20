#!/usr/bin/python

import time
import socket
import sys
import shlex
import subprocess
import random

print " - Launching Server"

command = "../zappy -c 1000 -x 100 -y 100 -t 1"
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

# "broadcast Je suis un gentil poney!",

cmd = ["voir",
       "avance",
       "gauche",
       "droite",
       "inventaire",
       "prend nourriture",
       "prend linemate",
       "prend deraumere",
       "pose deraumere",
       "incantation",
       "connect_nbr",
       "fork",
       "expulse"]

j = 0
while 1:
  j += 1
  i = 0
  rd = random.choice(cmd)
  time.sleep(2)
  print "- Send", j, rd
  while i < len(clients):
    clients[i].send("broadcast Je suis un gentil poney!\n")
    i += 1


p.communicate()
time.sleep(20)
p.terminate()
