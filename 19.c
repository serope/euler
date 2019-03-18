/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 19
 **********************************************************************/
#include <stdio.h>
#include <stdbool.h>

enum {SUN, MON, TUE, WED, THU, FRI, SAT};
enum {JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};

struct date {
	int day_of_year;
	int day_of_month;
	int weekday_name;
	int month;
	int year;
};

void print_date(struct date d);
void next_day(struct date* d);
int days_in_month(int month, int year);
int days_in_year(int year);
bool is_leap_year(int year);




int main() {
	/*******************************************************************
	 * 1. Initialize the date of Jan 1, 1900 (Monday)
	 ******************************************************************/
	struct date current_date;
	current_date.day_of_year	= 1;
	current_date.day_of_month	= 1;
	current_date.weekday_name	= MON;
	current_date.month			= JAN;
	current_date.year			= 1900;
	
	print_date(current_date);
	
	
	/*******************************************************************
	 * 2. Increase days until the problem's start date is reached
	 *    Jan 1, 1901
	 ******************************************************************/
	while (current_date.year < 1901)
		next_day(&current_date);
	
	
	/*******************************************************************
	 * 3. Increase days until Dec 31, 2000 is reached
	 *    Count each Sunday which is on day 1 of each month
	 ******************************************************************/
	int total_first_sundays = 0;
	
	while (current_date.year < 2001) {
		if (current_date.weekday_name==SUN && current_date.day_of_month==1) {
			print_date(current_date);
			total_first_sundays += 1;
		}
		next_day(&current_date);
	}
	
	printf("total_first_sundays     %d \n", total_first_sundays);
	return 0;
}






/***********************************************************************
 * Date functions
 **********************************************************************/
void next_day(struct date* d) {
	d->day_of_year	+= 1;
	d->day_of_month	+= 1;
	d->weekday_name	+= 1;
	
	
	//At the end of the month, go to the next month
	if (d->day_of_month == days_in_month(d->month, d->year)+1) {
		if (d->month == DEC)
			d->month = JAN;
		else
			d->month += 1;
		
		d->day_of_month = 1;
	}
	
	
	//At the end of the year, go to the next year
	if (d->day_of_year == days_in_year(d->year)+1) {
		d->day_of_year = 1;
		d->year += 1;
	}
	
	
	//At the end of the week, go to the next week
	if (d->weekday_name == SAT+1)
		d->weekday_name = SUN;
}


void print_date(struct date d) {
	const char* n;
	switch (d.weekday_name) {
		case SUN:
			n = "Sun";
			break;
		case MON:
			n = "Mon";
			break;
		case TUE:
			n = "Tue";
			break;
		case WED:
			n = "Wed";
			break;
		case THU:
			n = "Thu";
			break;
		case FRI:
			n = "Fri";
			break;
		case SAT:
			n = "Sat";
			break;
	}
	
	const char* m;
	switch (d.month) {
		case JAN:
			m = "Jan";
			break;
		case FEB:
			m = "Feb";
			break;
		case MAR:
			m = "Mar";
			break;
		case APR:
			m = "Apr";
			break;
		case MAY:
			m = "May";
			break;
		case JUN:
			m = "Jun";
			break;
		case JUL:
			m = "Jul";
			break;
		case AUG:
			m = "Aug";
			break;
		case SEP:
			m = "Sep";
			break;
		case OCT:
			m = "Oct";
			break;
		case NOV:
			m = "Nov";
			break;
		case DEC:
			m = "Dec";
			break;
	}
	
	printf("%s %d, %d (%s) (%d/%d) \n", 
	m, d.day_of_month, d.year, n, d.day_of_year, days_in_year(d.year));
}




/***********************************************************************
 * Miscellaneous functions
 **********************************************************************/
int days_in_month(int month, int year) {
	switch (month) {
		case SEP:
		case APR:
		case JUN:
		case NOV:
			return 30;
			
		case FEB: {
			if (is_leap_year(year))
				return 29;
			else
				return 28;
		}
	}
	
	return 31;
}



int days_in_year(int year) {
	if (is_leap_year(year))
		return 366;
	
	return 365;
}



bool is_leap_year (int year) {
	//Centuries (100, 200, etc.)
	if (year%100==0) {
		if (year%400==0)
			return true;
		else
			return false;
	}
	
	//Non-centuries
	if (year%4==0)
		return true;
	
	return false;
}
