#!/bin/bash

# GCD function
gcd() {
    a=$1
    b=$2
    while [ $b -ne 0 ]; do
        temp=$b
        b=$((a % b))
        a=$temp
    done
    echo $a
}

echo "CALCULATOR"
echo "1. Addition"
echo "2. Subtraction"
echo "3. Multiply"
echo "4. Division"
echo "5. Power"
echo "6. Factorial"
echo "7. GCD"
echo "8. LCM"
echo "0. EXIT"

choice=1
while [ $choice -ne 0 ]
do
    echo "Enter your choice: "
    read choice
    case $choice in
        1)
            echo "Enter 2 numbers: "
            read a
            read b
            echo "Sum: $a + $b = $((a + b))"
            ;;
        2)
            echo "Enter 2 numbers: "
            read a
            read b
            echo "Difference: $a - $b = $((a - b))"
            ;;
        3)
            echo "Enter 2 numbers: "
            read a
            read b
            echo "Product: $a * $b = $((a * b))"
            ;;
        4)
            echo "Enter 2 numbers: "
            read a
            read b
            if [ $b -eq 0 ]; then
                echo "Division by 0 is not possible"
            else
                echo "Quotient: $a / $b = $((a / b))"
            fi
            ;;
        5)
            echo "Enter the base and exponent: "
            read a
            read b
            result=1
            for i in $(seq 1 $b); do
                result=$((result * a))
            done
            echo "Result: $result"
            ;;
        6)
            echo "Enter a number: "
            read a
            fact=1
            while [ $a -gt 0 ]; do
                fact=$((fact * a))
                a=$((a - 1))
            done
            echo "Factorial: $fact"
            ;;
        7)
            echo "Enter 2 numbers: "
            read a 
            read b
            echo "GCD = $(gcd $a $b)"
            ;;
        8)
            echo "Enter 2 numbers: "
            read a
            read b
            gcdval=$(gcd $a $b)
            echo "LCM = $((a * b / gcdval))"
            ;;
        0)
            echo "Exiting..."
            break
            ;;
        *)
            echo "Invalid Choice"
            ;;
    esac
done
