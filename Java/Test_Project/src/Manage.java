class Manage {	
	private Problem1 p1;
	private Problem2 p2;
	private Problem3 p3; 
	private Problem4 p4;
	
	public Manage(InputManager im) {
		p1 = new Problem1(im);
		p2 = new Problem2(im);
		p3 = new Problem3(im);
		p4 = new Problem4(im);
	}
	
	public Problem1 getProblem1() {return p1;}
	public Problem2 getProblem2() {return p2;}
	public Problem3 getProblem3() {return p3;}
	public Problem4 getProblem4() {return p4;}
}
