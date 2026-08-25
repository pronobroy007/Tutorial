str0="hello world"
str1="hello world"
str2=""

if [ "$str1" = "$str0" ] 
then 
	echo "string match"
fi

if [ "$str1" != "$str2" ] 
then 	
	echo "string dosen't match"
fi

#Check if string is greater then 0 or not 
if [ -n "$str1" ]
then 
	echo "string is not null"
fi

#Check if string is 0 or not  
if [ -z "$str2" ] 
then 
	echo "string is null"
fi


