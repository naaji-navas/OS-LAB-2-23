## shell program to print the prime numbers up to a limit
## -------------------------------------------------------


echo "Enter the limit: "
read n

echo "The prime numbers up to $n are: "
for (( i=2; i<=n; i++ ))
do
    flag=0
    for (( j=2; j<i; j++ ))
    do
        if [ `expr $i % $j` -eq 0 ]
        then
            flag=1
            break
        fi
    done
    if [ $flag -eq 0 ]
    then
        echo $i
    fi
done
