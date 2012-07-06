#!/usr/bin/python

import random
import time
import termios
import select
import socket
import sys
import os
import time

def getcmd(data, cmds, cmdr):
  for elt in cmdr:
    if elt[0] == data:
      return ("prend", elt[2])
    if elt[1] == data:
      return ("pose", elt[2])

  for elt in cmds:
    if elt[0] == data:
      return (elt[1], "")

host = '127.0.0.1'
port = 4242
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
try:
  s.connect((host, port))
except socket.error as e:
  print " - Socket error({0}): {1}".format(e.errno, e.strerror)
  sys.exit()

s.setblocking(0)

s.send("Poney\n")
try:
  print s.recv(512)
except socket.error:
  pass

cmds = ["connect_nbr",
	"voir",
    	"inventaire",
	"expulse",
	"gauche",
	"avance",
	"droite",
        "prend nourriture",
        "pose nourriture",
	"incantation",
#	"fork",
	"broadcast PONEEEYYYY!"]

cmdr = ["nourriture",
    	"linemate",
	"deraumere",
	"sibur",
	"mendiane",
	"phiras",
	"thystame"]

flag = True
while flag:
  (rlist, wlist, _) = select.select([s], [s], [], 1.0)
  if wlist.count(s) > 0:
    data = random.choice(cmds)
    print " -", data
    s.send(data + "\n")
    s.send("prend nourriture\n")
  if rlist.count(s) > 0:
    data = s.recv(32768)
    if data != "":
      print data
    else:
      flag = False
#  time.sleep(1)
