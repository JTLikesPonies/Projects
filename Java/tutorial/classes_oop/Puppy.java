public class Puppy {
    //  Examples of constructors and accessing instances variables and Methods
    int puppy_age;    

    public Puppy() {
    }

    public Puppy( String name ) {
        //  Constructor that has one parameter, name
        System.out.println( "Puppy's name is: " + name );
    }

    public void setAge( int age ) {
        puppy_age = age;
    }

    public int getAge( ) {
        System.out.println("Puppy's age is: " + puppy_age);
        return puppy_age;
    }

    public static void main( String[] args ) {
        //  Create the Puppy object
        Puppy my_puppy = new Puppy( "Patches" );

        //  Call class method to set age
        my_puppy.setAge( 2 );

        //  Call another class method to get puppy's age
        my_puppy.getAge( );

        //  Accessing instance variables
        System.out.println( "Variable Value: " + my_puppy.puppy_age );
    }
}
