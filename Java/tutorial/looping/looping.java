import java.util.Scanner;

public class looping
{
    static Scanner user_input = new Scanner(System.in);

    public static void main(String[] args)
    {
        //While loop -- iterator declared outside of looping
        int i = 1;

        while (i <= 20)
        {
            if (i == 3)
            {
                i += 2;
                continue; //jumps out of this iteration of while loop and
                          //continues on with next iteration
            }

            System.out.println(i);
            i++;

            if ((i%2) == 0)
            {
                i++;
            }

            if (i > 10)
            {
                break; //breaks entire while loop and continues
                       //will only print to 9 now
            }
        }

        //Calculating value of pi -- 4 - 4/3 + 4/5 - 4/7 + ...
        double my_pi = 4.0;
        double j = 3.0;

        while( j < 8001)
        {
            my_pi = my_pi - (4/j) + (4/(j+2));
            j += 4;
            System.out.println(my_pi);
        }

        System.out.println("Value of PI: " + Math.PI);



        //While loop until user says to stop
        String y_or_n = "Y";
        int h = 1;

        while (y_or_n.equalsIgnoreCase("y"))
        {
            System.out.println(h);
            System.out.print("Continue y or n? ");
            y_or_n = user_input.nextLine();
            h++;
        }


        //Do...while loop -- used when code needs to be run at least once
        int k = 1000;
        do {
            System.out.println(k);
            k++;
        } while (k < 10);


        //For loop
        for (int l = 10; l >= 1; l--)
        {
            System.out.println(l);
        }

        int m, n;
        for (m = 1, n = 2; m <= 9; m+=2, n+=2)
        {
            System.out.println("m: " + m + " n: " + n);
        }
    }
}
