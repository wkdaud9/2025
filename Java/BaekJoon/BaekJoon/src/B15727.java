import java.util.*;
public class B15727 {

	public static void main(String[] args) {
		int result = 0;
		Scanner sc = new Scanner(System.in);
		int l = sc.nextInt();
		
		if(l<=5) {
			result = 1;
		}
		else if(l%5 == 0) {
			result = l/5;
		}
		else {
			result = (l/5)+1;
		}
		
		System.out.println(result);
	}

}
