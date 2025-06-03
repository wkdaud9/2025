import java.util.Scanner;

public class B2985 {

	public static void main(String[] args) {
		int num1, num2, result;
		int a, b, c;
		String s = "";
		char f=0, e;
		Scanner sc = new Scanner(System.in);
		
		num1 = sc.nextInt();
		num2 = sc.nextInt();
		result = sc.nextInt();
		
		a = num1;
		b = num2;
		c = result;
		
		if(a + b == c) f = '+';
		else if(a-b == c) f = '-';
		else if(a*b == c) f = '*';
		else if(a/b == c) f ='/';
		e='=';
			
		if(f == 0) {
			if(b + c == a) e = '+';
			else if(b-c == a) e = '-';
			else if(b*c == a) e = '*';
			else if(b/c == a) e ='/';
			f = '=';
		}
		
	
		
		
		s += a;
		s+= f;
		s+= b;
		s+=e;
		s+= result;
		
		System.out.println(s);
	}

}
