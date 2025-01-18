#!/bin/bash

echo "Enter elements"
read -a array
echo "Original Array: ${array[@]}"

declare -A freq

for num in "${array[@]}"
do
    ((freq[$num]++))
done

echo "Element Frequencies:"
for key in "${!freq[@]}"
do
    echo "$key: ${freq[$key]}"
done

