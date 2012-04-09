#!/bin/bash

if [ "$1" == "-d" ]
then
    echo "Test name ____.ext "
    exit 0
fi

cd test-data-files
result=`../../.rename ____.mp4`
if [ "$result" == "____.mp4" ]
then
#    echo success
    exit 0
else
#    echo problem
    echo "    Expected result : ____.mp4 Actual result: $result " > /tmp/hbrename-failure-text
    exit 1
fi
