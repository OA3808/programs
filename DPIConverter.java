import java.util.Scanner;
class DPIConverter{
  public static void main(String[]arg){
    //Declaration and Initialization
    Scanner UserInput = new Scanner(System.in);
    double odpi;
    double ndpi;
    double sens;
    double nsens;
    //UserInput
    System.out.println("Enter your sensitivity");
    sens=UserInput.nextDouble();
    System.out.println("Enter your old DPI");
    odpi=UserInput.nextDouble();
    System.out.println("Enter your new DPI");
    ndpi=UserInput.nextDouble();
    
    //Execution
    nsens = sens/(ndpi/odpi);
    
    //Output
    System.out.println(sens + " sens at " + odpi + " DPI is " + nsens + " sens at " + ndpi + " DPI.");
    

  }
}
    
    
    
    