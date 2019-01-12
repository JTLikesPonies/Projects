public class cond_stat
{
    public static void main(String[] args)
    {
        int rand_num = (int) (Math.random() * 50); //Create random number 0-49
        System.out.println("The random number is " + rand_num);

        if (rand_num < 25)
        {
            System.out.println("The random number is less than 25");
        }
        else if (rand_num > 40)
        {
            System.out.println("The random number is greather than 40");
        }
        else System.out.println("The random number is between 25 and 40");

        //Logical operators -- same as C, C++, etc.
        //  !, &, &&, |, ||, ^
        //Relational operators -- same
        //  <, >, <=, >=, ==, !=
        if (!(false))
        {
            System.out.println("\nI turned false into true");
        }

        if((true) && (true))
        {
            System.out.println("Both are true");
        }

        //Conditional operator -- assigns one value based on condition
        int val_one = 1;
        int val_two = 2;
        //If val one is greater than val two assign val one to biggest val else,
        //viceversa
        int biggest_value = (val_one > val_two) ? val_one : val_two;

        System.out.println("Biggest value: " + biggest_value);

        //Switch statement
        char grade = 'B';

        switch (grade)
        {
            case 'A':
              System.out.println("Great job");
              break;  //stops checking from here -- jump to end of Switch
            case 'B':
              System.out.println("Good job");
              break; 
            case 'C':
              System.out.println("OK job");
              break;
            case 'D':
              System.out.println("Bad job");
              break;
            case 'F':
              System.out.println("You failed");
              break;
            default:
              System.out.println("Invalid entry");
        }
    }
}
