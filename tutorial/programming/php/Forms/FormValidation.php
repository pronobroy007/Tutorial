<!-- forms : 1 -->

<html>
<body>
    <form method="post" action="<?php echo $_SERVER["PHP_SELF"];?>">
        Name: <input type="text" name="name"><br><br>
        E-mail: <input type="text" name="email"><br><br>
        Website: <input type="text" name="website"><br><br>
        Comment: <textarea name="comment" rows="5" cols="40"></textarea><br><br>

        <!-- Radio button -->
        Gender:
        <input type="radio" name="gender" value="female">Female
        <input type="radio" name="gender" value="male">Male
        <input type="radio" name="gender" value="other">Other
        <br><br>

        <input type="submit">
    </form>

</body>
</html>

<?php 
    $name = $email = $website = $comment = $gender = "";

    if($_SERVER['REQUEST_METHOD'] == "POST")
    {
        $name = valid_data($_POST['name']);
        $email = valid_data($_POST['email']);
        $website = valid_data($_POST['website']);
        $comment = valid_data($_POST['comment']);
        $gender = valid_data($_POST['gender']);

        echo "Name is ".$name."<br>";
        echo "email is ".$email."<br>";
        echo "Website is ".$website."<br>";
        echo "Comment is ".$comment."<br>";
        echo "Gender is ".$gender."<br>";
    }

    //Validation function.
    function valid_data($data)
    {
        /*  
            trim(string,charlist) 

            2nd paramete is optional.Specifies which characters to remove from the string.
            If omitted, all of the following characters are removed:
                "\0" - NULL "\t" - tab
                "\n" - new line
                "\x0B" - vertical tab
                "\r" - carriage return
                " " - ordinary white space
        */
        $data = trim($data);
        $data = stripslashes($data);    //The stripslashes() function removes backslashes.
        $data = htmlspecialchars($data);
        return $data;
    }

?>

<!------------------------------------------------------------------------------------- 
    Big Note on PHP Form Security

    The $_SERVER["PHP_SELF"] variable can be used by hackers!
    If PHP_SELF is used in your page then a user can enter a slash 
    (/) and then some Cross Site Scripting (XSS) commands to execute. 

    consider that a user enters the following URL in the address bar:
    http://www.example.com/test_form.php/%22%3E%3Cscript%3Ealert('hacked')%3C/script%3E

    In this case, the above code will be translated to:
    <form method="post" action="test_form.php/"><script>alert('hacked')</script>

    To avoid $_SERVER[] exploit use htmlspecialchars()
----------------------------------------------------------------------------------------->


<!---------------------------------------------------------------------------------------
    What is the htmlspecialchars() function?

    The htmlspecialchars() function converts special characters to HTML entities.
    This means that it will replace HTML characters like < and > with &lt; and &gt;.
    This prevents attackers from exploiting the code by injecting HTML or Javascript 
    code (Cross-site Scripting attacks) in forms. 
----------------------------------------------------------------------------------------->
