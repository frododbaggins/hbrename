#!/bin/bash

if [ "$1" == "-d" ]
then
    echo "Test with multiple non-contiguous underscores "
    exit 0
fi

result=`../.rename a_b_c_d-e.mp4`
if [ "$result" == "a_b_c_d.mp4" ]
then
#    echo success
    exit 0
else
#    echo problem
    echo "    Expected result : a_b_c_d.mp4 Actual result: $result " > $error_log_file
    exit 1
fi
