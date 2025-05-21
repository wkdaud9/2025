import java.math.BigDecimal;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int a, b, n;
		int cnt = 0;
		a = sc.nextInt();
		b = sc.nextInt();
		n = sc.nextInt();
		
		int temp = a%b;
		if(temp != 0) {
			while(cnt < n) {
				temp = a % b;
				temp *= 10;
				a = temp;
				cnt++;
			}
		}
		
		System.out.println(a/10);
	}
}
