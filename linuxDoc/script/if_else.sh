#Every batch command have true(0) or false(1) value like : 
#ls | grep if_else    After execute this command if we execute this
#echo $? 	This will "0" if previous command is success else 1.
echo $? 
if (($? == 0))
then
	ls | grep if_else
fi


echo -e "Enter a Value -> \c"
read value

if  [ $value -eq 32 ]
then 
	echo "Value is 32"

elif [ $value -lt 32 ] && [ $value -gt 20 ]
then
	echo "Value less then 32"

elif [ $value -gt 32 -a $value -lt 50 ]
then
	echo "Value is grater then 32"
fi



a=3.3
b=3.2
[ "$a" = $b ]
echo -e "exit status fo previous check : \c"
echo $?




#-lt 	=	<
#-eq 	= 	==
#-ne	= 	!=
#-ge	=	>=
#-le	=	<=

#&& 	= 	AND
#-a 	= 	AND

#||	= 	OR
#-o	=	OR





