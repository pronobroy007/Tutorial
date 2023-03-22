<!-- A cookie is often used to identify a user. A cookie is a small file that the 
server embeds on the user's computer. Each time the same computer requests 
a page with a browser, it will send the cookie too. With PHP, 
you can both create and retrieve cookie values. -->


<?php
    $cookie_name = "user";
    $cookie_value = "John ";
    
    //Setting a cookie.
    setcookie($cookie_name, $cookie_value, time() + (86400 * 30), "/"); // 86400 = 1 day

    //Delete a cookie.
    setcookie($cookie_name, "", time() - 3600, "/");
?>
  
<html>
<body>
<?php   
    if(!isset($_COOKIE[$cookie_name])) {
        echo "Cookie named '" . $cookie_name . "' is not set!";
    } else {
        echo "Cookie '" . $cookie_name . "' is set!<br>";
        echo "Value is: " . $_COOKIE[$cookie_name];
    }
?>  
</html>
</body>
