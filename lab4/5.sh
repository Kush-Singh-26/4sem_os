#!/bin/bash

array=(1 2 3 2 1)

echo "Original Array: ${array[@]}"

len=${#array[@]}

is_palindrome=1

for ((i = 0; i < len / 2; i++)); do
    if [[ ${array[i]} -ne ${array[len-i-1]} ]]; then
        is_palindrome=0
        break
    fi
done

if [[ $is_palindrome -eq 1 ]]; then
    echo "The array is a palindrome."
else
    echo "The array is not a palindrome."
fi

