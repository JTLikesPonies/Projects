class OuterClass {
    int num;

    //  inner class
    private class InnerClass {
        public void print() {
            System.out.println( "This is an inner class" );
        }
    }

    //  Accessing the inner class from the method within
    void displayInner() {
        InnerClass inner = new InnerClass();
        inner.print();
    }
}

public class OuterExample {
    public static void main( String[] args ) {
        //  Instantiating the outer class
        OuterClass outer = new OuterClass();

        //  Accessing the displayInner() method
        outer.displayInner();
    }
}
