import java.util.Scanner;

class Word{
	String s;
	
	static public String comp(Word w[], int n) {
		String result = "";
		int len = w[0].s.length();
		int idx = 0;
		int cnt = 0;
		
		while(result.length() != len) {
			for(int j=0; j<len; j++) {
				cnt = 0;
				for(int i=0; i<n-1; i++) {
					if(w[i].s.charAt(j) == w[i+1].s.charAt(j)) cnt++;
				}
				if(cnt == n-1) result+= w[idx].s.charAt(j);
				else result += '?';
			}
		}
		return result;
	}
}

public class B1032 {

	public static void main(String[] args) {
		Word filename[];
		String str;
		int n;
		Scanner sc = new Scanner(System.in);
		n = sc.nextInt();
		if(n == 1) {
			System.out.println(str = sc.next());
		}
		else {
			filename = new Word[n];
			for(int i=0; i<n; i++) {
				filename[i] = new Word();
				filename[i].s = sc.next();
			}
			System.out.println(Word.comp(filename, n));
		}
	}

}
