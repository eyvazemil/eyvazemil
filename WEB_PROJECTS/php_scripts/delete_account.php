<?php

	session_start();

	$user_login = $_SESSION['login'];

	require_once("./server_connection.php");

	$server = new Server("../Resources/server_configuration.txt");
	$server->query_without_return("DELETE FROM users WHERE login = '$user_login'");

	recursively_remove_directory("../Mails/$user_login");
	
	header('Location: ../index.php');
	exit();

?>



<?php

	function recursively_remove_directory($path_to_directory) {
		$directories = glob("$path_to_directory/*");
		foreach($directories as $directory) {
			if(is_dir($directory))
				recursively_remove_directory($directory);
			else
				unlink($directory);
		}
		rmdir($path_to_directory);
	}

?>