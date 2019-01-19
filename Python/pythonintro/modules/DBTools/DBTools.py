import mysql.connector

class MySQLConnection:
	def __init__(self, config: dict) -> None:
		self.configuration = config

	def __enter__(self) -> 'cursor':
		self.conn = mysql.connector.connect(**self.configuration)
		self.cursor = self.conn.cursor()
		return self.cursor

	def __exit__(self, exec_type, exec_value, exec_trace) -> None:
		self.conn.commit()
		self.cursor.close()
		self.conn.close()