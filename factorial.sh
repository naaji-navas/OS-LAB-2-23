#!/bin/sh

echo "Enter a  number:"
read n
factorial=1
while [ $n -gt 1 ]
do
factorial=$((factorial*n))
n=$((n-1))
done
echo "Factorial of the given number $n is : $factorial"

