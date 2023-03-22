<?php 
    session_start();

    if(isset($_SESSION['name']))
    {
        echo "First name : ".$_SESSION['name']."<br>";
        echo "Last name : ".$_SESSION['last_name']."<br>";
    }
?>
