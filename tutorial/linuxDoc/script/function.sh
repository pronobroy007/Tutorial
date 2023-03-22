#!/bin/bash

var1='A'
var2='B'

hello_world () 
{
    #$1 is value passing as argument
    echo "Value pass as argument is $1"

    #This is local variable 
    local var1="Hello"

    #This is Global variable 
    var2="World"

    echo "Inside function: var1: $var1, var2: $var2"

    return 55
}

echo "Before executing function: var1: $var1, var2: $var2"
hello_world 20
echo "Value return from function is $?"
echo "After executing function: var1: $var1, var2: $var2"
#................................................



#Another Way to return value form function.
my_function () {
  local func_result="Another way to return value"
  echo "$func_result"
}

func_result="$(my_function)"
echo $func_result
#................................................




