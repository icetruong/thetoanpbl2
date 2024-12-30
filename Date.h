#ifndef Date_H
#define Date_H

#include <iostream>

using namespace std;

class Date
{
	private:
		int day;
		int month;
		int year;
			
		static int DayInMonth[13];
	public:
		Date(int = 1, int = 1,int = 2024);
		Date(const Date&);
		
		int getDay();
		int getMonth();
		int getYear();
		
		Date operator + (int);
		Date operator - (int);	
		
		friend istream& operator >>(istream&, Date&);
		friend ostream& operator <<(ostream&,const Date&);
		
		friend class order;
};

int Date::getDay()
{
	return this->day;
}

int Date::getMonth()
{
	return this->month;
}

int Date::getYear()
{
	return this->year;
}

int Date::DayInMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Date::Date(int d, int m, int y) : day(d),month(m),year(y)
{
	if(y % 400 == 0 || (y % 4 == 0 && y% 100 != 0))
		this->DayInMonth[2] = 29;
	int maxDay = this->DayInMonth[m];
	while(this->day > maxDay)
	{
		this->day -= maxDay;
		this->month++;
	}
	if(this->day < 1)
	{
		this->month --;
		if(this->month < 1)
		{
		this->month = 12;
		this->year --;
		}
		this->day = this->DayInMonth[this->month];
	}
	
	while(this->month > 12)
	{
		this->month -= 12;
		this->year++;
	}
	if(this->month < 1)
	{
		this->month = 12;
		this->year --;
	}
}


ostream& operator <<(ostream& os, const Date& D)
{
	os << D.day << "/" << D.month << "/" << D.year << endl;
	
	return os;
}

Date Date::operator + (int d)
{
	return Date(this->day + d,this->month, this->year);
}

Date Date::operator - (int d)
{
	return Date(this->day - d,this->month, this->year);
}

Date::Date(const Date& D):day(D.day),month(D.month),year(D.year)
{
}
		
istream& operator >>(istream& is, Date& D)
{
	cout << "enter day: "; is >> D.day;
	cout << "enter month: "; is >> D.month;
	cout << "enter year: "; is >> D.year;
	
	return is;
}

#endif
