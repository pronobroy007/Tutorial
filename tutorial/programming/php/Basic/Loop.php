<?php
    $n = 0;


    //While Loop
    echo "While Loop: <br>";
    while ($n < 6) {
        echo "Iteration No. ".$n."<br>";
        $n++;
    }

    //Do While loop
    $n = 0;
    echo "<br>";
    echo "Do While loop: <br>";
    do {
        echo "Iteration No. ".$n."<br>";
        $n++;
    } while ($n <= 10);


    //For Loop 
    $n = 0;
    echo "<br>";
    echo "For loop: <br>";
    for($n = 0; $n < 5; $n++)
    {
        echo "Iteration No. ".$n."<br>";
    }


    //Foreatch loop
    echo "<br>";
    echo "Foreach loop: <br>";

    $colors = array("red", "green", "blue", "yellow");
    foreach ($colors as $value) {
        echo "$value <br>";
    }

?>
