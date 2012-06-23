#!/bin/bash

echo "Poney"
tr -cd '[:alnum:]\n' < /dev/urandom | head -c1024
