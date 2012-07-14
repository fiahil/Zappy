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
## Time manipulation option
##

def getCurTime(host, port):
  s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  try:
    s.connect((host, port))
    s.send("GRAPHIC\n")
    data = s.recv(4096)
    ma = re.search(re.compile("sgt ([0-9]+)\n"), data)
    while ma == None:
      data = s.recv(4096)
      ma = re.search(re.compile("sgt ([0-9]+)\n"), data)
    print "\033[31m- Time t:\033[33m", ma.groups()[0], "\033[00m"
  except socket.error as e:
    print "\033[31m- Failure", e.strerror, "\033[00m"

def setTime(value, host, port):
  s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  try:
    s.connect((host, port))
    s.send("GRAPHIC\n")
    data = s.recv(4096)
    ma = re.search(re.compile("sgt ([0-9]+)\n"), data)
    while ma == None:
      data = s.recv(4096)
      ma = re.search(re.compile("sgt ([0-9]+)\n"), data)
    s.send("sst " + str(int(ma.groups()[0]) + value) + "\n")
    data = s.recv(4096)
    ma = re.search(re.compile("sgt ([0-9]+)\n"), data)
    while ma == None:
      data = s.recv(4096)
      ma = re.search(re.compile("sgt ([0-9]+)\n"), data)
    print "\033[31m- Time t:\033[33m", ma.groups()[0], "\033[00m"
  except socket.error as e:
    print "\033[31m- Failure", e.strerror, "\033[00m"

##
## Main class
##

class Main:

  def __init__(self):
    self.host = '127.0.0.1'
    self.port = 4242
    self.team = 'Poney'
    self.process = []
    self.selected = 0

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
    print "\033[31m- Spawn new Drone\033[00m"
    self.process.append([subprocess.Popen(["./Trantorian_to_Human_Interface.py",
      "-h", self.host, "-p", str(self.port), "-n", self.team],
      stdout=subprocess.PIPE, stdin=subprocess.PIPE,
      stderr=subprocess.PIPE), False, True])

  def loopAll(self):
    while True:
      l = []
      for elt in self.process:
        l.append(elt[0].stdout)
      l.append(sys.stdin)
      (rlist, _, _) = select.select(l, [], [], 0.01)
      if rlist.count(sys.stdin) > 0:
	data = sys.stdin.read(1)
	if data == "\033":
	  data = sys.stdin.read(1)
	  data = sys.stdin.read(1)
	
	if data == "1":
	  self.spawnChild()
	  data = None
	if data == "=":
	  getCurTime(self.host, self.port)
	  data = None
	if data == "-":
	  setTime(5, self.host, self.port)
	  data = None
	if data == "0":
	  setTime(-5, self.host, self.port)
	  data = None
	if data == "2":
	  self.selected -= 1
	  if self.selected < 0:
	    self.selected = len(self.process) - 1
	  print "\033[31m- Switch to drone", self.selected, "\033[00m"
	  data = None
	if data == "3":
	  self.selected += 1
	  self.selected = self.selected % len(self.process)
	  print "\033[31m- Switch to drone", self.selected, "\033[00m"
	  data = None
	if data == "4":
	  print "\033[31m- Active drone id:", self.selected, "\033[00m"
	if data == "5":
	  print "\033[31m- Total active drones", len(self.process), "\033[00m"
	  data = None

	if len(self.process) > 0 and data != None:
	  self.process[self.selected][0].stdin.write(data)
      for elt in rlist:
	if elt != sys.stdin:
	  data = elt.readline()
	  if data == "":
	    for e in self.process:
	      if e[0].stdout == elt:
		print "\033[31m- Drone Disconnected\033[00m"
		if self.process[self.selected] == e:
		  self.selected = 0
		  print "\033[31m- Switch selection to drone 0\033[00m"
		self.process.remove(e)
	  sys.stdout.write(data)

if __name__ == "__main__":
  try:
    m = Main()
    m.ioMode()
    m.spawnChild()
    m.loopAll()
  except KeyboardInterrupt:
    pass

