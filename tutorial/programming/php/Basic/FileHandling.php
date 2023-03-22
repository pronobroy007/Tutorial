<?php 
    echo readfile('hello.txt');
    echo "<br><br>";

    //A better method to open files is with the fopen() function.
    //This function gives you more options than the readfile() function.
    $file = fopen("hello.txt", "r") or die("Can not open file");
    echo fread($file, filesize("hello.txt"));
    fclose($file);

    //The fgetc() function is used to read a single character from a file.
    //The fgets() function is used to read a single line from a file
    //The feof() function checks if the "end-of-file" (EOF) has been reached.
    $file = fopen("hello.txt", "r") or die("Can not open file");
    while(!feof($file))
        echo fgets($file);
    fclose($file);


    /****************************************************************************** 
     *   r 	Open a file for read only. File pointer starts at the beginning of the file
     *   w 	Open a file for write only. Erases the contents of the file or creates a new file if it doesn't exist. File pointer starts at the beginning of the file
     *   a 	Open a file for write only. The existing data in file is preserved. File pointer starts at the end of the file. Creates a new file if the file doesn't exist
     *   x 	Creates a new file for write only. Returns FALSE and an error if file already exists
    ************************************************************************************/
    //Write a file
    $file = fopen("hello.txt", "w") or die("Can not open file");
    $text = "Hello world";
    fwrite($file, $text);
    fclose($file);

?>
