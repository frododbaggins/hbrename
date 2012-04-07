#!/bin/bash

export BASEDIR=$PWD
echo $BASEDIR

#temporarily rename ``rename'' to ``.rename'' for tests
r_renamed=0
c_rename=0
if [ -e rename ]
then
    mv rename .rename
    r_renamed=1
else
    "rename executable not found"
fi

if [ -e cleanup.sh ]
then
    mv cleanup.sh .cleanup.sh
    c_renamed=1
else
    "cleanup.sh script not found"
fi

# Function to run tests in each test-type directory
function runtests()
{
#   Living dangerously, no check on whether an argument was passed
    touch /tmp/hbrename-failure-text  # Location for detailed failure message
    if [ ! -e /tmp/hbrename-failure-text ]
    then
	echo "Could not create error log file"
	exit 1
    fi
    for file in `ls $1/*.sh`
    do
	bash $file
	if [ $? -eq 0 ]
	then
	    echo `./$file -d` : Passed
	else
	    echo `./$file -d` : Failed!
	    cat /tmp/hbrename-failure-text
	    echo
	    cat /dev/null > /tmp/hbrename-failure-text # clear it for subsequent tests
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

cd -

if [ $r_renamed -eq 1 ]
then
    mv .rename rename
fi

if [ $c_renamed -eq 1 ]
then
    mv .cleanup.sh cleanup.sh
fi
