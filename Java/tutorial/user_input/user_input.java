import java.util.Scanner; //Accepts user input

public class user_input
{
    //static signifies only classes can call for this statement ot exec
    //scanner tool that accepts user input
    static Scanner user_input = new Scanner(System.in);

    public static void main(String[] args)
    {
        System.out.print("Your favorite number: ");

        //If next thing typed by user is an integer
        if(user_input.hasNextInt()) //.hasNextDouble, .hasNextFloat, etc
        {
            //receives user input and stores into user_number
            int user_number = user_input.nextInt(); //.nextDouble, .nextLine, etc
            System.out.println("You entered " + user_number);

            int double_num = user_number + user_number;
            System.out.println(user_number + " + " + user_number + " = " + double_num);

            int num_min_2 = user_number - 2;
            System.out.println(user_number + " - 2  = " + num_min_2);

            int mult_num = user_number * 2;
            System.out.println(user_number + " * 2 = " + mult_num);

            int div_num = user_number / 2;
            System.out.println(user_number + " / 2 = " + div_num);

            user_number--;
            user_number++;

            //absolute value
            int abs_user = Math.abs(user_number);

            //comparison with max and min function
            int which_is_bigger = Math.max(5, user_number);
            int which_is_smaller = Math.min(1, user_number);

            double sqrt_num = Math.sqrt(5.123412341234);
            int num_ceiling = (int) Math.ceil(5.1234);
            int num_floor = (int) Math.floor(5.123412341);
            int num_round = (int) Math.round(5.62341);

            //random numbers
            //(int) cast ensures returned int
            int random_number = (int) (Math.random() * 10); //random number between
                                                           //0 and 9
            System.out.println("Random Number " + random_number);

        } else {
            System.out.println("Enter an integer");
        }
    }
}
