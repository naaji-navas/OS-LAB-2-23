
#NAJID NAVAS
#CS B
#20220064



# Program to Calculate Sum of N numbers

 #!/bin/sh
echo "Enter the value of N"
read N


sum=0

for((i=1;i<=N;i++))
do
	echo "Enter number $i:"
	read num
	sum=$((sum+num))
done

echo $sum

#output
#Enter the value of N:5
#Enter number 1:2
#Enter number 2:3
#Enter number 3:4
#Enter number 4:5
#Enter number 5:1
#sum:15

