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
		int inputNum;
		int printIndex = 1;

		if(l.getNumber()==0) l.insertRandomNumber(0, 6); // 매개변수 1부터 매개변수 2 까지 랜덤 값으로 채우는 함수(자동에도 중복 제거)
		else if(l.getNumber()<= 6) {
			for(int i=0; i<l.getNumber(); i++) {
				printIndex = i+1;
				System.out.println(printIndex + "번째 번호를 입력하세요(1~45) : ");
				inputNum = im.LottoNumberInput();	// 범위에 속하는 숫자일 경우 return num, 범위 밖이면 return 0
				while(inputNum == 0) {
						System.out.println("입력 범위를 벗어났습니다. 다시 " + printIndex +"번째 번호를 입력하세요(1~45) : ");
						inputNum = im.LottoNumberInput();
					}
				while(l.duplication(inputNum, index) || inputNum == 0) {
					if(l.duplication(inputNum, index)) {
						System.out.println(inputNum +"은 중복된 번호입니다. 다시 " + printIndex +"번째 번호를 입력하세요(1~45) : ");
					}
					else if(inputNum == 0) {
						System.out.println("입력 범위를 벗어났습니다. 다시 " + printIndex +"번째 번호를 입력하세요(1~45) : ");
					}
					inputNum = im.LottoNumberInput();
				}
				l.setLottoNum(inputNum, index++);
			}
			l.insertRandomNumber(index, 6);
		} 
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
