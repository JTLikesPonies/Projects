public class hello_world
{
    //Class Variable
    static String random_string = "Here is a string";

    //Constant -- var name all caps for const
    static final double PINUM = 3.14159;

    public static void main(String[] args)
    {
        System.out.println("Hello world");
        System.out.println(random_string);
        System.out.println(PINUM);

        //Int variables
        //Declaration statements
        int integer_one = 1;
        int integer_two = 0;

        //Expression statement
        integer_two
        +=
        integer_one;  //Valid because ';' marks end of line

        System.out.println(integer_two);

        //Primitive types
        byte big_byte = 127;
        short big_short = 32767;
        int big_int = 2100000000;
        long big_long = 920000000000000000L;
        float big_float = 3.14F;
        double big_double = 3.14121234981723948712938479989898;

        //Prints max size of float and double for system
        System.out.println(Float.MAX_VALUE);
        System.out.println(Double.MAX_VALUE);

        boolean true_or_false = true; //or false -- never '0' or '1'


        //Character codes -- these will be equal
        char random_char = 65;
        char another_char = 'A';

        System.out.println(random_char);
        System.out.println(another_char);

        String another_string = "I'm another random string";
        String one_more = "And yet another";

        String final_string = another_string + ' ' + one_more;
        System.out.println(final_string);

        String byte_string = Byte.toString(big_byte);
        String short_string = Short.toString(big_short);
        //All other priimtive types mentioned above are valid in same format

        //Casting -- Converting from one primitive type to another
        double double_value = 3.1412341234;
        int double_to_int = (int) double_value;

        System.out.println(double_to_int);

        //Cast string to other data types
        String int_string = Integer.toString(big_int);
        int string_to_int = Integer.parseInt(int_string); //parseByte, parseLong,
                                                          //parseDouble, etc...

        System.out.println(string_to_int);
    }
}
