#!/usr/bin/python

import time
import termios
import select
import socket
import sys
import os

def getcmd(data, cmds, cmdr):
  for elt in cmdr:
    if elt[0] == data:
      return ("prend", elt[2])
    if elt[1] == data:
      return ("pose", elt[2])

  for elt in cmds:
    if elt[0] == data:
      return (elt[1], "")

host = '10.19.252.96'
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

cmds = [("y", "connect_nbr"),
	("a", "voir"),
    	("z", "inventaire"),
	("t", "expulse"),
	("4", "gauche"),
	("8", "avance"),
	("6", "droite"),
	("r", "incantation"),
	("e", "fork"),
	("o", "broadcast PONEEEYYYY!")]

cmdr = [("q", "w", "nourriture"),
    	("s", "x", "linemate"),
	("d", "c", "deraumere"),
	("f", "v", "sibur"),
	("g", "b", "mendiane"),
	("h", "n", "phiras"),
	("j", ",", "thystame")]

attr = termios.tcgetattr(0)
attr[3] = attr[3] & ~(termios.ECHO | termios.ICANON)
termios.tcsetattr(0, termios.TCSANOW, attr)

flag = True
while flag:
  (rlist, _, _) = select.select([sys.stdin, s], [], [], 1.0)
  if rlist.count(sys.stdin) > 0:
    data = getcmd(sys.stdin.read(1), cmds, cmdr)
    if data == None:
      continue
    if data[1] != "":
      print " -", data[0], data[1]
      s.send(data[0] + " " + data[1] + "\n")
    else:
      print " -", data[0]
      s.send(data[0] + "\n")
  if rlist.count(s) > 0:
    data = s.recv(32768)
    if data != "":
      print data
    else:
      flag = False

