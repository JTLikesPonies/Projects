class Calculation {
    int z;

    public void addition( int x, int y ) {
        z = x + y;
        System.out.println( "The sum of the given numbers: " + z );
    }

    public void subtraction( int x, int y ) {
        z = x - y;
        System.out.println( "The difference of the given numbers: " + z );
    }
}

public class MyCalculation extends Calculation {
    public void multiplication( int x, int y ){
        z = x * y;
        System.out.println( "The product of the given numbers: " + z );
    }

    public static void main( String[] args ) {
        int a = 20, b = 10;
        MyCalculation calc = new MyCalculation();
        calc.addition( a, b );
        calc.subtraction( a, b );
        calc.multiplication( a, b );
    }
}
