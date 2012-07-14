#!/bin/sh

for i in {0..100} ;do
  ./stringM.sh | nc 127.0.0.1 4242 > /dev/null &
done
killall nc