import java.util.Scanner;
public class B1798 {

	public static void main(String[] args) {
		long n;
		long result = 0L;
		long i=0L;
		Scanner sc = new Scanner(System.in);
		n = sc.nextLong();
		
		while(true) {
			i++;
			result += i;
			if(result >= n) break;
		}
		if(result == n) System.out.println(i);
		else System.out.println(i-1);
		
	}

}
