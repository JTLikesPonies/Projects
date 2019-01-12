import java.util.Scanner;

public class methods_fields
{
    //Class variable
    //static -- indicates callable from other classes & functions in program
    static double my_pi = 3.14159;
    static int rand_num;

    static Scanner user_input = new Scanner(System.in);

    public static void main(String[] args)
    {
        System.out.println(add(1, 2));

        int d = 5;
        try_to_change(d);

        System.out.println("main d = " + d);


        System.out.println(getRandomNum());
        int guess_result = 1;
        int rand_guess = 0;

        while(guess_result != -1)
        {
            System.out.print("Guess a number between 0 and 50: ");

            rand_guess = user_input.nextInt();

            guess_result = checkGuess(rand_guess);
        }

        System.out.println("You guessed the random number " + rand_guess); 

    }


    //Just messing around
    public static int add (int a, int b)
    {
        double small_pi = 3.140; //Local variable --only accessible in add
                                 //value can be passed but not accessed
        double my_pi = 3.0; //Can overwrite  my_pi

        System.out.println("Local " + my_pi);
        int c = a + b;

        return c;
    }


    //Passing by reference
    public static void try_to_change (int d)
    {
        d = d + 1;
        System.out.println("try_to_change d = " + d);
    }


    public static int getRandomNum ()
    {
        rand_num = (int) (Math.random() * 51);

        return rand_num;
    }

    public static int checkGuess (int guess)
    {
        if(guess == rand_num)
        {
            return -1;
        } else {
            return guess;
        }
    }
}
