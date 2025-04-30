
public class DateInfo {
	
	private int year, month, day;
	private int mDay[] = new int[13];
	
	public void setYear(int year) {
		this.year = year;
		setMonthDays();
		setTwoMonth();
	}
	public void setMonth(int month) {this.month = month;}
	public void setDay(int day) {this.day = day;}
	public int getYear() {return year;}
	public int getMonth() {return month;}
	public int getDay() {return day;}
	public int getMonthDays(int m) {return mDay[m];}
	public int getyearAllDay() {
		int yearAllDay = 0;
		for(int i=1; i<=12; i++) {
			yearAllDay += getMonthDays(i);
		}
		return yearAllDay;
	}
	
	public int getBeforeDay() {
		int beforeDay = 0;
		for(int i=1; i<month; i++) {
			beforeDay += getMonthDays(i);
		}
		beforeDay += day;
		return beforeDay;
	}
	
	private void setTwoMonth() {
		if(checkYun()) mDay[2] = 29;
		else mDay[2] = 28;
	}
	
	private void setMonthDays() {
		for(int i=1; i<=12; i++) {
			if(i <= 7) {
				if(i % 2 == 0 && i != 2) mDay[i] = 30;
				else if(i%2 != 0) mDay[i] = 31;
			}
			else {
				if(i % 2 == 0 && i!= 2) mDay[i] = 31;
				else if(i%2 != 0) mDay[i] = 30;
			}
		}
	}
	
	
	private boolean checkYun() {
		if(year % 4 == 0 && year % 100 != 0) {
			return true;
		} else if(year % 400 == 0) {
			return true;
		} else return false;
	}
	
}
