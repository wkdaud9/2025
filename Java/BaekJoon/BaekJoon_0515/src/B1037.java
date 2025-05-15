import java.util.Scanner;
import java.util.Arrays;

public class B1037 {

	public static void main(String[] args) {
		int result = 0;
		int n;
		Scanner sc = new Scanner(System.in);
		n = sc.nextInt();
		int arr[] = new int[n];
		
		if(n == 1) {
			result = sc.nextInt();
			System.out.println((int)Math.pow(result, 2));
		}
		
		else {
			for(int i= 0; i<n; i++) {
				arr[i] = sc.nextInt();
			}
			Arrays.sort(arr);
			result = arr[0] * arr[n-1];
			System.out.println(result);
		}
		
	}

}
