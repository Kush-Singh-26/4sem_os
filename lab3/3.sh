#!/bin/bash

echo "Enter a number : "
read n
ans=0
while [ $n -gt 0 ]
do
	ans=$(((ans * 10) + (n%10)))
	n=$((n / 10))
done

echo "$ans"
