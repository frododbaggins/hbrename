#!/bin/bash

if [ "$1" == "-d" ]
then
    echo "Test name --.ext "
    exit 0
fi

cd test-data-files
result=`../../.rename --.mp4`
if [ "$result" == "--.mp4" ]
then
#    echo success
    exit 0
else
#    echo problem
    exit 1
fi
