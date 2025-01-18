#!/bin/bash
array1=(1 3 5 7 9 11 13 26) 
array2=(0 2 4 6 8 34)

echo "Array 1 : ${array1[@]}"
echo "Array 2 : ${array2[@]}"

len1=${#array1[@]}
len2=${#array2[@]}

i=0
j=0

array3=()

while [[ $i -lt $len1 &&  $j -lt $len2 ]]
do
	if [[ ${array1[i]} -lt ${array2[j]} ]]; then
		array3+=("${array1[i]}")
		((i++))
	else
		array3+=("${array2[j]}")
		((j++))
	fi
done

while [[ $i -lt $len1 ]]
do
	array3+=("${array1[i]}")	
	((i++))
done

while [[ $i -lt $len2 ]]
do
	array3+=("${array2[i]}")	
	((i++))
done

	
echo "Merged array : ${array3[@]}" 
