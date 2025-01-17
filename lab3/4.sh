#!/bin/sh

echo "Enter the value of n:"
read n

a=0
b=1

echo "Fibonacci numbers less than or equal to $n:"
echo -n "$a"

while [ $b -le $n ]; do
  echo -n ", $b"
  temp=$((a + b))
  a=$b
  b=$temp

done
echo