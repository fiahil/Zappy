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
import re

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

    attr = termios.tcgetattr(0)
    attr[3] = attr[3] & ~(termios.ECHO | termios.ICANON)
    termios.tcsetattr(0, termios.TCSANOW, attr)
    self.keyMap = [
		(";", "connect_nbr"),
		("k", "voir"),
		("l", "inventaire"),
		(".", "expulse"),
		("D", "gauche"),
		("A", "avance"),
		("C", "droite"),
		("/", "incantation"),
		("'", "fork"),
		(",", "broadcast PONEY!"),
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

  def monitor(self, l):
    """Retrieve select informations"""

    l.append(sys.stdin)
    (rlist, _, _) = select.select(l, [], [], 1.0)
    return rlist

  def getCmd(self, channel):
    """Associate commands and keys"""

    data = channel.read(1)
    if data == '\033':
      data = channel.read(1)
      data = channel.read(1)
    for (key, value) in self.keyMap:
      if key == data:
	return value
    return None

  def printOrNot(self, st):
    """Disable print 0"""

    if st == "0":
      return " "
    else:
      return st

  def printMe(self, line):
    """Print one line"""

    while len(line) > 0:
      print "[\033[31m"+self.printOrNot(str(line[0][0]))+"\033[00m"+\
	"\033[32m"+self.printOrNot(str(line[0][1]))+"\033[00m"+\
	"\033[33m"+self.printOrNot(str(line[0][2]))+"\033[00m"+\
	"\033[34m"+self.printOrNot(str(line[0][3]))+"\033[00m"+\
	"\033[35m"+self.printOrNot(str(line[0][4]))+"\033[00m"+\
	"\033[36m"+self.printOrNot(str(line[0][5]))+"\033[00m"+\
	"\033[37m"+self.printOrNot(str(line[0][6]))+"\033[00m"+\
	"\033[38m"+self.printOrNot(str(line[0][7]))+"\033[00m"+"]",
      line = line[1:]

  def parseCmd(self, raw):
    """Pretty-print raw commands"""

    if raw == "":
      sys.exit()
    if raw[:8] == "{ joueur":
      raw = raw[2:-1]
      lines = re.split(re.compile(","), raw)
      vision = []
      for elt in lines:
	tmp = re.split(re.compile(" "), elt)
	val = (len(re.findall(re.compile("joueur"), elt)),
	    len(re.findall(re.compile("nourriture"), elt)),
	    len(re.findall(re.compile("linemate"), elt)),
	    len(re.findall(re.compile("deraumere"), elt)),
	    len(re.findall(re.compile("sibur"), elt)),
	    len(re.findall(re.compile("mendiane"), elt)),
	    len(re.findall(re.compile("phiras"), elt)),
	    len(re.findall(re.compile("thystame"), elt)))
	vision.append(val)
      i = len(lines)
      log = [0, 1]
      if i > 4:
	log.append(4)
      if i > 9:
	log.append(9)
      if i > 16:
	log.append(16)
      if i > 25:
	log.append(25)
      if i > 36:
	log.append(36)
      if i > 49:
	log.append(49)
      if i > 64:
	log.append(64)
      j = 0
      while len(vision) > 0:
	val = log.pop()
	if j != 0:
	  print "           " * j,
	else:
	  print "",
	self.printMe(vision[val:])
	vision = vision[:-(len(vision) - val)]
	print ""
	j += 1
      #|||||||||||||||
      # |||||||||||||
      #  |||||||||||
      #   |||||||||
      #    |||||||
      #     |||||
      #      |||
      #       |
      #[01234567][ 1   5  ]
      #
      # Slice {}
      # Split ,
      # Split " "
      # Fill
      return ""
    return raw

  def loop(self, link):
    """Iter on stdin and socket"""

    while True:
      rlist = self.monitor([l.s])
      if rlist.count(sys.stdin) > 0:
	data = self.getCmd(sys.stdin)
	print "\033[34m-", data, "\033[00m"
	link.send(data)
      if rlist.count(link.s) > 0:
	data = link.recv()
	print self.parseCmd(data)

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
    b.loop(l)
  except KeyboardInterrupt:
    pass
