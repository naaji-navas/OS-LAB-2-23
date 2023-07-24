#!/bin/bash

# This is a bash program to prnt the prime numbers upto a limit

is_Prime() {
  local num=$1
  if [ $num -lt 2 ];
  then
    return 1
  fi
  

  #check for the divisibilty from 2 to squre root of the number
  for ((i=2 ; i*i<=num ; i++))
  do
    if [ $((num % i )) -eq 0 ]
    then
      return 1
    fi
  done

  return 0
    

}

print_up_to_n(){
  local n=$1
  for (( num=2; num<=n; num++ ))
  do
    if is_Prime "$num"
    then
      echo  "$num "
    fi
  done
    
}

echo "Enter the limit  to check prime numbers"
read n
print_up_to_n "$n"
