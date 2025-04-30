class Problem3{
	private InputManager im;
	
	public Problem3(InputManager im) {
		this.im = im;
	}

	public void control() {
		int n;
		System.out.println("입력한 수에 맞게 *로 마름모를 그리는 프로그램입니다.");
		System.out.println("정수입력(1~19사이의 홀수) : ");
		n = im.inputOneNumber();
		if(im.checkNum(n)) { 
			for(int i=0; i<n/2 +1; i++) {
				for(int j=i; j<n/2; j++) {
					System.out.print(" ");
				}
				for(int j=0; j<=i*2; j++) {
					System.out.print("*");
				}
				System.out.println();
			}
			
			for(int i=0; i<n-(n/2+1); i++) {
				for(int j=0; j<=i; j++) {
					System.out.print(" ");
				}
				for(int j=i; j<n-2-i; j++) {
					System.out.print("*");
				}
				System.out.println();
			}
		}
		else {
			System.out.println("입력 범위를 벗어났습니다.");
			System.out.println("마름모 그리기 프로그램을 종료합니다.");

		}
	}
}
