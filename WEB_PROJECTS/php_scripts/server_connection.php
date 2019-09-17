<?php

	class Server {
		public $db_connection;

		function __construct($file_path) {
			// "../Resources/server_configuration.txt"
			$file_array = $this->read_file($file_path);

			$db_host = $this->parse_server_info($file_array[0]);
			$db_user = $this->parse_server_info($file_array[1]);
			$db_password = $this->parse_server_info($file_array[2]);
			$db_name = $this->parse_server_info($file_array[3]);

			$this->$db_connection = new mysqli($db_host, $db_user, $db_password, $db_name);
			if($this->$db_connection->connect_error) 
				die($this->$db_connection->connect_error);
		}

		function __destruct() {
			$this->$db_connection->close();
		}

		public function query($query_str) {
			$result = $this->$db_connection->query($query_str);
			if(!$result)
				die($this->$db_connection->error);

			if($result->num_rows == 0) {
				$result->close();
				return 0;
			} else {
				$array_to_return;
				for($i = 0; $i < $result->num_rows; $i++) {
					$result->data_seek($j);
					$row = $result->fetch_array(MYSQLI_ASSOC);
					$array_to_return[] = $row;
				}
				$result->close();
				return $array_to_return;
			}
		}

		public function query_without_return($query_str) {
			$this->$db_connection->query($query_str);
		}

		// read file
		private function read_file($location) {
			$counter = 0;
			$array_to_return;
			$file = fopen("$location", 'r');

			while($line = fgets($file)) {
				$array_to_return[$counter] = $line;
				$counter++;
			}
			fclose($file);

			return $array_to_return;
		}

		// parse every line in server information file
		private function parse_server_info($line) {
			$data_to_return = "";
			$char = "";
			$flag = false;
			for($counter = 0; $counter < strlen($line) - 1; $counter++) {
				$char = substr($line, $counter, 1);
				if($char == ":") {
					$flag = true;
					continue;
				}
				if($flag)
					$data_to_return .= $char;
			}

			return $data_to_return;
		}


	}

?>