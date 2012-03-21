#!/bin/bash

if [ "$1" == "-d" ]
then
    echo "Test name a-b-c.ext "
    exit 0
fi

cd test-data-files
result=`../../.rename a-b-c.mp4`
if [ "$result" == "a.mp4" ]
then
#    echo success
    exit 0
else
#    echo problem
    exit 1
fi
