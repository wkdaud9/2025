import java.util.Scanner;
import java.util.Arrays;

public class B2822 {

	public static void main(String[] args) {
		int result = 0;	// 값 저장
		int arr[] = new int[8];
		int cnt[] = new int[5]; // 인덱스 번호 저
		int idx = 0;
		Scanner sc = new Scanner(System.in);
		
		for(int i=0; i<8; i++) {
			arr[i] = sc.nextInt();
		}
		
		int max = 0;
		
		while(idx != 5) {
			max = 0;
			for(int i=1; i<8; i++) {
				if(arr[max] < arr[i]) {
					max = i;
				}
			}
			cnt[idx++] = max;
			result += arr[max];
			arr[max] = 0;
		}
		Arrays.sort(cnt);
		System.out.println(result);
		for(int i=0; i<5; i++) {
			System.out.print(cnt[i]+1 + " ");
		}
	}

}
