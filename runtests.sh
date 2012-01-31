#!/bin/bash

# Function to run tests in each test-type directory
function runtests()
{
#   Living dangerously, no check on whether an argument was passed
    for file in `ls $1/*.sh`
    do
	bash $file
	if [ $? -eq 0 ]
	then
	    echo `./$file -d` : Passed
	else
	    echo `./$file -d` : Failed!
	fi
    done
}

cd tests

echo "Running sanity test "
echo "------------------- "
runtests sanity

echo "Running basic tests "
echo "------------------- "
runtests basic

echo "Running pathological tests "
echo "-------------------------- "
runtests pathological
