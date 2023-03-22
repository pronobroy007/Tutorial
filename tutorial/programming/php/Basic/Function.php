<?php
    //Return a value from a function...............................
    function sum($var1, $var2)
    {
        return $var1 + $var2;
    }

    echo "Sum of two number : ".sum(10, 23)."<br>";



    //Function Default Argument................................
    function defFunc($val = 10)
    {
        echo "Value is ".$val."<br>";
    }

    defFunc();

    


    //Function Pass by Reference.................................
    function ref(&$var)
    {
        echo "Pass by Reference variable is change to 10<Br>";
        $var = 10;
    }

    $n = 0;
    ref($n);
    echo "Value of n is : ".$n."<Br>";
?>
