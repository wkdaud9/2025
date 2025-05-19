import java.util.Scanner;

class Ab{
	int n;
	int f;
	
	public Ab(int num) {
		n = num;
		n = n%10;
		if(n == 0) n = 10;
		if(n == 1 || n == 10 || n == 5 || n == 6) f = 1;
		else if(n==2 || n ==3 || n == 7 || n==8) f = 4;
		else if(n==4 || n == 9) f = 2;
	}
}

public class B1009 {

	public static void main(String[] args) {
		int a, b, t;
		int temp;
		int p;
		Ab nm;
		
		Scanner sc = new Scanner(System.in);
		t = sc.nextInt();
		for(int i=0; i<t; i++) {
			a = sc.nextInt();
			b = sc.nextInt();
			if(a > 0 && b > 0) {
				nm = new Ab(a);
				temp = b % nm.f;
				
				if(nm.f == 1 && temp == 0) temp = 1;
				else if(nm.f == 4 && temp == 0) temp = 4;
				else if(nm.f == 2 && temp == 0) temp = 2;
				
				p = (int)Math.pow(a, temp) % 10;
				if(p == 0) System.out.println(10);
				else System.out.println(p);
			}
		}
		
	}

}
