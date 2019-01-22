//  Method-local inner class

public class OuterClass {
    //  instance method of the outer class
    void myMethod() {
        int num = 23;

        //  method-local inner class
        class MethodInner {
            public void print() {
                System.out.println( "This is the method inner class " + num );
            }
        } //  end of inner class

        //  Accessing inner class
        MethodInner inner = new MethodInner();
        inner.print();
    }

    public static void main( String[] args ) {
        OuterClass outer = new OuterClass();
        outer.myMethod();
    }
}
