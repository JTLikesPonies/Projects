import java.io.FileReader;
import java.io.IOException;

public class TryWith {

    public static void main( String[] args ) {
        try( FileReader fr = new FileReader( "E://file.txt" )) {
            char [] a = new char[50];
            fr.read( a );   //  reads contents into array
            for( char c : a )
              System.out.print( c );
        } catch( IOException e ) {
            e.printStackTrace();
        }
    }
}
