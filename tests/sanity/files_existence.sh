#!/bin/bash

if [ "$1" == "-d" ]
then
    echo "Basic sanity test - cleanup.sh and rename executable must exist"
    exit 0
fi

if [ -e "$BASEDIR/.cleanup.sh" ]
then
    if [ -e "$BASEDIR/.rename" ]
    then
	exit 0
    else
	exit 1
    fi
else
    exit 1
fi
