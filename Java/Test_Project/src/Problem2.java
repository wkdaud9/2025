class Problem2{
	private DateInfo di = new DateInfo();	// 날짜 관련 정보 및 메서드들 모은 클래스
	private InputManager im;
	
	public Problem2(InputManager im) {
		this.im = im;
	}

	public void control() {
		System.out.println("년 월 일을 입력하면 그해의 총 날수와 몇 번째 날인지 출력하는 프로그램 ");
		
		int y = im.getYear();
		di.setYear(y);
		
		int m = im.getMonth();
		di.setMonth(m);
		
		int d = im.getDay(di.getMonthDays(m));
		di.setDay(d);

		printResult();
	}
	
	private void printResult() {
		System.out.println(di.getYear() +"년도는 총 " + di.getyearAllDay() + "입니다. ");
		System.out.println(di.getYear() + "년 " + di.getMonth() +"월 " + di.getDay() + "일은 " + di.getYear() + "년도의 " 
		+ di.getBeforeDay() + "번째 날입니다. ");
		System.out.println();
	}
	
}