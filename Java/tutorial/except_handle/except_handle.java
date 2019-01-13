import java.util.*;
import java.io.*;

public class except_handle
{
    static Scanner user_input = new Scanner(System.in);

    public static void main(String[] args)
    {
        divide_by_zero(2);

        System.out.print("How old are you? ");
        int age = check_valid_age();

        if (age != 0)
        {
            System.out.println("You are " + age + " years old");
        }

        get_file("./somestuff.txt");
    }

    public static void divide_by_zero (int a)
    {
        try{
            System.out.println(a/0);
        }

        catch(ArithmeticException e)
        {
            System.out.println("You can't do that");

            System.out.println(e.getMessage());

            System.out.println(e.toString());

            //e.printStackTrace();
        }
    }

    public static int check_valid_age()
    {
          try
          {
              return user_input.nextInt();
          }

          //If user doesn't enter an integer
          catch (InputMismatchException e)
          {
              user_input.next(); //Disregards previous input and skips to next
              System.out.println("Enter an integer");
              return 0;
          }
    }



    public static void get_file(String file_name) //throws IOException, FileNotFoundException, etc...
    {
        try
        {
            FileInputStream file = new FileInputStream(file_name);
        }

        catch(FileNotFoundException e)
        {
            System.out.println("Sorry can't find that file");
        }

        /*catch(IOException e)
        {
            System.out.println("Unknown IO Error");         //CAUSES ERRORS HERE??
        }
        //Ignores exception
        catch(ClassNotFoundException e) {}*/

        catch(Exception e)
        {
            System.out.println("Some error occured");
        }
        //Basic clean-up duty -- ALWAYS EXECUTES
        finally
        {
            System.out.println("");
        }
    }
}
