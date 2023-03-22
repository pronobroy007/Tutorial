<!-- First, ensure that PHP is configured to allow file uploads. -->
<!-- In your "php.ini" file, search for the file_uploads directive, and set it to On: -->
<!-- file_uploads = On -->

<!DOCTYPE html>
<html>
<body>
    <form action="upload.php" method="post" enctype="multipart/form-data">
        Select image to upload:
        <input type="file" name="fileToUpload" id="fileToUpload">
        <br>
        <input type="submit" value="Upload Image" name="submit">
        <br>
    </form>
</body>
</html>
