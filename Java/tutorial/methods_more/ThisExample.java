public class ThisExample {

    //  Instance variable num
    int num = 10;

    ThisExample() {
        System.out.println( "This is an example program for the keyword this" );
    }

    ThisExample( int num ) {
        //  Invokes the default constructor
        this();

        //  Assigns the local variable num to the instance variable num
        this.num = num;
    }

    public void greet() {
        System.out.println( "Hello from this Example" );
    }

    public void print() {
        //  Local variable num
        int num = 20;

        //  Printing the local variable
        System.out.println( "Value of the local variable num is: " + num );
        //  Printing the instance variable
        System.out.println( "Value of instance variable num is: " + this.num );
        //  Invoking the greet method
        this.greet();
    }

    public static void main( String[] args ) {
        //  Instantiating the class
        ThisExample obj1 = new ThisExample();

        //  Invoking the print method
        obj1.print();

        //  Passing a new value to the num variable through parameterized constructor
        ThisExample obj2 = new ThisExample(30);

        //  Invoking print method again
        obj2.print();
    }
}
