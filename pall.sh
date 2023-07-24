#!/bin/bash
# this is a code for checking the pallindrome

echo "Enter the String :"
read string
reverse=""

len=${#string}
echo $len

for(( i=$len-1; i>=0; i--))
do
  reverse="$reverse${string:$i:1}"
done
if [ $string == $reverse ]
then
  echo "$string is pallindrome"
else
  echo "$string is not pallindrome"
fi