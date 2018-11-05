#!/usr/bin/env bash

if [[ -z $1 ]]; then
  echo "Usage: $0 BLOCKHEIGHT"
  exit
fi

if [ "$1" -eq "$1" ] 2>/dev/null; then
  sed -i -e "s/^max_height=.*$/max_height=$1/g" linearize.cfg
  ./linearize-hashes.py linearize.cfg > hashlist.txt
  ./linearize-data.py linearize.cfg
  rm hashlist.txt
else
  echo "BLOCKHEIGHT must be an integer"
  exit
fi
