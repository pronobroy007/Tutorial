#This wont create any new line after print.
echo -e "resutl : \c"

#This "val" will have number of ".zip" file have in current folder.
val=`ls | grep "\.zip" | wc -l`

val=`echo $line|cut -f1`

folder=${file//.zip}
	#This line will cut ".zip" from file name so that we can create a folder 
	#Ex: hello.zip	This line wiil cut .zip so we left with "hello" now we extrect zip file in hello folder




for file in $(ls | grep .zip)
do
	#This line will cut ".zip" from file name so that we can create a folder 
	#Ex: hello.zip	This line wiil cut .zip so we left with "hello" now we extrect zip file in hello foldeer
	folder=${file//.zip}
	mkdir $folder
	# -d = distination path.
	unzip $file -d $folder
done




********************************************
*	Inside "jul-9.txt"		
****************************************
*220  *  
*150  *   
*25   * 
********
resutl=0
for line in `cat jul-9.txt`
do
	#val will have number of eatch line in jul-9.txt.
	val=`echo $line|cut -f1`
	result=`expr $result + $val`
done
echo "Total amoutn : "
echo $result














