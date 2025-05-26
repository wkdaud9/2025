import java.io.*;
import java.util.StringTokenizer;

public class Main {

	public static void main(String[] args) throws IOException {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int si = 1;
		
		while(true) {
			int result = 0;
			
			int n = Integer.parseInt(br.readLine());
			if(n == 0) break;
			
			String s[] = new String[n+1];
			for(int i=1; i<=n; i++) {
				s[i] = br.readLine();
			}
			
			
			for(int i=1; i<n*2; i++) {
				String st[] = br.readLine().split(" ");
				int temp = Integer.parseInt(st[0]);
				char tmp = st[1].charAt(0);
				
				if(i <= n) {
					result += temp;
				}
				else if(i>n) {
					result -= temp;
				}
			}
			
			System.out.println(si + " " + s[result]);
			si++;
		}
			
	}

}
