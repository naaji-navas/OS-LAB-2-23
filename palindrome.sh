
#NAJID NAVAS
#CS B
#20220064



# Shell script program check whether a string is palindrome or not.

#!/bin/bash
echo "Enter a String"
read string
reverse=""

len=${#string}
for (( i=$len-1; i>=0; i-- ))
do 
	reverse="$reverse${string:$i:1}"
done
if [ $string == $reverse ]
then
    echo "$string is palindrome"
else
    echo "$string is not palindrome"
fi

#ouput
#Enter a String Malayalam
#Malayalam is palindrome

