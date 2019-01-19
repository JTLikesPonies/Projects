import java.io.*;
public class Employee {
	
	String name;
	int age;
	String designation;
	double salary;

	//	Constructor for class Employee
	public Employee( String name ) {
		this.name = name;
	}

	//	Assign the age of the Employee to variable age
	public void empAge( int empAge ) {
		age = empAge;
	}

	//	Assign designation to variable desigination
	public void empDesignation( String empDesig ) {
		designation = empDesig;
	}

	//	Assign the salary to the variable salary
	public void empSalary( double empSalary ) {
		salary = empSalary;
	}

	//	Print employee details
	public void printEmployee() {
		System.out.println( "Name: " + name );
		System.out.println( "Age: " + age );
		System.out.println( "Designation: " + designation );
		System.out.println( "Salary: " + salary );
	}
}
