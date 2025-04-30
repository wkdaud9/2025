class Problem1{
	private int a, b;
	private InputManager im;
	
	public Problem1(InputManager im) {
		this.im = im;
	}
	
	public void control() {
		int n1, n2;
		System.out.println("시작 정수에서 종료 정수까지 합을 구하는 프로그램입니다.");

		System.out.println("시작 정수를 입력하세요 : ");
		n1 = im.getNumber();
		System.out.println("종료 정수를 입력하세요 : ");
		n2 = im.getNumber();
		setNum(n1, n2);
		System.out.println(n1 + "부터 " + n2 + "까지의 합은? : " + addNum());
		System.out.println();
	}
	private void setNum(int n1, int n2) {
		if(n1 > n2) {
			a = n2;
			b = n1;
		}
		else {
			a = n1;
			b = n2;
		}
	}
	private int addNum() {
		int result = 0;
		for(int i=a; i<=b; i++) {
			result += i;
		}
		return result;
	}
}