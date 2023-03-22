<?php
    $x = 20;

    if($x == 10)
        echo "X is 10";
    elseif($x == 20)
        echo "X is 20";
    else
        echo "X is something";

    echo "<br>";

    switch ($x) {
        case 10:
            echo "X is 10";
            break;

        case 20:
            echo "X is 20";
            break;
            
        default:
            echo "X is something";
            break;
    }
?>