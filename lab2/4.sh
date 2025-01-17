#!/bin/bash
echo "Enter a character"
read char

case $char in
    [A-Z])
        echo "The character is an uppercase."
        ;;
    [a-z])
        echo "The character is an lowercase."
        ;;
    [0-9])
        echo "The character is a digit."
        ;;
    *)
        echo "The character is a special symbol."
        ;;
esac
    