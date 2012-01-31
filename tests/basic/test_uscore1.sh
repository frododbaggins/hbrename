#!/bin/bash

if [ "$1" == "-d" ]
then
    echo "Test removing a single underscore "
    exit 0
fi

cd test-data-files
result=`../../rename filename_-rem.mp4`
if [ "$result" == "filename.mp4" ]
then
#    echo success
    exit 0
else
#    echo problem
    exit 1
fi
