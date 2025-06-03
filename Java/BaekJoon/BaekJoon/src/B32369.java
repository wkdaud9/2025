import java.util.Scanner;

public class B32369 {

	public static void main(String[] args) {
		int arr[] = new int[2];
		int goodP=0, badP=1;
		int n, a, b;
		int temp;
		Scanner sc = new Scanner(System.in);
		
		for(int i=0; i<2; i++) {
			arr[i] = 1;
		}
		
		n=sc.nextInt();
		a=sc.nextInt();
		b=sc.nextInt();
		
		for(int i=0; i<n; i++) {
			arr[goodP] += a;
			arr[badP] += b;
			if(arr[goodP] < arr[badP]) {
				temp = goodP;
				goodP = badP;
				badP = temp;	
			}
			if(arr[goodP] == arr[badP]) arr[badP] -=1;
			
		}
		
		System.out.println(arr[goodP] + " " + arr[badP]);
		
	}

}
