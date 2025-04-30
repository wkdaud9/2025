public class K2401528_Project {

	public static void main(String[] args) {
		int n;
		InputManager im = new InputManager(); // input 전담 클래스
		Manage manage = new Manage(im);	// 전체적인 관리 클래스
		
		do {
			System.out.println("어떤 과제를 실행할까요? : (1: 1번 과제 , 2: 2번 과제 , 3: 3번 과제, 4: 4번 과제, 99: 종료)");
			n = im.inputOneNumber();
			if(n == 1) manage.getProblem1().control();
			else if(n == 2) manage.getProblem2().control();
			else if(n == 3) manage.getProblem3().control();
			else if(n == 4) manage.getProblem4().control();
			
		} while (n != 99);

		System.out.println("프로그램을 종료합니다. 감사합니다.");
	}

}
