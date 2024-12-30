#ifndef Person_H
#define Person_H

#include <iostream>
#include <string>
#include <fstream>
#include "ID.h"


using namespace std;

class person : public ID
{
	protected:
		string name;
		string address;
		string phoneNumber;
		int gender;
	public:
		person(){}
		person(string, string, string, int);
		virtual ~person() {}
		
		string getName();
		
		virtual void viewDetailedInformation();
		virtual void updateInformation();		
};

person::person(string name, string address, string phoneNumber, int gender): name(name),
address(address), phoneNumber(phoneNumber), gender(gender)
{

}

string person::getName()
{
	return this->name;
}

void person::viewDetailedInformation()
{
	cout << "\nName: " << name << "\nAddress: " << address << "\nPhone Number: " << phoneNumber ;
	if(gender == 1)
		cout << "\nGender: Nam";
	else
		cout << "\nGender: Nu";
}

void person::updateInformation()
{
	cout << "What personal information do you want to change?\n";
	cout << "1. Name: " << name;
	cout << "\n2. Address " << address;
	cout << "\n3. PhoneNumber" << phoneNumber;
	cout << "\n4. gender: ";
	if(gender == 1)
		cout << "\nGender: Nam";
	else
		cout << "\nGender: Nu";
	while(true)
	{
		cout << "\nYour choose is: ";
		int yourChoose;
		cin >> yourChoose;
		
		string new_string;
		int check = 0;
		switch(yourChoose)
		{
			case 1:
				cout << "New Name: ";
				cin.ignore();
				getline(cin,this->name);
				break;
			case 2:
				cout << "New Address: ";
				cin.ignore();
				getline(cin, this->address);
				break;
			case 3:
				cout << "New Phone Number: ";
				cin.ignore();
				getline(cin,new_string);
				if(new_string.length() != 10)
					cout << "Invalid Phone Number: ";
				else
					this->phoneNumber = new_string;
				break;
			case 4:
				cout << "gender: nam or nu   (1/0): ";
				cin >> this->gender;
				break;
		}
		cout << "Do you want to continue ?(1/0)";
		bool is_continue;
		cin >> is_continue;
		if(!is_continue)
			break;
	}
}

#endif
