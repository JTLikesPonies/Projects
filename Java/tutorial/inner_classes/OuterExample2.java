class OuterClass {
    //  private variable of the outer class
    private int num = 175;

    //  inner class
    public class InnerClass {
        public int getNum() {
            System.out.println( "This is the getnum method of the inner class" );
            return num;
        }
    }
}

public class OuterExample2 {

    public static void main( String[] args ) {
        //  instantiates the outer class
        OuterClass outer = new OuterClass();

        //  instantiates the inner class
        OuterClass.InnerClass inner = outer.new InnerClass();
        System.out.println( inner.getNum() );
    }
}
