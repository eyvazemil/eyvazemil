<?php

	function error($msg) {
		echo "Error: $msg" . "<br/>";
		exit();
	}

	$db_hostname = "localhost";
	$db_username = "root";
	$db_password = "";

	$database_name = "First_database";

	// connect to the server
	$db_connected = new mysqli($db_hostname, $db_username, $db_password, $database_name);

	if(!$db_connected)
		error("Could not connect to MySQL server!");

	$query = "SELECT * FROM tUsers";
	$result = $db_connected->query($query);

	$rows_num = $result->num_rows;

	for($j = 0; $j < $rows_num; $j++) {
		$result->data_seek($j);
		$row = $result->fetch_array(MYSQLI_ASSOC);
		echo 'First name: ' . $row['first_name'] . '<br/>';
		echo 'Second name: ' . $row['second_name'] . '<br/>';
		echo 'Gender: ' . $row['gender'] . '<br/><br/>';
	}

	$result->close;
	$db_connected->close;

?>