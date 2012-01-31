#!/bin/bash

for file in *
do
    newname=`~/software/scr/rename $file`
    if [ "$newname" != "$file" ]
    then
	mv -v ./$file ./$newname
    fi
done
