/*
 * Project Euler
 * 19.c
 */
#include <stdio.h>
#include <stdbool.h>

typedef struct date_s {
	int day_of_year;
	int day_of_month;
	int weekday;
	int month;
	int year;
} date_t;

enum {SUN, MON, TUE, WED, THU, FRI, SAT};
enum {JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};

date_t			date_new(int doy, int dom, int wd, int m, int y);
void			date_print(date_t d);
void			date_increment(date_t* d);
bool			date_is_first_sunday(date_t d);
const char*		month_to_string(int month);
const char*		weekday_to_string(int weekday);
int				days_in_month(int month, int year);
int				days_in_year(int year);
bool			is_leap_year(int year);
int				total_first_sundays(date_t start, int end_year);

int main() {
	// initialize Jan 1, 1900 (Mon)
	date_t start = date_new(1, 1, MON, JAN, 1900);
	date_print(start);
	
	/*
	 * increment days until the problem's start date is reached
	 * (Jan 1, 1901)
	 */
	while (start.year < 1901)
		date_increment(&start);
	
	// solve
	int total = total_first_sundays(start, 2000);
	printf("total %d \n", total);
	return 0;
}


/**
 * Creates a new date.
 *
 * @param	doy		day of year
 * @param	dom		day of month
 * @param	wd		weekday
 * @param	m		month
 * @param	y		year
 * @return			a new date instance
 */
date_t date_new(int doy, int dom, int wd, int m, int y) {
	date_t d;
	d.day_of_year	= doy;
	d.day_of_month	= dom;
	d.weekday		= wd;
	d.month			= m;
	d.year			= y;
	return d;
}

/**
 * Returns the month's name.
 * 
 * @param	month	a month enum
 * @return			a string
 */
const char* month_to_string(int month) {
	static const char* months[12];
	months[JAN] = "Jan";
	months[FEB] = "Feb";
	months[MAR] = "Mar";
	months[APR] = "Apr";
	months[MAY] = "May";
	months[JUN] = "Jun";
	months[JUL] = "Jul";
	months[AUG] = "Aug";
	months[SEP] = "Sep";
	months[OCT] = "Oct";
	months[NOV] = "Nov";
	months[DEC] = "Dec";
	return months[month];
}


/**
 * Returns the weekday's name.
 * 
 * @param	weekday		a weekday int
 * @return				a string
 */
const char* weekday_to_string(int weekday) {
	static const char* weekdays[7];
	weekdays[SUN] = "Sun";
	weekdays[MON] = "Mon";
	weekdays[TUE] = "Tue";
	weekdays[WED] = "Wed";
	weekdays[THU] = "Thu";
	weekdays[FRI] = "Fri";
	weekdays[SAT] = "Sat";
	return weekdays[weekday];
}


/**
 * Increments d to the next day.
 * 
 * @param	d	a pointer to a date
 */
void date_increment(date_t* d) {
	d->day_of_year	+= 1;
	d->day_of_month	+= 1;
	d->weekday		+= 1;
	
	// next month
	if (d->day_of_month == days_in_month(d->month, d->year)+1) {
		if (d->month == DEC)
			d->month = JAN;
		else
			d->month += 1;
		d->day_of_month = 1;
	}
	
	// next year
	if (d->day_of_year == days_in_year(d->year)+1) {
		d->day_of_year = 1;
		d->year += 1;
	}
	
	// next week
	if (d->weekday == SAT+1)
		d->weekday = SUN;
}


/**
 * Returns true if the date is a Sunday on the 1st of the month.
 * 
 * @param	d	the date to check
 * @return		true or false
 */
bool date_is_first_sunday(date_t d) {
	return d.weekday == SUN && d.day_of_month == 1;
}


/**
 * Prints the date in a human-readable format.
 * 
 * @param	d	the date to be printed
 */
void date_print(date_t d) {
	const char* n = weekday_to_string(d.weekday);
	const char* m = month_to_string(d.month);
	printf("%s %d, %d (%s) (%d/%d) \n", m,
										d.day_of_month,
										d.year,
										n,
										d.day_of_year,
										days_in_year(d.year));
}


/**
 * Counts the amount of days in the month of a given year.
 * 
 * @param	month	the month
 * @param	year	the year
 * @return			an integer; 28-31
 */
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


/**
 * Counts the amount of days in the given year.
 * 
 * @param	year	the year to check
 * @return			an integer; 365 or 366
 */
int days_in_year(int year) {
	if (is_leap_year(year))
		return 366;
	return 365;
}


/**
 * Returns true if the year is a leap year.
 * 
 * @param	year	the year to check
 * @return			true or false
 */
bool is_leap_year(int year) {
	if (year%100==0) {		// centuries (100, 200, etc.)
		if (year%400==0)
			return true;
		else
			return false;
	}
	if (year%4==0)			// non-centuries
		return true;
	return false;
}


/**
 * Counts the amount of first Sundays between the given start date and
 * the end year.
 * 
 * @param	start		the date to start counting from
 * @param	end_year	the year to stop at
 * @return				an integer
 */
int total_first_sundays(date_t start, int end_year) {
	int total = 0;
	while (start.year < end_year) {
		if (date_is_first_sunday(start)) {
			date_print(start);
			total += 1;
		}
		date_increment(&start);
	}
	return total + 1;
}
