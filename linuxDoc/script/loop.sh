###########################################################
#################	While loop   ##########################
count=0
echo "This is While Loop"
while ((count <= 10))
#while [ $count -lt 10 ]
do 
	echo $count 
	((count ++))
	#count=`expr $count + 1`
done






###########################################################
#################	Until loop   ##########################
#Until loop. Until loop get execute when condition is flase
#In while loop when condition is true it in get execute 
count=0
echo "This is Until loop"
until [ $count -gt 10 ] 
do
	echo $count
	count=`expr $count + 1`
done





###########################################################
#################	For loop   ##########################
echo "This is 1st For loop"
echo "----------------------"
#Here "*" mean all file and folder in currnet directory
#We also can use ls like "for item in `ls`"
for item in *		
do 
	echo -e "$item \c"
done
echo ""
echo ""


#***********************************************************************
#Print 1 to 10.
echo "This is 2st For loop"
echo "----------------------"
for item in $(seq 10)
do
	echo -e "$item \c"
done
echo ""
echo ""
#***********************************************************************
echo "This is 3rd For loop"
echo "----------------------"
for item in {1..10}
do
	echo -e "$item \c"
done
echo ""
echo ""



#***********************************************************************
echo "This is 4th For loop"
echo "----------------------"
for item in apple banana orange
do
	echo -e "$item \c"
done
echo ""
echo ""





