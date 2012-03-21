#!/bin/bash

renamed=0
if [ -e rename ]
then
    mv rename .rename
    renamed=1
else
    "rename executable not found"
fi

# Guard against missing rename executable
if [ -e ./.rename ]
then
    for file in *
    do
	newname=`./.rename $file`
	if [ "$newname" != "$file" ]
	then
	    mv --no-clobber -v ./$file ./$newname
	    touch ./$newname
	fi
    done
else
    echo "Rename executable not found."
    exit -2
fi

if [ $renamed -eq 1 ]
then
    mv .rename rename
fi
