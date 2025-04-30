import java.util.Scanner;

class InputManager {
	
	private Scanner sc = new Scanner(System.in);
	
	public int getNumber() {return sc.nextInt();}
	
	public int getYear() {
		int year;
		System.out.println("년도 입력: ");
		year = sc.nextInt();
		while(year <= 0) {
			System.out.println("년도 입력 오류 다시 입력:" );
			year = sc.nextInt();
		}
		return year;
	}
	
	public int getMonth() {
		int mtf;
		int month;
		
		System.out.println("월을 입력: ");
		month = sc.nextInt();
		
		if(month >= 1 && month <=12) mtf = 0;
		else mtf = 1;
		while(mtf == 1) {
			System.out.println("월 입력 오류, 다시 입력: ");
			month = sc.nextInt();
			if(month >= 1 && month <=12) mtf = 0;
		}
		return month;
	}
	
	public int getDay(int mday) {
		int day;
		System.out.println("일을 입력: ");
		day = sc.nextInt();
		
		while(true) {
			if(day <= mday && day > 0) {
				break;
			}
			else {
				System.out.println("일 입력 오류, 다시 입력: ");
				day = sc.nextInt();
			}
		}
		
		return day;
	}
	
	public boolean checkNum(int n) {
		if((n % 2 != 0) && (n>0 && n <=19)) return true;
		else return false;
	}
	
	public int inputOneNumber() {
		return sc.nextInt();
	}
	
	public int LottoWhatinput() {
		int n = sc.nextInt();
		
		while(true) {
			if(n>=0 && n<=6) {
				break;
			}
			else {
				System.out.println("입력 범위를 벗어났습니다. 다시 개수를 입력하세요(0~6) : ");
				n = sc.nextInt();
			}
		}
		return n;
	}
	
	public int LottoNumberInput() {
		int num = sc.nextInt();
		if(num > 0 && num <= 45) return num;
		else return 0;
	}
	
	
	
}
