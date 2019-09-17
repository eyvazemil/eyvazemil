<?php

	session_start();

	$user_login = $_SESSION['login'];

	require_once("./server_connection.php");

	$password_changed_successfully = false;

	$master_error = false;
	$error_current_password = false;
	$blank_current_password = false;
	$blank_new_password = false;

	$user_current_password = "";
	$user_new_password = "";

	if(isset($_POST['user_current_password']))
		$user_current_password = $_POST['user_current_password'];

	if(isset($_POST['user_new_password']))
		$user_new_password = $_POST['user_new_password'];

	if($user_current_password !== "" && $user_new_password !== "") {
		$server = new Server("../Resources/server_configuration.txt");
		$row = $server->query("SELECT password FROM users WHERE login = '$user_login'");

		if($user_current_password != $row[0]['password']) {
			$error_current_password = true;
			$master_error = true;
		} else {
			$server->query_without_return("UPDATE users SET password = '$user_new_password' WHERE login = '$user_login'");

			$password_changed_successfully = true;
		}
	} else if(isset($_POST['user_submit'])) {
		if($user_current_password == "")
			$blank_current_password = true;
		if($user_new_password == "")
			$blank_new_password = true;

		$master_error = true;
	}

?>



<!DOCTYPE html>

<html lang = "en-US">

	<head>
		<meta charset = "utf-8">
		<link rel = "icon" href = "../Resources/Images/main_icon.jpg">
		<title>Messenger</title>
	</head>

	<body>

		<?php
			if($master_error)
				echo "<p>Password did not change</p>";
			else if($password_changed_successfully)
				echo "<p>Password changed successfully</p>";
		?>

		<form action = "" method = "post">
			<input type="password" name="password_fake" id="password_fake" value="" style="display:none;" />

			<div>
				<label for = "current_password">Current password:</label>
				<input type = "password" id = "current_password" name = "user_current_password"/>
				<?php
					if($error_current_password)
						echo "<p>Incorrect password</p>";
					else if($blank_current_password)
						echo "<p>Current password field is required</p>";
				?>
			</div>

			<div>
				<label for = "new_password">New password:</label>
				<input type = "password" id = "new_password" name = "user_new_password"/>
				<?php
					if($blank_new_password)
						echo "<p>New password field is required</p>";
				?>
			</div>

			<div>
				<button type = "submit" name = "user_submit">Submit</button>
			</div>

			<a href = "./user_page.php">&lt;&lt; Go back</a>
		</form>

	</body>

</html>