#!/bin/bash

if [ "$1" == "-d" ]
then
    echo "Test name __.ext "
    exit 0
fi

result=`../.rename __.mp4`
if [ "$result" == "__.mp4" ]
then
#    echo success
    exit 0
else
#    echo problem
    echo "    Expected result : __.mp4 Actual result : $result "  > $error_log_file
    exit 1
fi
