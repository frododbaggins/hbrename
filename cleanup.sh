#!/bin/bash

for file in *
do
    newname=`./rename $file`
    if [ "$newname" != "$file" ]
    then
	mv --no-clobber -v ./$file ./$newname
    fi
done
