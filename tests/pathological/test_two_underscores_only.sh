#!/bin/bash

if [ "$1" == "-d" ]
then
    echo "Test name __.ext "
    exit 0
fi

cd test-data-files
result=`../../rename __.mp4`
if [ "$result" == "__.mp4" ]
then
#    echo success
    exit 0
else
#    echo problem
    exit 1
fi
