import junit.framework.TestCase;
import java.io.File; 
import java.io.FileNotFoundException; 
import java.util.Scanner; 


public class UrlValidatorUnitTest extends TestCase {
	
	
	public static void main(String[] args) throws Exception { 
			UrlValidator validator = new UrlValidator();
			File urlfile = new File("./URLValidatorInCorrect/test/urls.txt");
			File resultfile = new File("./URLValidatorInCorrect/test/urlresults.txt");
			Scanner sc = new Scanner(urlfile);
			Scanner scr = new Scanner(resultfile);
			
			System.out.print("Testing null string ");
			boolean nullresult = validator.isValid(null);
			System.out.println("Result: " + nullresult);
			
			System.out.print("Testing nonsense ");
			boolean nonresult = validator.isValid("sdgsadgdahadgagdadgagadgadgda");
			System.out.println("Result: " + nonresult);
			
			int counter = 1;
			while (sc.hasNextLine()) {
				String url = sc.nextLine();
				boolean expectedResult = Boolean.parseBoolean(scr.nextLine());
				boolean result = validator.isValid(url);
				if (result != expectedResult) {
					System.out.print("Testing url #" + counter + ": " + url);
					System.out.println(" Result: " + result + " Expected Result: " + expectedResult);
				}
				counter += 1;
				
			}
			sc.close();
			scr.close();
	}
	
	
	
	

}