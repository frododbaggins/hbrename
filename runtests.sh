#!/bin/bash

export BASEDIR=$PWD
sanity_status=0
error_log_file=/tmp/hbrename-failure-text  # Location for detailed failure message
export error_log_file

#temporarily rename ``rename'' to ``.rename'' for tests
if [ -e rename ]
then
    mv -f rename .rename
else
    echo "rename executable was not found."
    echo "Please recreate executable (run \"make\") before running tests"
    exit 2
fi

if [ -e cleanup.sh ]
then
    mv -f cleanup.sh .cleanup.sh
else
    echo "cleanup.sh script was not found"
    echo "Please obtain cleanup.sh from a backup or other git revisions before running tests"
    exit 2
fi

# Function to remove temporarily renamed files and other cleanup work
function final_cleanup()
{
    cd $BASEDIR
    if [ -e .rename ]
    then
	mv -f .rename rename
    fi

    if [ -e .cleanup.sh ]
    then
	mv -f .cleanup.sh cleanup.sh
    fi

    rm -f $error_log_file
}
# Function to run tests in each test-type directory
function runtests()
{
#   Check that the function was called with the test-type directory
    invar=${1-"none"}
    if [ "$invar" == "none" ]
    then
	echo "No test-type directory specified!"
	return
    fi
    touch $error_log_file
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
	    cat $error_log_file
	    echo
	    cat /dev/null > $error_log_file
	    if [ "$1" == "sanity" ]
	    then
		sanity_status=1
		break
	    fi
	fi
    done
}

cd tests

echo "Running sanity test "
echo "------------------- "
runtests sanity

if [ $sanity_status -eq 1 ]
then
    final_cleanup
    exit 2
fi

echo "Running basic tests "
echo "------------------- "
runtests basic

echo "Running pathological tests "
echo "-------------------------- "
runtests pathological

final_cleanup
