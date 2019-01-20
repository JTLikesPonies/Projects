import java.util.*;

public class DiffDemo {
	public static void main( String[] args ) {
		try {
			long start = System.currentTimeMillis();
			System.out.println( new Date() + "\n" );

			Thread.sleep( 3000 );
			System.out.println( new Date() + "\n" );

			long end = System.currentTimeMillis();
			long diff = end - start;
			System.out.println( "Difference is: " + diff );
		} catch ( Exception e ) {
			System.out.println( "Got an exception!" );
		}	
	}
}
