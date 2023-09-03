

#Function to check if a number is a  pallindrome or not
is_pallindrom(){
  local num=$1
  local reversed=0
  local original=$num
  while [ $num -gt 0]
  do
    digit=$((num%10))
    reversed=$((reversed * 10 + digit))
    num = $((num/10))
  done

if [ $original -eq $reversed ];
then
    echo "it is a pallindrome" 
else
    echo "it is not  a pallindrome" 
fi
}

echo "Enter the string to check the pallindrome"
read string
if is_pallindrom  $string then
echo $i
fi
end
