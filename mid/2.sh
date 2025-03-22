#!/bin/bash

echo "Enter the range (a b): " 
read a
read b
for ((i=a; i<=b; i++))
do
    if ((i < 2)); then
        continue
    fi

    is_prime=1
    for ((j=2; j*j<=i; j++))
    do
        if ((i % j == 0)); then
            is_prime=0
            break
        fi
    done

    if ((is_prime == 1)); then
        echo "$i"
    fi
done
