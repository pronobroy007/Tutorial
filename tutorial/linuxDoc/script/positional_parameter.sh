#set=hello world    This is a positional parameter 
#echo $1    will print "hello" 
#echo $2    will pring "world"

for ARG in $*; do
    echo $ARG
done

echo $1 $2
echo "Total number of positional parameter : $#"

#Set a positional parameter
set `ls`
echo "Total number of file or directory present in currnet folder $#"


#Now we execute this shell script like this
#sh positional_parameter hello world.
#Then echo $1 == hello & $2 = world.

#If we execute like this
#sh positional_parameter `who am i` 
#Then echo $1 == root & $2 == terminal id.
