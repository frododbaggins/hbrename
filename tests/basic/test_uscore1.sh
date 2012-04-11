#!/bin/bash

if [ "$1" == "-d" ]
then
    echo "Test removing a single underscore "
    exit 0
fi

result=`../.rename filename_-rem.mp4`
if [ "$result" == "filename.mp4" ]
then
#    echo success
    exit 0
else
#    echo problem
    echo "    Expected result : filename.mp4 Actual result: $result " > $error_log_file
    exit 1
fi
