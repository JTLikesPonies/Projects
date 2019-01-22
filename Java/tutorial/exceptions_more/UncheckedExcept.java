//  Will not compile, runtime exception

public class UncheckedExcept {

    public static void main( String[] args ) {
        int num[] = {1, 2, 3, 4};
        System.out.println( num[5] );
    }
}
