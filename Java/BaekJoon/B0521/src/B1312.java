import java.util.Scanner;

public class B1312 {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int a, b, n;
		int result = 0;
		a = sc.nextInt();
		b = sc.nextInt();
		n = sc.nextInt();
		
		a = a % b;
		
		for(int i=0; i<n; i++) {
			a *= 10;
			result = a/b;
			a %= b;
		}

		System.out.println(result);
		
	}
}
