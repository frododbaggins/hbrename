#!/bin/bash

for file in *
do 
    mv -v $file `~/software/scr/rename $file`
done
