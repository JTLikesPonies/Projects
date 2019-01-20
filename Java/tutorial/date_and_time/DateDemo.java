import java.util.*;
import java.text.*;

public class DateDemo {
	public static void main( String[] args ) {
		//	Instantiate a Date object
		Date date = new Date();

		//	Display time and date using toString()
		System.out.println( date.toString() );
	
		//	Date formatting
		SimpleDateFormat ft = 
		new SimpleDateFormat( "E yyyy.MM.dd ' at ' hh:mm:ss a zzz" );

		System.out.println( "Current date: " + ft.format(date));
	
		//	Date formatting with printf
		String str = String.format( "Current Date/Time: %tc\n", date );

		System.out.printf(str);

		//	Display date and time
		System.out.printf( "%1$s %2$tB %2$td, %2$tY\n", 
				"Due date: ", date );

		//	Additional format
		System.out.printf( "%s %tB %<te, %<tY\n", "Due date: ", date);

		//	Parsing Strings into Dates
		SimpleDateFormat fmt = new SimpleDateFormat( "yyyy-MM-dd");
		String input = (args.length == 0) ? "1818-11-11" : args[0];

		System.out.print( input + " Parses as " );
		Date t;
		try {
			t = fmt.parse( input );
			System.out.println( t );
		} catch ( ParseException e ) {
			System.out.println( "Unparseable using " + fmt );
		}
	}
}
