import java.io.*;

public class EmployeeTest {
	public static void main( String args[] ) {
		//	Create two objects using constructor
		Employee emp_one = new Employee( "James Smith" );
		Employee emp_two = new Employee( "Mary Anne" );

		//	Invoke methods for each object created
		emp_one.empAge( 26 );
		emp_one.empDesignation( "Senior Software Engineer" );
		emp_one.empSalary( 1000 );
		emp_one.printEmployee();

		emp_two.empAge( 21 );
		emp_two.empDesignation( "Software Engineer" );
		emp_two.empSalary( 500 );
		emp_two.printEmployee();
	}
}
