/*  An inner class declared without a class name
 *  Must be declared and instantiated at same time
 *  Used whenever need to override method of a class
 */

 abstract class AnonymousInnerClass {
    public abstract void myMethod();
 }

 public class AnonymousInner {

    public static void main( String[] args ) {
        AnonymousInnerClass inner = new AnonymousInnerClass() {
            public void myMethod() {
                System.out.println( "This is an example of anonymous inner class" );
            }
        };

        inner.myMethod();
    }
 }
