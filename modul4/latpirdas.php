<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "pirdas";

if ($_GET["ldr_value"])
    $ldr_value = $_GET["ldr_value"];
$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql = "INSERT INTO prakpirdas (ldr_value) VALUES (" . $ldr_value . ")";

if ($conn->query($sql) === TRUE) {
    echo "DATA LDR VALUE BERHASIL DITAMBAHKAN";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}
$conn->close();
exit();
