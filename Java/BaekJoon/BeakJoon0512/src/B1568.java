import java.util.Scanner;

public class B1568 {

	public static void main(String[] args) {
		long n;
		long k = 1L;
		int cnt = 0;
		long result = 0L;
		Scanner sc = new Scanner(System.in);
		n = sc.nextLong();
		while(result != n) {
			result += k++;
			if(result + k > n) k = 1;
			cnt++;
		}
		System.out.println(cnt);
		
	}

}
