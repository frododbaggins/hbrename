#!/bin/bash

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
fi
