<!-- The include or require statement takes all the text/code/markup
that exists in the specified file and copies it into the file that uses the include statement

there is one big difference between include and require; when a file is included with the include
statement and PHP cannot find it, the script will continue to execute.

If we do the same example using the require statement, the echo statement will not be executed 
because the script execution dies after the require statement returned a fatal error. -->





<!-- Assume we have a standard footer file called "footer.php", that looks like this: -->
<?php
    echo "<p>Copyright &copy; 1999-" . date("Y") . " W3Schools.com</p>";
?>


<!-- To include the footer file in a page, use the include/require statement: -->
<html>
<body>
    <h1>Welcome to my home page!</h1>
    <p>Some text.</p>
    <p>Some more text.</p>
    <?php include 'footer.php';?>
</body>
</html> 