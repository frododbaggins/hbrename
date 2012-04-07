#!/bin/bash

if [ "$1" == "-d" ]
then
    echo "Basic sanity test - using one hyphen "
    exit 0
fi

cd test-data-files
result=`../../.rename aaa-bbb.ext`
if [ "$result" == "aaa.ext" ]
then
#    echo success
    exit 0
else
#    echo problem
    echo "    Expected result : aaa.ext Actual result: $result " > /tmp/hbrename-failure-text
    exit 1
fi
