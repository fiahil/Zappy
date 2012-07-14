#!/bin/sh

for i in {0..100} ;do
  ./stringM.sh | nc 10.19.253.175 4444 > /dev/null &
done
killall nc