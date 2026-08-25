echo "Enter a charecter : \c "
read char

case $char in 
[a-z])
	echo "This is lower case alphabel."
	;;

[A-Z])
	echo "This is upper case alphabel."
	;;

[0-9])
	echo "This is a digit."
	;;

*)
	echo "Invalid charecter"
	;;
esac
