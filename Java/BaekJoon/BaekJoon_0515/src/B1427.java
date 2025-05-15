import java.util.Scanner;
import java.util.Arrays;
import java.util.Collections;

public class B1427 {

	public static void main(String[] args) {
		String s;
		Scanner sc = new Scanner(System.in);
		s = sc.next();
		int len = s.length();
		Integer arr[] = new Integer[len];
		
		for(int i=0; i<len; i++) {
			arr[i] = Character.getNumericValue(s.charAt(i));
		}
		
		Arrays.sort(arr, Collections.reverseOrder());
		
		s = "";
		
		for(int i=0; i<arr.length; i++) {
			s += arr[i];
		}
		
		System.out.println(s);
		

	}

}
