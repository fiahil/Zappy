#!/usr/bin/python

import time
import socket
import sys
import string
import subprocess

print " - Launching Client"

host = '127.0.0.1'
port = 4242
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
try:
  s.connect((host, port))
except socket.error as e:
  print " - Socket error({0}): {1}".format(e.errno, e.strerror)
  sys.exit()

s.send("Poney\n")
s.recv(32768);

cmd = "voir"

print " - Sending", cmd
s.send(cmd + "\n")
print " - Waiting for response"
print s.recv(32768);
