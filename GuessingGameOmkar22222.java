import java.lang.Math;
import java.util.Scanner;
class GuessingGameOmkar22222{
  public static void main(String[]arg){
    //Delaration and Initialization
    Scanner UserInput = new Scanner(System.in);
    int num=0;//input variable
    int random = (int)(Math.random()*100+1);//random number generator 
    int tries = 6;
    int min=1;
    int max=100;
    
    System.out.println(random);
      
    System.out.println("Please enter an integer between 1 and 100");
    
    do{  
        System.out.printf("Try %s ",tries);         
      if (!(UserInput.hasNextInt())){
        tries--;
        System.out.println(num);       
        System.out.println("Oh no! You just wasted a try!");
        System.out.printf("Please enter an integer between %d and %d\n", min, max);
        UserInput.next();
      }
      else{ 
      {
        num = UserInput.nextInt();
      }
      if (num == random){
        tries--;
        System.out.println("You won!");
      }
      
      else if (tries==1&&random!=num){
        System.out.println("You ran out of tries!");
        return;
      }
      else if (num>random&&num<max&&tries>0){
        tries--;
        System.out.println("Guess is too high");
        max = num - 1;
        System.out.printf("Please enter an integer between %d and %d\n", min, max);
      }
      else if (num<random&&num>min&&tries>0){
        tries--;
        System.out.println("Guees is too low");
        min = num + 1;
        System.out.printf("Please enter an integer between %d and %d\n", min, max);
      }
      else if (num>max||num<min&&tries>0){
        tries--;
        System.out.println("Oh no! You wasted a try!");
        System.out.printf("Please enter an integer between %d and %d\n", min, max);
      }

      }
      }while (num!=random&&tries!=0);
      

    
    
  }
}
