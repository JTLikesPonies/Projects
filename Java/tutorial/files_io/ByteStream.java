//  Used to perform input and output of 8-bit bytes

import java.io.*;
public class ByteStreamCopy {

    public static void main( String[] args ) throws IOException {
        //  Specifically for byte stream
        FileInputStream in = null;
        FileOutputStream out = null;

        try {
            in = new FileInputStream( "input.txt" );
            out = new FileOutputStream( "output.txt" );

            int c;
            while( (c = in.read() ) != -1 ) {
                out.write( c );
            }
        } finally {
            if( in != null ) {
              in.close();
            }
            if( out != null ) {
              out.close();
            }
        }
    }
}
