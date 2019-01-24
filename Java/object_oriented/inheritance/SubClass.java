/*  Example of super keyword
 *  used to differentiate members of superclass from members of subclass
 *  if they share the same name
 *  Used to invoke superclass constructor from subclass
 */

 class SuperClass {
    int num = 20;

    //  display method of superclass
    public void display() {
        System.out.println( "This is the display method of SuperClass" );
    }
 }

 public class SubClass extends SuperClass {
    int num = 10;

    //  display method of subclass
    public void display() {
        System.out.println( "This is the display method of the SubClass" );
    }

    public void myMethod() {
        //  Instantiating new subclass
        SubClass sub = new SubClass();

        //  Invoking display() method of subclass
        sub.display();

        //  Invoking display of superclass
        super.display();

        //  Print value of subclass num
        System.out.println( "Num from SubClass = " + sub.num );

        //  Print value of superclass num
        System.out.println( "Num from SuperClass = " + super.num );
    }

    public static void main( String[] args ) {
        SubClass obj = new SubClass();
        obj.myMethod();
    }
 }
