import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class ReadDataEx {

      public static void main( String[] args ) {
          FileReader fr = null;

          try {
              File file = new File( "file.txt" );
              fr = new FileReader( file );
              char[] a = new char[50];
              fr.read( a );   //  reads the content of the array
              for( char c : a ) System.out.print( c );    //  prints chars one by one
          } catch ( IOException e ) {
              e.printStackTrace();
          } finally {
              try {
                  fr.close();
              } catch( IOException ex ) {
                  ex.printStackTrace();
              }
          }
      }
}
