#!/bin/bash

fileName=$(find "/" -type f -wholename "$1")

if [[ "$fileName" == *"$1"* ]]
then
 	echo "$fileName" 
 	exit 0
else
 	exit 1
fi


