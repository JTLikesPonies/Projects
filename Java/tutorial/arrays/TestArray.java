public class TestArray {
	
	public static void main(String[] args) {
		double[] my_list = { 1.9, 2.9, 3.4, 3.5 };

		//	Print all the array elements
		for( int i = 0; i < my_list.length; i++ ) {
			System.out.println(my_list[i] + " ");
		}

		//	Summing all elements
		double total = 0;
		for( int i = 0; i < my_list.length; i++ ) {
			total += my_list[i];
		}
		System.out.println("Total is: " + total);

		//	Finding largest element
		double max = my_list[0];
		for( int i = 1; i < my_list.length; i++ ) {
			if( max < my_list[i] ) {
				max = my_list[i];
			}
		}
		System.out.println( "Max is: " + max );

		//	Enhanced for loop -- foreach loop
		for( double element: my_list ) {
			System.out.println( element );
		}
	}

	//	Method that returns an array
	public static int[] reverse( int[] list ) {
		int[] result = new int[list.length];

		for( int i = 0, j = result.length - 1;
			       	i < list.length; i++, j-- ) {
			result[j] = list[i];
		}
		return result;
	}
}
