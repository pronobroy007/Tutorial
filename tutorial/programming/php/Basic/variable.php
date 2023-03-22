<?php
    echo "<h2>PHP is Fun!</h2>";
    echo "Hello world!<br>";
    echo "I'm about to learn PHP!<br>";
    echo "This ", "string ", "was ", "made ", "with multiple parameters.", "<br>";


    $var = "Variable";
    echo "Name of this variable is ".$var."<br>";

    /********************************************************* */
    /************** This is for Global variable *****************/
    $x = 4;
    $y = 5;

    function func()
    {
        global $x, $y;
        $y = $x + $y;
    }

    func();
    echo "Globl variable : ".$y."<br>"; 
    /************************************************************ */



    /********************************************************* */
    /****************** Output variable ************************/
    $txt = "W3Schools.com";
    echo "I love $txt <br>";
    /********************************************************* */






    
    //Const variable
    //Constants are Global
    define("constant", "hello world");
    echo "This is const variable : ".constant."<br>";

?>