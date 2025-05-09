import java.util.Scanner;

class Num{
	String s = new String();
	
	public int change() {
		int num = 0;
		for(int i=0; i<s.length(); i++) {
			num += (s.charAt(i)-'0');
		}
		return num;
	}
}
public class B1769 {
	public static void main(String[] args) {
		int temp = 0;
		int cnt = 1;
		int result = 0;
		Num x = new Num();
		Scanner sc = new Scanner(System.in);
		x.s = sc.next();
		if(x.s.length() == 1) {
			cnt = 0;
			result = x.change();
		}
		else {
			result += x.change();
			while(result >= 10) {
				x.s = Integer.toString(result);
				result = x.change();
				cnt++;
			}
		}
		System.out.println(cnt);
		System.out.println(result % 3 == 0 ? "YES" : "NO");
		sc.close();

	}

}
