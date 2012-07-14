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
import os

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
      self.s.connect((host, int(port)))
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

    self.vision = ()
    self.gather = False
    self.lvl = 1
    if os.isatty(0):
      try:
        attr = termios.tcgetattr(0)
        attr[3] = attr[3] & ~(termios.ECHO | termios.ICANON)
        termios.tcsetattr(0, termios.TCSANOW, attr)
      except termios.error as e:
	pass
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
		("m", "pose thystame"),
		("q", "gather_all"),
		("w", "require_stones"),
		("e", "broadcast @all: IMMEDIATE VORTEX")]

  def monitor(self, l):
    """Retrieve select informations"""

    l.append(sys.stdin)
    (rlist, _, _) = select.select(l, [], [], 0.01)
    return rlist

  def getCmd(self, channel):
    """Associate commands and keys"""

    data = channel.read(1)
    if data == "":
      sys.exit()
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
    elif int(st) > 9:
      return "+"
    else:
      return st

  def printMe(self, line):
    """Print one line"""

    while len(line) > 0:
      print "[\033[00m"+self.printOrNot(str(line[0][0]))+"\033[00m"+\
	"\033[36m"+self.printOrNot(str(line[0][1]))+"\033[00m"+\
	"\033[30;01m"+self.printOrNot(str(line[0][2]))+"\033[00m"+\
	"\033[32;01m"+self.printOrNot(str(line[0][3]))+"\033[00m"+\
	"\033[33;01m"+self.printOrNot(str(line[0][4]))+"\033[00m"+\
	"\033[00;01m"+self.printOrNot(str(line[0][5]))+"\033[00m"+\
	"\033[34;01m"+self.printOrNot(str(line[0][6]))+"\033[00m"+\
	"\033[31;01m"+self.printOrNot(str(line[0][7]))+"\033[00m"+"]",
      line = line[1:]

  def printRcs(self, lvl):
    """Print stones"""

    print "\033[32mNiveau actuel :", lvl
    if lvl == 1:
      print "1 Linemate\033[00m"
    elif lvl == 2:
      print "2 Joueurs - 1 Linemate - 1 Deraumere - 1 Sibur\033[00m"
    elif lvl == 3:
      print "2 Joueurs - 2 Linemate - 1 Sibur - 2 Phiras\033[00m"
    elif lvl == 4:
      print "4 Joueurs - 1 Linemate - 1 Deraumere - 2 Sibur - 1 Phiras\033[00m"
    elif lvl == 5:
      print "4 Joueurs - 1 Linemate - 2 Deraumere - 1 Sibur - 3 Mendiane\033[00m"
    elif lvl == 6:
      print "6 Joueurs - 1 Linemate - 2 Deraumere - 3 Sibur - 1 Phiras\033[00m"
    elif lvl == 7:
      print "6 Joueurs - 2 Linemate - 2 Deraumere - 2 Sibur - 2 Mendiane - 2 Phiras - 1 Thystame\033[00m"
    elif lvl == 8:
      print "Elevation maximale atteinte\033[00m"

  def move_to(self, n, link):
    """Move to emiter"""

    print "\033[32mIncomming transmission!"
    if n == 0:
      print "I'm here captain!\033[00m"
    elif n == 1:
      print "Moving to North\033[00m"
      link.send("avance")
    elif n == 2:
      print "Moving to NW\033[00m"
      link.send("avance\ngauche\navance")
    elif n == 3:
      print "Moving to West\033[00m"
      link.send("gauche\navance")
    elif n == 4:
      print "Moving to SW\033[00m"
      link.send("gauche\navance\ngauche\navance")
    elif n == 5:
      print "Moving to South\033[00m"
      link.send("gauche\ngauche\navance")
    elif n == 6:
      print "Moving to SE\033[00m"
      link.send("droite\navance\ndroite\navance")
    elif n == 7:
      print "Moving to East\033[00m"
      link.send("droite\navance")
    elif n == 8:
      print "Moving to NE\033[00m"
      link.send("avance\ndroite\navance")

  def parseCmd(self, raw, link):
    """
    Pretty-print raw commands
      |||||||||||||||
       |||||||||||||
        |||||||||||
         |||||||||
          |||||||
           |||||
            |||
             |
      [01234567][ 1   5  ]
    """

    if raw == "":
      sys.exit()
    if raw[10:] == "@all: IMMEDIATE VORTEX":
      self.move_to(int(raw[8:9]), link)
      return None
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
      self.vision = vision[0]
      log = [0, 1]
      if i > 4:
	self.lvl = 2
	log.append(4)
      if i > 9:
	self.lvl = 3
	log.append(9)
      if i > 16:
	self.lvl = 4
	log.append(16)
      if i > 25:
	self.lvl = 5
	log.append(25)
      if i > 36:
	self.lvl = 6
	log.append(36)
      if i > 49:
	self.lvl = 7
	log.append(49)
      if i > 64:
	self.lvl = 8
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
      if self.gather == True:
	data = self.gatherAll(link)
      return None
    return raw

  def gatherRcs(self, rcs, n, link):
    """Gather a given resource"""

    while n > 0:
      link.send(rcs)
      n -= 1

  def gatherAll(self, link):
    """Gather all resources on a square"""

    self.gatherRcs("prend nourriture", self.vision[1], link)
    self.gatherRcs("prend linemate", self.vision[2], link)
    self.gatherRcs("prend deraumere", self.vision[3], link)
    self.gatherRcs("prend sibur", self.vision[4], link)
    self.gatherRcs("prend mendiane", self.vision[5], link)
    self.gatherRcs("prend phiras", self.vision[6], link)
    self.gatherRcs("prend thystame", self.vision[7], link)
    self.gather = False

  def loop(self, link):
    """Iter on stdin and socket"""

    while True:
      sys.stdout.flush()
      rlist = self.monitor([l.s])
      if rlist.count(sys.stdin) > 0:
	data = self.getCmd(sys.stdin)
	if data == None:
	  continue
	print "\033[34m-", data, "\033[00m"
	if data == "gather_all":
	  link.send("voir")
	  self.gather = True
	elif data == "require_stones":
	  self.printRcs(self.lvl)
	else:
	  link.send(data)
      if rlist.count(link.s) > 0:
	data = link.recv()
	data = self.parseCmd(data, link)
	if data != None:
	  print data

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
  except:
    pass
