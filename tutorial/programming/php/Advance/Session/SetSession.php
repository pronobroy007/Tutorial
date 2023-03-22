<?php 
    //Strart a session.
    //The session_start() function must be the very first thing in your document. Before any HTML tags.
    session_start();

    //Set session variable.
    $_SESSION["name"] = "Pronab";
    $_SESSION["last_name"] = "Roy";
    echo "Session variable is set";  
?>