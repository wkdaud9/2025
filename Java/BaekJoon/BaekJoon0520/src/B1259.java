import java.util.Scanner;

public class B1259 {

	public static void main(String[] args) {
		String n;
		Scanner sc = new Scanner(System.in);
		int arr[];
		
		n = sc.next();
		
		while(!(n.equals("0"))) {
			int cnt = 0;
			arr= new int[n.length()];
			for(int i=0; i<n.length(); i++) {
				arr[i] = Character.getNumericValue(n.charAt(i));
			}
			for(int i=0; i<arr.length / 2; i++) {
				if(arr[i] == arr[arr.length-1- i]) {
					cnt++;
				}
			}
			if(cnt == arr.length/2) System.out.println("Yes");
			else System.out.println("No");
			n = sc.next();
		}
	}

}
