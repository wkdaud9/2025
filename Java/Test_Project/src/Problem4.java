class Problem4{
	private Lotto l = new Lotto(); // 로또 관련 정보 모은 클래스
	private InputManager im;
	
	public Problem4(InputManager im) {
		this.im = im;
	}

	public void control() {
		
		System.out.println("Lotto 번호 생성기 프로그램입니다.");
		System.out.println("자동 : 0, 수동(개수) : 1~6");
		System.out.println("개수를 입력하세요(0~6) : ");
		
		l.setNumber(im.LottoWhatinput());
		insertNumber();
		printLotto();
	}
	
	private void insertNumber() {
		int index = 0;
		int num;

		if(l.getNumber()==0) {
			l.insertRandomNumber(0, 6); // 매개변수 1부터 매개변수 2 까지 랜덤 값으로 채우는 함수(자동에도 중복 제거)
			return;
		}
		
		 while(index < l.getNumber()) {
				System.out.println((index + 1) + "번째 번호를 입력하세요(1~45) : ");
				num = im.LottoNumberInput(index);
				while(l.duplication(num, index)) {
					System.out.println(num +"은 중복된 번호입니다. 다시 " + (index + 1) +"번째 번호를 입력하세요(1~45) : ");
					num = im.LottoNumberInput(index);
				}
				l.setLottoNum(num, index);
				index++;
		 }
		 l.insertRandomNumber(index, 6);
	}
	
	private void printLotto() {

		System.out.print("생성된 Lotto 번호들 : ");
		for(int i=0; i<6; i++) {
			System.out.print(l.getLottoNum(i) + " ");
		}
		System.out.println();
		
		l.arraySort();
		
		System.out.print("정렬된 Lotto 번호들 : ");
		for(int i=0; i<6; i++) {
			System.out.print(l.getLottoNum(i) + " ");
		}
		System.out.println();

	}
	
}
