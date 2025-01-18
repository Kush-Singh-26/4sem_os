#!/bin/bash
array=(1 3 5 7 9 11 13 26)
echo "Original array: ${array[@]}"

len=${#array[@]}
for ((i = 0; i < len / 2; i++))
do
    temp=${array[i]}
    array[i]=${array[len-i-1]}
    array[len-i-1]=$temp
done

echo "Reversed array: ${array[@]}"

