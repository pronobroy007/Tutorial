<?php 


if(isset($_POST['submit']))
{
    $file_name = $_FILES['fileToUpload']['name'];

    //file_terget is path to stroe upload file.
    $file_terget = "File/".$file_name;
    
    $file_size = $_FILES['fileToUpload']['size'];
    $file_tmp = $_FILES['fileToUpload']['tmp_name'];
    $file_type = $_FILES['fileToUpload']['type'];
    $file_extension = pathinfo($_FILES['fileToUpload']['name'], PATHINFO_EXTENSION);
   
    echo "File Name : ".$file_name."<br>";
    echo "File Size : ".$file_size."<br>";
    echo "File Temp : ".$file_tmp."<br>";
    echo "File Type : ".$file_type."<br>";      
    echo "File Extension : ".$file_extension."<br>";

    //Check if file is alrady exist or not 
    if(file_exists($file_terget))
    {
        echo "File alrady exist!";
    }else 
    {
        if(move_uploaded_file($file_tmp, $file_terget))
        {
            echo "File is uploaded successfully!";
        }else
        {
            echo "File could not uploaded!";
        }
    }

}


?>
