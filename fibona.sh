
#NAJID NAVAS
#CS B
#20220064

# Shell Script Program to print Fibonacci Series

#! /bin/bash
echo "Enter the value of n"
read n
a=0
b=1
count=2
echo "Fibonacci series:"
echo $a
echo $b
while [ $count -le $n ]
do
fib=`expr $a + $b`
a=$b
b=$fib
echo $fib
count=`expr $count + 1`
done

#output
#Enter the value of n :5
#Fibonacci series:
#0
#1
#1
#2
#3
#5

