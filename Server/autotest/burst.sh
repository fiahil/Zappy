#!/bin/sh

for i in {0..10000} ;do
  ./string.sh | nc 10.19.252.96 4242
done
