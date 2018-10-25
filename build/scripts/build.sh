#!/bin/bash
SCRIPTFOLDER="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

TARGETS=("debug" "release" "armeabi-v7adebug" "armeabi-v7arelease" "x86_64debug" "x86_64release")

function join {
  local IFS="$1"
  shift
  echo "$*"
}

function help {
  echo "Usage:"
  echo -n `basename "$0"`
  echo -n " "
  echo `join "|" ${TARGETS[@]}`
}

function index_of {
  local item="$1"
  shift
  index=0
  while [ $# -gt 0 -a "$item" != "$1" ]; do
    let "index++"
    shift
  done
  if [ $# -eq 0 ]; then
    echo -1
  else
    echo $index
  fi
}

if [ $# -ne 1 ]; then
  help
  exit 1
fi

if [ `index_of "$1" "${TARGETS[@]}"` -lt 0 ]; then
  echo "$1 is not a valid target"
  help
  exit 1
fi

cd $SCRIPTFOLDER/../..
if [ ! -d bin ]; then
  mkdir bin
fi

cd bin
if [ ! -d $1 ]; then
  mkdir $1
fi

cd $1
$SCRIPTFOLDER/cmake$1
make
