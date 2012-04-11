#!/bin/bash

if [ "$1" == "-d" ]
then
    echo "Test removing multiple underscores "
    exit 0
fi

result=`../.rename a________-rem.mp4`
if [ "$result" == "a.mp4" ]
then
#    echo success
    exit 0
else
#    echo problem
    echo "    Expected result : a.mp4 Actual result: $result " > $error_log_file
    exit 1
fi
