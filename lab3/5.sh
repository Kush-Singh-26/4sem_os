#!/bin/sh

echo "Enter a number:"
read number

echo "Choose the sort order:"
echo "1. Ascending"
echo "2. Descending"
read choice

digits=$(echo $number | fold -w1 | tr '\n' ' ')

if [ "$choice" -eq 1 ]; then
  sorted=$(echo $digits | tr ' ' '\n' | sort -n | tr '\n' ' ')
  echo "Digits in ascending order: $sorted"
elif [ "$choice" -eq 2 ]; then
  sorted=$(echo $digits | tr ' ' '\n' | sort -nr | tr '\n' ' ')
  echo "Digits in descending order: $sorted"
else
  echo "Invalid choice. Please choose 1 or 2."
fi
