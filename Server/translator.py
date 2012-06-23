#!/usr/bin/python

import time
import termios
import socket
import fcntl
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

cmds = [("0", "connect_nbr"),
	("1", "voir"),
    	("2", "inventaire"),
	("3", "expulse"),
	("4", "gauche"),
	("5", "avance"),
	("6", "droite"),
	("7", "incantation"),
	("8", "fork"),
	("9", "broadcast PONEEEYYYY!")]

cmdr = [("a", "z", "nourriture"),
    	("s", "x", "linemate"),
	("d", "c", "deraumere"),
	("f", "v", "sibur"),
	("g", "b", "mendiane"),
	("h", "n", "phiras"),
	("j", "m", "thystame")]

attr = termios.tcgetattr(0)
attr[3] = attr[3] & ~(termios.ECHO | termios.ICANON)
termios.tcsetattr(0, termios.TCSANOW, attr)

fl = fcntl.fcntl(0, fcntl.F_GETFL)
fcntl.fcntl(0, fcntl.F_SETFL, fl | os.O_NONBLOCK)

flag = 1
while flag:
  time.sleep(0.01)
  try:
    data = sys.stdin.read(1)
  except IOError:
    try:
      print s.recv(32768)
    except socket.error:
      continue
    continue
  data = getcmd(data, cmds, cmdr)
  if data == None:
    try:
      print s.recv(32768)
    except socket.error:
      continue
    continue
  if data[1] != "":
    print " -", data[0], data[1]
    s.send(data[0] + " " + data[1] + "\n")
  else:
    print " -", data[0]
    s.send(data[0] + "\n")
  try:
    print s.recv(32768)
  except socket.error:
    continue
