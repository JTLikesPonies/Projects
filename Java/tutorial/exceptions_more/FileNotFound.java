//  Will not compile

import java.io.File;
import java.io.FileReader;

public class FileNotFound {

    public static void main( String[] args ) {
        File file = new File( "E://file.txt" );
        FileReader fr = new FileReader( file ) ;
    }
}
