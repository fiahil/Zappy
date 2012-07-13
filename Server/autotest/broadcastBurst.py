#!/usr/bin/python

import time
import socket
import sys
import string
import subprocess

print " - Launching Clients"

host = '10.19.252.96'
port = 4242

i = 0
s = []
while (i < 300):
  s.insert(0, socket.socket(socket.AF_INET, socket.SOCK_STREAM))
  try:
    s[0].connect((host, port))
  except socket.error as e:
    print " - Socket error({0}): {1}".format(e.errno, e.strerror)
    sys.exit()
  s[0].send("Poney\n")
  s[0].recv(32768)
  print " - Client", i, "connected"
  i += 1

cmd = "broadcast PONEEEY!"

time.sleep(2)
print " - THIS"
time.sleep(0.5)
print " - IZ"
time.sleep(0.5)
print " - SPARTAAAAAAAAAAAAA"
time.sleep(0.5)


while (True):
  i = 0
  while (i < 300):
    print " - Sending", i, cmd
    s[i].send(cmd + "\n")
    i += 1
  print " - Next Round"
  time.sleep(5)
