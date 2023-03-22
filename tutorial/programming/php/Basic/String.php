<?php
    $var = "Hello world";

    echo "Length of string is : ".strlen($var)."<br>";
    echo "Total number of world is : ".str_word_count($var)."<br>";
    echo "Reverse of string is : ".strrev($var)."<br>";
    echo "Searches for a spacific text : ".strpos($var, "world")."<br>";
    echo "Replace world to hello : ".str_replace("world", "hello", $var)."<br>";
?>
