<!-- forms : 2 -->

<?php 
    $nameErr = $emailErr = $genderErr = $websiteErr = "";
    $name = $email = $website = $comment = $gender = "";

    if($_SERVER['REQUEST_METHOD'] == "POST")
    {
        if (empty($_POST["name"])) {
          $nameErr = "Name is required";
        } else {
          $name = valid_data($_POST["name"]);
        }
    
        if (empty($_POST["email"])) {
          $emailErr = "Email is required";
        } else {
          $email = valid_data($_POST["email"]);
        }
    
        if (empty($_POST["website"])) {
          $website = "";
        } else {
          $website = valid_data($_POST["website"]);
        }
    
        if (empty($_POST["comment"])) {
          $comment = "";
        } else {
          $comment = valid_data($_POST["comment"]);
        }
    
        if (empty($_POST["gender"])) {
          $genderErr = "Gender is required";
        } else {
          $gender = valid_data($_POST["gender"]);
        }

        //Show all values
        if($nameErr == "" && $emailErr == "" && $genderErr == "" && $comment != "" && $website != "")
        {
            echo "Name is ".$name."<br>";
            echo "email is ".$email."<br>";
            echo "Website is ".$website."<br>";
            echo "Comment is ".$comment."<br>";
            echo "Gender is ".$gender."<br><br>";
        }
    }

    //Validation function.
    function valid_data($data)
    { 
        $data = trim($data);
        $data = stripslashes($data);    
        $data = htmlspecialchars($data);
        return $data;
    }
?>

<html>
<body>
    <form method="post" action="<?php echo $_SERVER["PHP_SELF"];?>">
        Name: <input type="text" name="name">
        <span class="error">* <?php echo $nameErr;?></span>
        <br><br>
        E-mail:
        <input type="text" name="email">
        <span class="error">* <?php echo $emailErr;?></span>
        <br><br>
        Website:
        <input type="text" name="website">
        <span class="error"><?php echo $websiteErr;?></span>
        <br><br>
        Comment: <textarea name="comment" rows="5" cols="40"></textarea>
        <br><br>
        Gender:
        <input type="radio" name="gender" value="female">Female
        <input type="radio" name="gender" value="male">Male
        <input type="radio" name="gender" value="other">Other
        <span class="error">* <?php echo $genderErr;?></span>
        <br><br>
        <input type="submit" name="submit" value="Submit"> 
    </form>

</body>
</html>


