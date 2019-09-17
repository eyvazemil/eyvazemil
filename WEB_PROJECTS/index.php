<?php

	session_start();

	if(isset($_SESSION['first_name']) && strlen($_SESSION['first_name']) > 0)
		session_destroy();

	require_once("./php_scripts/server_connection.php");

	$errors = array(
		"first_name" => false,
		"second_name" => false,
		"login" => false,
		"password" => false
	);

	$blanks = array(
		"first_name" => false,
		"second_name" => false,
		"new_login" => false,
		"new_password" => false,
		"login" => false,
		"password" => false,
		"gender" => false
	);

	$bool_success_sign_up = false;
	$bool_error_sign_up = false;
	$bool_sign_up_already_exists = false;
	$bool_log_in_does_not_exist = false;
	$bool_error_log_in = false;
	$bool_log_in_success = false;

	$success_sign_up = "Sign up submitted successfully<br/>";
	$error_sign_up = "Sign up submitted incorrectly<br/>Please submit all values correctly<br/>";
	$error_log_in = "Log in submitted incorrectly<br/>Please submit all values correctly<br/>";
	$error_log_in_exists = "User with such a login already exists<br/>Please choose another login<br/>";
	$error_log_in_does_not_exist = "User with such a login does not exist<br/>Please type correct login<br/>";

	$first_name = "";
	$second_name = "";
	$new_login = "";
	$new_password = "";
	$login = "";
	$password = "";
	$gender_male = "";
	$gender_female = "";
	$gender = "";

	// session purposes variables
	$session_first_name = "";
	$session_second_name = "";
	$session_login = "";
	$session_gender = "";

	if(isset($_POST['user_first_name']))
		$first_name = $_POST['user_first_name'];
	if(isset($_POST['user_second_name']))
		$second_name = $_POST['user_second_name'];
	if(isset($_POST['user_new_login']))
		$new_login = $_POST['user_new_login'];
	if(isset($_POST['user_new_password']))
		$new_password = $_POST['user_new_password'];
	if(isset($_POST['user_login']))
		$login = $_POST['user_login'];
	if(isset($_POST['user_password']))
		$password = $_POST['user_password'];
	if(isset($_POST['user_gender'])) {
		if($_POST['user_gender'] == "male")
			$gender_male = "true";
		if($_POST['user_gender'] == "female")
			$gender_female = "true";
	}

	if($gender_male == "true")
		$gender = "m";
	else if($gender_female == "true")
		$gender = "f";

	if($first_name !== "" && $second_name !== ""
	&& $new_login !== "" && $new_password !== "" 
	&& $gender !== "") {
		// sign up handling

		$error = false;

		if(!check_entered_values($first_name)) {
			$errors['first_name'] = true;
			$error = true;
		}
		if(!check_entered_values($second_name)) {
			$errors['second_name'] = true;
			$error = true;
		}
		if(!check_login($new_login)) {
			$errors['login'] = true;
			$error = true;
		}

		if(!$error) {
			// if all the data in the form is correct
			// handle mysqli part

			// connect to mysql server and check if
			// user with such login already exists

			$server = new Server("./Resources/server_configuration.txt");
			$row = $server->query("SELECT * FROM users WHERE login = '$new_login'");

			if($row == 0) {
				// there is no user with this login
				// add this user to the database
				$server->query_without_return("INSERT INTO users(first_name, second_name, login, password, gender) 
						  VALUES('$first_name', '$second_name', '$new_login', '$new_password', '$gender')");
				// new account was created successfully
				$bool_success_sign_up = true;

				if(!file_exists("./Mails/$new_login")) {
					$oldumask = umask(0);
					mkdir("./Mails/$new_login", 0777);
					umask($oldumask);
					$oldumask = umask(0);
					mkdir("./Mails/$new_login/Sent", 0777);
					umask($oldumask);
					$oldumask = umask(0);
					mkdir("./Mails/$new_login/Inbox", 0777);
					umask($oldumask);
				}
			} else {
				// such user already exists
				$bool_sign_up_already_exists = true;
			}

		} else
			$bool_error_sign_up = true;


	} else if($login !== "" && $password !== "") {
		// login handling
		// no error checking is needed
		$server = new Server("./Resources/server_configuration.txt");
		$row = $server->query("SELECT * FROM users WHERE login = '$login'");

		if($row == 0)
			$bool_log_in_does_not_exist = true;
		else {
			if($password != $row[0]['password'])
				$errors['password'] = true;
			else {
				// successfully logged in
				$bool_log_in_success = true;

				$session_first_name = $row[0]['first_name'];
				$session_second_name = $row[0]['second_name'];
				$session_login = $row[0]['login'];
				$session_gender = $row[0]['gender'];
			}
		}
	} else if(isset($_POST['submit_sign_up'])) {
		// submit was pressed without complete sign up form

		$bool_error_sign_up = true;

		if($first_name == "")
			$blanks['first_name'] = true;
		else if(!check_entered_values($first_name))
			$errors['user_first_name'] = true;

		if($second_name == "")
			$blanks['second_name'] = true;
		else if(!check_entered_values($second_name))
			$errors['user_second_name'] = true;

		if($new_login == "")
			$blanks['new_login'] = true;

		if($new_password == "")
			$blanks['new_password'] = true;

		if($gender_male == "" && $gender_female == "")
			$blanks['gender'] = true;
	} else if(isset($_POST['submit_log_in'])) {
		// submit was pressed without complete log in form

		$bool_error_log_in = true;

		if($login == "")
			$blanks['login'] = true;

		if($password == "")
			$blanks['password'] = true;
	}

?>

<?php

	function check_entered_values($str) {
		$correct = true;

		for($i = 0; $i < strlen($str); $i++) {
			$int = ord(substr($str, $i, 1));
			if($i == 0) {
				if($int < 65 || $int > 90) {
					$correct = false;
					break;
				}
				continue;
			}
			if($int < 65 || ($int > 90 && $int < 97) || $int > 122) {
				$correct = false;
				break;
			}
		}

		return $correct;
	}

	function check_login($str) {
		$correct = true;

		for($i = 0; $i < strlen($str); $i++) {
			$char = substr($str, $i, 1);
			if($char == "&") {
				$correct = false;
				break;
			}
		}

		return $correct;
	}

?>



<!DOCTYPE html>

<html lang = "en-US">

	<head>
		<meta charset = "utf-8">
		<meta name = "author" description = "Qwerty Qwerty">
		<meta name = "description" description = "My first messenger">
		<meta name = "viewport" content = "width=device-width">
		<link rel = "stylesheet" type = "text/css" href = "./styles/index_style.css">
		<link rel = "icon" href = "./Resources/Images/main_icon.jpg">

		<title>Messenger</title>
	</head>

	<body>

		<header>
			<h1>My messenger</h1>
		</header>

		<main>

			<?php

				if($bool_success_sign_up)
					echo "<p class = \"error top_error\">$success_sign_up</p>";
				if($bool_error_sign_up)
					echo "<p class = \"error top_error\">$error_sign_up</p>";
				if($bool_error_log_in)
					echo "<p class = \"error top_error\">$error_log_in</p>";
				if($bool_sign_up_already_exists)
					echo "<p class = \"error top_error\">$error_log_in_exists</p>";
				if($bool_log_in_does_not_exist)
					echo "<p class = \"error top_error\">$error_log_in_does_not_exist</p>";

			?>

			<section id = "sign_up">
				<h2>Sign up</h2>

				<div id = "form">
					<form action = "" method = "post">
						<input type="text" name="prevent_autofill" id="prevent_autofill" value="" style="display:none;" />
						<input type="password" name="password_fake" id="password_fake" value="" style="display:none;" />
						<div class = "text_inputs">
							<label for = "first_name">First name:</label>
							<input type = "text" id = "first_name" name = "user_first_name" maxlength = "30" 
							value = "<?php echo $first_name; ?>"/>
							<?php
								if($errors['first_name'])
									echo "<p class = \"error\">Incorrect first name</p>";
								else if($blanks['first_name'])
									echo "<p class = \"error\">First name field is required</p>";
							?>
						</div>
						<div class = "text_inputs">
							<label for = "second_name">Second name:</label>
							<input type = "text" id = "second_name" name = "user_second_name" maxlength = "30"
							value = "<?php echo $second_name; ?>"/>
							<?php
								if($errors['second_name'])
									echo "<p class = \"error\">Incorrect second name</p>";
								else if($blanks['second_name'])
									echo "<p class = \"error\">Second name field is required</p>";
							?>
						</div>

						<div class = "text_inputs">
							<label for = "new_login">LOGIN:</label>
							<input type = "text" id = "new_login" name = "user_new_login" maxlength = "30"
							value = "<?php echo $new_login; ?>"/>
							<?php
								if($errors['login'])
									echo "<p class = \"error\">'&' sign is not allowed in login</p>";
								else if($blanks['new_login'])
									echo "<p class = \"error\">Login field is required</p>";
							?>
						</div>
						<div class = "text_inputs">
							<label for = "new_password">PASSWORD:</label>
							<input type = "password" id = "new_password" name = "user_new_password" maxlength = "30"
							value = "<?php echo $new_password; ?>"/>
							<?php
								if($blanks['new_password'])
									echo "<p class = \"error\">Password field is required</p>";
							?>
						</div>

						<div class = "radio_inputs">
							<section>
								<label class = "label_gender" for = "gender_male">Male</label>
								<input type = "radio" id = "gender_male" name = "user_gender" value = "male"
									<?php if($gender_male === "true") echo "checked"; ?>
								/>
							</section>
							<span>
								<label class = "label_gender" for = "gender_female">Female</label>
								<input type = "radio" id = "gender_female" name = "user_gender" value = "female"
									<?php if($gender_female === "true") echo "checked"; ?>
								/>
							</span>
							<?php
								if($blanks['gender'])
									echo "<p class = \"error\">Gender field is required</p>";
							?>
						</div>

						<button type = "submit" name = "submit_sign_up">Sign up</button>
					</form>
				</div>
			</section>

			<aside id = "log_in">
				<h2>Log in</h2>
				<form action = "" method = "post">
					<input type="text" name="prevent_autofill_2" id="prevent_autofill_2" value="" style="display:none;" />
					<input type="password" name="password_fake_2" id="password_fake_2" value="" style="display:none;" />
					<div class = "text_inputs">
						<label for = "login">LOGIN:</label>
						<input type = "text" id = "login" name = "user_login" maxlength = "30"
						value = "<?php echo $login; ?>"/>
						<?php
							if($blanks['login'])
								echo "<p class = \"error\">Login field is required</p>";
						?>
					</div>

					<div class = "text_inputs">
						<label for = "password">PASSWORD:</label>
						<input type = "password" id = "password" name = "user_password" maxlength = "30"
						value = "<?php echo $password; ?>"/>
						<?php
							if($errors['password'])
								echo "<p class = \"error\">Incorrect password</p>";
							else if($blanks['password'])
								echo "<p class = \"error\">Password field is required</p>";
						?>
					</div>

					<button type = "submit" name = "submit_log_in">Log in</button>
				</form>
			</aside>

		</main>

		<footer>
		</footer>

	</body>

</html>



<?php

	if(isset($_SESSION['first_name']) && strlen($_SESSION['first_name']) > 0)
		session_destroy();

	if($bool_log_in_success) {
		session_start();

		$_SESSION['first_name'] = $session_first_name;
		$_SESSION['second_name'] = $session_second_name;
		$_SESSION['login'] = $session_login;
		$_SESSION['gender'] = $session_gender;

		header('Location: ./php_scripts/user_page.php');
	}

?>