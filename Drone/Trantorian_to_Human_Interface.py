#!/usr/bin/python
#
# Fiahil
# 10.07.2012
#
# Ninja

##
## imports
##

import getopt
import sys
import socket
import select
import termios

##
## Server Connection
##

class Link:
  """Enable async link to the server"""

  def __init__(self, (host, port, team)):
    """Initialize TCP connection and communication"""

    self.host = host
    self.port = port
    self.team = team
    self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
      self.s.connect((host, port))
    except socket.error as e:
      print "- Failure:", e.strerror
      sys.exit()

    self.s.recv(512)
    self.s.send(team + "\n")

  def send(self, string):
    """Send data to the server"""

    if (string != None):
      self.s.send(string + "\n")

  def recv(self):
    """Recv data and aggregate them"""

    data = self.s.recv(4096)
    ret = data
    while (len(data) == 4096):
      data = self.s.recv(4096)
      ret = ret + data
    return ret[:-1]

##
## Bridge user input
##

class Bridge:
  """Monitor file descriptor"""

  def __init__(self):
    """Set stdin to raw mode"""

    self.fdList = [sys.stdin]
    attr = termios.tcgetattr(0)
    attr[3] = attr[3] & ~(termios.ECHO | termios.ICANON)
    termios.tcsetattr(0, termios.TCSANOW, attr)
    self.keyMap = [
		("0", "connect_nbr"),
		("1", "voir"),
		("2", "inventaire"),
		("3", "expulse"),
		("4", "gauche"),
		("5", "avance"),
		("6", "droite"),
		("7", "incantation"),
		("8", "fork"),
		("9", "broadcast PONEY!"),
		("a", "prend nourriture"),
		("s", "prend linemate"),
		("d", "prend deraumere"),
		("f", "prend sibur"),
		("g", "prend mendiane"),
		("h", "prend phiras"),
		("j", "prend thystame"),
		("z", "pose nourriture"),
		("x", "pose linemate"),
		("c", "pose deraumere"),
		("v", "pose sibur"),
		("b", "pose mendiane"),
		("n", "pose phiras"),
		("m", "pose thystame")]

  def register(self, descriptor):
    """Register a file descriptor"""

    self.fdList.append(descriptor)

  def monitor(self):
    """Retrieve select informations"""

    (rlist, _, _) = select.select(self.fdList, [], [], 1.0)
    return rlist

  def getCmd(self, channel):
    """Associate commands and keys"""

    data = sys.stdin.read(1)
    for (key, value) in self.keyMap:
      if key == data:
	return value
    return None

  def loop(self, link):
    """Iter on stdin and socket"""

    while True:
      rlist = self.monitor()
      if rlist.count(sys.stdin) > 0:
	data = self.getCmd(sys.stdin)
	print "-", data
	link.send(data)
      if rlist.count(link.s) > 0:
	data = link.recv()
	if data == "": # TODO Placer dans parse voir
	  sys.exit()
	print data # TODO Parse voir

##
## Command line options
##

def parseCommandLine():
  host = '127.0.0.1'
  port = 4242
  team = 'Poney'
  
  try:
    argList = getopt.getopt(sys.argv[1:], "n:p:h:")
    for (arg, value) in argList[0]:
      if arg == "-n":
	team = value
      elif arg == "-p":
	port = value
      elif arg == "-h":
	host = value
  except getopt.GetoptError as e:
    print "-", e
    print "- Valid options are [-h HOST] [-p PORT] [-n TEAM]"
    print "- Default values are -h 127.0.01 -p 4242 -n Poney"
    sys.exit()
  
  print "- Options:"
  print "-- Host:", host
  print "-- Port:", port
  print "-- Team:", team

  return (host, port, team)

##
## Main
##

if __name__ == "__main__":
  try:
    l = Link(parseCommandLine())
    b = Bridge()
    b.register(l.s)
    b.loop(l)
  except KeyboardInterrupt:
    pass
