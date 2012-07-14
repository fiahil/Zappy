#!/bin/sh

for i in {0..10000} ;do
  ./string.sh | nc 127.0.0.1 4242
done
