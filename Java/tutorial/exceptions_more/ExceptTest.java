/*  Notes
 *  A catch clause cannot exist without a try statement
 *  It is not compulsory to have finally clauses whenever a try/catch block is present
 *  The try block cannot be present without either catch clause or finally clause
 *  Any code cannot be present in between the try, catch, finally blocks
 */
public class ExceptTest {

    public static void main( String[] args ) {
        int a[] = new int[2];

        try {
            System.out.println( "Access element 3 of array: " + a[3] );
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println( "Exception thrown: " + e );
        } finally {
            a[0] = 6;
            System.out.println( "First element is: " + a[0] );
            System.out.println( "The finally statement always executes" );
        }
    }
}
