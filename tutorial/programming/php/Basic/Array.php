<?php
    $cars = array('Volvo', 'BMW', 'Toyota');
    
    //Insert a value 
    $cars[3] = "Lambroghini";
    
    $aryCount = count($cars);

    for($n = 0; $n < $aryCount; $n++)
        echo $cars[$n]."<br>";
    echo "<br>";



    //Multi dimentional array..................................
    $cars = array
                (
                array("Volvo",22,18),
                array("BMW",15,13),
                array("Saab",5,2),
                array("Land Rover",17,15)
                );

    echo "Multi-Dimention array : <br>";
    echo $cars[0][0].": In stock: ".$cars[0][1].", sold: ".$cars[0][2].".<br>";
    echo $cars[1][0].": In stock: ".$cars[1][1].", sold: ".$cars[1][2].".<br>";
    echo $cars[2][0].": In stock: ".$cars[2][1].", sold: ".$cars[2][2].".<br>";
    echo $cars[3][0].": In stock: ".$cars[3][1].", sold: ".$cars[3][2].".<br>";
    echo "<br><br>";





    //Associative Arrays.......................................
    $age = array("Peter"=>"35", "Ben"=>"37", "Joe"=>"43");
    
    //Insert a value.
    $age["Pronab"] = "22";
    
    echo "Associative Array :<br>";
    foreach ($age as $key => $value) {
        echo "Name is $key and age is $value <br>";
    }
    echo "<br><br>";
?>

<!-- sort() - sort arrays in ascending order
rsort() - sort arrays in descending order
asort() - sort associative arrays in ascending order, according to the value
ksort() - sort associative arrays in ascending order, according to the key
arsort() - sort associative arrays in descending order, according to the value
krsort() - sort associative arrays in descending order, according to the key -->
