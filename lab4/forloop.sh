#!/bin/bash
names=(one two three four five six)
for item in ${names[@]}; do
        echo -n $item | wc -c
done
~           
