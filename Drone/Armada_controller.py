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
import time
import socket
import select
import termios
import re
import os
import subprocess

##
## Command line options
##

class Main:

  def __init__(self):
    self.host = '127.0.0.1'
    self.port = 4242
    self.team = 'Poney'
    self.process = []
    self.selected = None

  def parseCommandLine(self):
    try:
      argList = getopt.getopt(sys.argv[1:], "n:p:h:")
      for (arg, value) in argList[0]:
        if arg == "-n":
          self.team = value
        elif arg == "-p":
	  self.port = value
        elif arg == "-h":
	  self.host = value
    except getopt.GetoptError as e:
      print "-", e
      print "- Valid options are [-h HOST] [-p PORT] [-n TEAM]"
      print "- Default values are -h 127.0.01 -p 4242 -n Poney"
      sys.exit() 

  def ioMode(self):
    if os.isatty(0):
      attr = termios.tcgetattr(0)
      attr[3] = attr[3] & ~(termios.ECHO | termios.ICANON)
      termios.tcsetattr(0, termios.TCSANOW, attr)

  def spawnChild(self):
    self.selected = subprocess.Popen(["./Trantorian_to_Human_Interface.py",
      		     "-h", self.host, "-p", str(self.port), "-n", self.team],
		     stdout=subprocess.PIPE, stdin=subprocess.PIPE,
		     stderr=subprocess.PIPE)
    #self.selected = self.process[len(self.process) - 1]

  def loopAll(self):
    while True:
      (rlist, _, _) = select.select([sys.stdin, self.selected.stdout], [], [], 0.01)
      if rlist.count(sys.stdin) > 0:
	data = sys.stdin.read(1)
	if data == "\033":
	  data = sys.stdin.read(1)
	  data = sys.stdin.read(1)
	self.selected.stdin.write(data)
      if rlist.count(self.selected.stdout) > 0:
	sys.stdout.write(self.selected.stdout.readline())

if __name__ == "__main__":
  try:
    m = Main()
    m.ioMode()
    m.spawnChild()
    m.loopAll()
  except KeyboardInterrupt:
    pass

