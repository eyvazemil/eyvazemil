<?php

	session_start();

	$user_first_name = $_SESSION['first_name'];
	$user_second_name = $_SESSION['second_name'];
	$user_login = $_SESSION['login'];
	$user_gender = $_SESSION['gender'];

	require_once("./server_connection.php");

	// mails load
	$mails_object = new Mails();


	$send_success = false;

	$incorrect_send_to = false;
	$error = false;
	$search_user_does_not_exist = false;

	// user to search if search bar was set
	$user_to_search = "&";
	$str_search = "";

	// searched user to show in a search bar
	$user_to_search_parsed = "";

	// send message variables
	$user_send_to_user = "";
	$user_subject = "";
	$user_message = "";

	// send email
	if(isset($_POST['user_send_to_user']) && strlen($_POST['user_send_to_user']) > 0)
		$user_send_to_user = $_POST['user_send_to_user'];

	if(isset($_POST['user_subject']) && strlen($_POST['user_subject']) > 0)
		$user_subject = $_POST['user_subject'];

	if(isset($_POST['user_message']) && strlen($_POST['user_message']) > 0)
		$user_message = $_POST['user_message'];

	if($user_send_to_user !== "" && isset($_POST['button_send'])) {
		$server = new Server("../Resources/server_configuration.txt");
		$row = $server->query("SELECT * FROM users WHERE login = '$user_send_to_user'");

		if($row == 0)
			$incorrect_send_to = true;
		else {
			// save message in sender's directory
			$gender = "";
			if($row[0]['gender'] == "m")
				$gender = "Mr.";
			else
				$gender = "Mrs.";

			$to_user = $user_send_to_user . "&" . $gender . " " . $row[0]['first_name'] . " " . $row[0]['second_name'];

			if(!file_exists("../Mails/$user_login/Sent/$to_user")) {
				$oldumask = umask(0);
				mkdir("../Mails/$user_login/Sent/$to_user", 0777);
				umask($oldumask);
			}

			$current_date = current_date();
			$str_file_to_create = "../Mails/$user_login/Sent/$to_user/$current_date.txt";
			if(file_exists($str_file_to_create))
				$error = true;
			else {
				$created_file = fopen($str_file_to_create, 'x+');
				if(!$created_file)
					die("File could not be created!_1");

				chmod($str_file_to_create, 0666); 

				$message_to_append = "\n" . $user_message;
				fwrite($created_file, $user_subject);
				fwrite($created_file, $message_to_append);
				fclose($created_file);

				// save message in receiver's directory
				$gender = "";
				if($user_gender == "m")
					$gender = "Mr.";
				else
					$gender = "Mrs.";

				$to_user = $user_login . "&" . $gender . " " . $user_first_name . " " . $user_second_name;

				if(!file_exists("../Mails/$user_send_to_user/Inbox/$to_user")) {
					$oldumask = umask(0);
					mkdir("../Mails/$user_send_to_user/Inbox/$to_user", 0777);
					umask($oldumask);
				}

				$current_date = current_date();
				$str_file_to_create = "../Mails/$user_send_to_user/Inbox/$to_user/$current_date.txt";
				$created_file = fopen($str_file_to_create, 'x+');
				if(!$created_file)
					die("File could not be created!_2");

				chmod($str_file_to_create, 0666);

				$message_to_append = "\n" . $user_message;
				fwrite($created_file, $user_subject);
				fwrite($created_file, $message_to_append);
				fclose($created_file);

				$send_success = true;
			}
		}
	}

	// search particular user
	if(isset($_GET['user_search']) && isset($_GET['button_search'])) {
		$str_search = $_GET['user_search'];

		if($str_search !== "") {
			$server = new Server("../Resources/server_configuration.txt");
			$row = $server->query("SELECT * FROM users WHERE login = '$str_search'");

			if($row == 0)
				$search_user_does_not_exist = true;
			else {
				$gender = "";
				if($row[0]['gender'] == "m")
					$gender = "Mr. ";
				else
					$gender = "Mrs. ";
				$user_to_search = $row[0]['login'] . "&" . $gender . $row[0]['first_name'] . " " . $row[0]['second_name'];
				$user_to_search_parsed = $row[0]['login'];
			}
		}
	}

	// show inbox or sent
	if(!isset($_SESSION['inbox_sent']))
		$_SESSION['inbox_sent'] = "Inbox";
	if(isset($_GET['user_sent']))
		$_SESSION['inbox_sent'] = "Sent";
	if(isset($_GET['user_inbox']))
		$_SESSION['inbox_sent'] = "Inbox";

	$mails_object->load_mails($_SESSION['inbox_sent'], $user_to_search);

?>


<?php
	
	function current_date() {
		$current_date = date("Y") . date("m") . date("d") . "_" . date("H") . date("i") . date("s");
		return $current_date;
	}

	// read the file and return the appropriate array
	function read_file($user, $location) {
		$counter = 0;
		$subject = "";
		$message = "";
		$file = fopen("$location", 'r');

		while($line = fgets($file)) {
			if($counter == 0)
				$subject = $line;
			else {
				if($counter == 1)
					$message .= $line;
				else
					$message .= "<br/>" . $line;
			}
			$counter++;
		}
		fclose($file);

		return array($user, $subject, $message);
	}

	// extract file name from the given path
	function extract_file_name($str) {
		$file_name = "";
		$i = 0;
		for($j = strlen($str) - 1; $j >= 0; $j--) {
			$char = substr($str, $j, 1);
			if($char == '/') {
				$i = $j;
				break;
			}
		}
		for(++$i; $i < strlen($str); $i++) {
			$char = substr($str, $i, 1);
			if($char == ".")
				break;
			$file_name .= $char;
		}
		return $file_name;
	}

	// the same as extract_file_name
	// with the difference that this function
	// reads file name till the end of the string
	// does not drop file extension
	function extract_name($str) {
		$file_name = "";
		$i = 0;
		for($j = strlen($str) - 1; $j >= 0; $j--) {
			$char = substr($str, $j, 1);
			if($char == '/') {
				$i = $j;
				break;
			}
		}
		for(++$i; $i < strlen($str); $i++) {
			$char = substr($str, $i, 1);
			$file_name .= $char;
		}
		return $file_name;
	}

	// return date as proper date string from file name
	function extract_date_from_str($date) {
		$year = substr($date, 0, 4);
		$month = substr($date, 4, 2);
		$day = substr($date, 6, 2);

		$hour = substr($date, 9, 2);
		$minutes = substr($date, 11, 2);
		$seconds = substr($date, 13, 2);

		return $year . "/" . $month . "/" . $day . "_" . $hour . ":" . $minutes . ":" . $seconds;
	}

?>


<?php

	class Mails {

		public $mails;

		function __construct() {}

		public function load_mails($inbox_sent, $user) {
			global $user_login;
			if($user == "&") {
				// load all mails
				$all_senders = glob("../Mails/$user_login/$inbox_sent/*");

				foreach($all_senders as $file_name) {
					$all_files = glob("$file_name/*");
					for($i = count($all_files) - 1; $i >= 0; $i--) {
						$text = $all_files[$i];
						$date = extract_date_from_str(extract_file_name($text));
						$read_file = read_file(extract_name($file_name), "$text");
						$this->$mails["$date"] = $read_file;
					}
				}
			} else {
				// load mails from particular user
				$all_files = glob("../Mails/$user_login/$inbox_sent/$user/*");
				for($i = count($all_files) - 1; $i >= 0; $i--) {
					$text = $all_files[$i];
					$date = extract_date_from_str(extract_file_name($text));
					$read_file = read_file($user, "$text");
					$this->$mails["$date"] = $read_file;
				}
			}
			// sort
			krsort($this->$mails, SORT_STRING);
		}

		// show mails in basic html
		public function show_mails() {
			foreach($this->$mails as $key => $value) {
				echo <<<_END
				<div>
					<p>Date: $key</p>
					<p>Name: $value[0]</p>
					<p>Subject: $value[1]</p>
					<p>Message: $value[2]</p>
				</div>
_END;
			}
		}

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

		<header>
			<h1>My messenger</h1>
			<?php
				if($user_gender == "m")
					echo "Mr. " . $user_first_name . " " . $user_second_name . "<br/>";
				else
					echo "Mrs. " . $user_first_name . " " . $user_second_name . "<br/>";
			?>

			<nav>
				<ul>
					<li>
						<a href = "./change_password.php">Change password</a>
					</li>
					<li>
						<a href = "../index.php">Sign out</a>
					</li>
					<li>
						<a href = "./delete_account.php">Delete account</a>
					</li>
				</ul>
			</nav>
		</header>

		<main>

			<div>
				<form action = "" method = "get">
					<label for = "search">Search:</label>
					<input type = "text" id = "search" name = "user_search" maxlength = "30"
						<?php 
							if($user_to_search !== "&")
								echo "value = " . $user_to_search_parsed;
						?>
					/>
					<?php
						if($search_user_does_not_exist)
							echo "<p>Such user does not exist</p>";
					?>

					<button type = "submit" name = "button_search">Search</button>
				</form>
			</div>

			<aside>

				<div>
					<ul>
						<li>
							<form action = "" method = "get">
								<input type = "submit" id = "inbox" name = "user_inbox" value = "Inbox">
							</form>
						</li>
						<li>
							<form action = "" method = "get">
								<input type = "submit" id = "sent" name = "user_sent" value = "Sent">
							</form>
						</li>
					</ul>
				</div>

				<div>
					<?php
						if($send_success)
							echo "<p>The message was sent successfully</p>";
						else if($incorrect_send_to)
							echo "<p>The message was not sent</p>";
					?>

					<form action = "" method = "post">
						<div>
							<label for = "send_to_user">To:</label>
							<input type = "text" id = "send_to_user" name = "user_send_to_user" maxlength = "30"/>
							<?php
								if($incorrect_send_to)
									echo "<p>Such user does not exist</p>";
							?>
						</div>
						<div>
							<label for = "subject">Subject:</label>
							<input type = "text" id = "subject" name = "user_subject" maxlength = "50"/>
						</div>
						<div>
							<label for = "message">Message:</label>
							<textarea id = "message" name = "user_message">Text...</textarea>
						</div>
						<div>
							<button type = "submit" name = "button_send">Send</button>
						</div>
					</form>
				</div>
			</aside>

			<div>
				<?php 
					$mails_object->show_mails();
				?>
			</div>
		</main>

	</body>

</html>