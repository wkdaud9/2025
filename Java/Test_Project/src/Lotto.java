import java.util.Random;
import java.util.Arrays;

class Lotto {
	private Random ran = new Random();
	private int n;
	private int num[] = new int[6];
	
	 public void insertRandomNumber(int start, int end) {
		 int r;
		 for(int i=start; i<end; i++) {
			 r = (ran.nextInt(45)) + 1;
			 while(duplication(r, i)) {
				 r = (ran.nextInt(45)) + 1;
			 }
			 num[i]= r; 
		 }
	 }
	 
	 public boolean duplication(int n, int idx) {
		for(int j=0; j<idx; j++) {
			if(num[j] == n) return true;
		}
		return false;
	 }
	 
	 public int getLottoNum(int i) {return num[i];}
	 public int getNumber() {return n;}
	 public void setLottoNum(int num, int idx){this.num[idx++] = num;}
	 public void setNumber(int n) {this.n = n;}
	 public void arraySort() {Arrays.sort(num);}
	 
}
