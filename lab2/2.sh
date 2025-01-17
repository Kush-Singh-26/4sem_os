#!/bin/bash
echo "Enter 3 numbers "
read a
read b
read c
if [ $a -ge $b ] && [ $a -ge $c ] 
then
    echo "The greatest number = $a"
elif [ $b -ge $a ] && [ $b -ge $c ] 
then 
    echo "The greatest number = $b"
else    
    echo "The greatest number = $c"
fi