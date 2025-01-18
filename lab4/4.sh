#!/bin/bash
array=(12 45 1 67 34 89 23 56 78)

echo "Original Array: ${array[@]}"


len=${#array[@]}

for ((i = 0; i < len - 1; i++)); do
    for ((j = 0; j < len - i - 1; j++)); do
        if [[ ${array[j]} -gt ${array[j+1]} ]]; then
            temp=${array[j]}
            array[j]=${array[j+1]}
            array[j+1]=$temp
        fi
    done
done

echo "Sorted Array: ${array[@]}"


second_smallest=${array[1]}
second_largest=${array[len-2]}

echo "Second Smallest Element: $second_smallest"
echo "Second Largest Element: $second_largest"

