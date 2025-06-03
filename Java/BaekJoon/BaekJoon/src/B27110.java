import java.util.*;
public class B27110 {

	public static void main(String[] args) {
		int result = 0;
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int a[] = new int[3];
		
		for(int i=0; i<3; i++) {
			a[i] = sc.nextInt();
			if(a[i] <= n) result += a[i];
			else if(a[i] > n) result += n;
		}
		
		System.out.println(result);
		
		
	}

}
