#NAJID NAVAS
#CS B
#20220064


#!/bin/sh
# enter number
echo " Enter a number : "
read n1
factorial=1
n=$n1
while [ $n1 -gt 1 ]
do
	factorial=$((factorial*n1))
	n1=$((n1-1))
done
echo "FActorial of given number $n is : $factorial"

#output
# Enter a number : 5
#FActorial of given number 5 is : 120

