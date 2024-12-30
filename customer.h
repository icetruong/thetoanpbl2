#ifndef Customer_H
#define Customer_H

#include <iostream>
#include <string>
#include <fstream>
#include "Person.h"

using namespace std;


class customer : public person
{
	private:
		string account;
		string password;
		
		class customer *headCustomer;
		class customer *lastCustomer;
		
	public:
		class customer *next;
		
		void handle_create_customer(customer *C)
		{
			this->lastCustomer->next = C;
			this->lastCustomer = C;
		}
		
		customer();
		customer(string, string, string, int, string, string);
		virtual ~customer() {}
		
		virtual void updateInformation();

		friend ostream& operator << (ostream&, customer&);
		
		typedef class customer *ListCustomer;
		friend ListCustomer create_list_customer();
		
		void addCustomer(customer* );
		
		friend istream& operator >> (istream& , customer& );
		friend customer* Login(ListCustomer ,string , string );
		friend customer* Register(ListCustomer );
		
		friend void writeFileCustomer(ListCustomer);
		void readFileCustomer();
};

customer::customer()
{
	next = NULL;
}
customer::customer(string name, string address, string phoneNumber, int gender, string account, string password)
: person(name, address, phoneNumber, gender), account(account), password(password)
{
	next = NULL;
}

ostream& operator << (ostream& os, customer& C)
{
	cout << "<----- Customer information ----->";
	C.viewDetailedInformation();
	
	return os;
}

void customer::updateInformation()
{
	while(true)
	{	
		cout << "What information do you want to change?\n";
		cout << "1. Personal information\n2. Login information";
		cout << "\nYour choose is: ";
		int yourChoose;
		cin >> yourChoose;
		switch(yourChoose)
		{
			case 1:
				system("cls");
				person::updateInformation();
				break;
			case 2:
				system("cls");
				cout << "What Login information do you want to change?\n";
				cout << "1. Account\n2.Password";
				cout << "\nYour choose is: ";
				cin >> yourChoose;
				cin.ignore();
				if(yourChoose == 1)
				{
					cout << "Old account: ";
					string old_account;
					getline(cin,old_account);
					if(old_account.compare(account))
					{
						cout << "Old account not true ";
						break;
					}
					else
					{
						cout << "New account: ";
						getline(cin,account);
					}
					if(!old_account.compare(account))
					{
						cout << "New account same old account";
						break;
					}
					cout << "Retype the new account: ";
					string new_account;
					getline(cin,new_account);
					if(!new_account.compare(account))
					{
						cout << "New account not true ";
						cout << "Account change failed ";
						account = old_account;
						break;
					}
					else
						cout << "Account change successfully" ;				
				}
				else
				{
					cout << "Old password: ";
					string old_password;
					getline(cin,old_password);
					if(old_password.compare(password))
					{
						cout << "Old password not true ";
						break;
					}
					else
					{
						cout << "New password: ";
						getline(cin,password);
					}
					if(!old_password.compare(password))
					{
						cout << "New password same old password";
						break;
					}
					cout << "Retype the password: ";
					string new_password;
					getline(cin,new_password);
					if(!new_password.compare(password))
					{
						cout << "New password not true ";
						cout << "password change failed ";
						password = old_password;
						break;
					}
					else
						cout << "password change successfully\n" ;
				}
				break;
		}
		cout << "\nDo you want to continue change information?(1/0)";
		bool is_continue;
		cin >> is_continue;
		if(!is_continue)
			break;
	}
}

typedef class customer *ListCustomer;
ListCustomer create_list_customer()
{
	ListCustomer LC = new customer;
	LC->ID = ID_default;
	LC->headCustomer = LC;
	LC->lastCustomer = LC;
	
	return LC;
}

istream& operator >> (istream& is, customer& CT)
{
	int i = 0;
	cout << "Enter information :\n 1. name: ";
	getline(is,CT.name);
	cout << "2. address: ";
	getline(is,CT.address);
	
	while(true)
	{
		if(i > 0)
			cout << "\nPlease retype the correct phoneNumber again.\n";
		cout << "3. phoneNumber: ";
		getline(is,CT.phoneNumber);
		if(CT.phoneNumber.length() == 10)
			break;
		i++;
	}
		
	cout << "4. gender: nam/ nu (1/0) ";
	is >> CT.gender;
	is.ignore();
	i = 0;
	string new_account;
	do
	{
		if(i > 0)
			cout << "\nPlease retype the correct account again.\n";
		cout << "5. Your account: ";
		getline(is,CT.account);
		cout << "6. Retype your account: ";
		getline(is,new_account);
		i++;
	} while(new_account.compare(CT.account));
	i = 0;
	string new_password;
	do
	{
		if(i > 0)
			cout << "Please retype the correct password again.\n";
		cout << "7. Your password: ";
		getline(is,CT.password);
		cout << "8. Retype your password: ";
		getline(is,new_password);
		i++;
	} while(new_password.compare(CT.password));
	
	return is;	
}

customer* Login(ListCustomer LC, string account, string password)
{
	LC = LC->next;
	while(LC != NULL)
	{
		if(!account.compare(LC->account))
			break;
		LC = LC->next;
	}
	if(LC == NULL)
		return NULL;
	if(password.compare(LC->password))
	{
		cout << "There is an error with the account or password !!!";
		return NULL;	
	}
	else
		cout << "Login successfull";
	return LC;
}

customer* Register(ListCustomer LC)
{
	customer *C = new customer;
	cin >> *C;
	LC->addCustomer(C);
	while(LC->next->next != NULL)
	{
		if(!C->account.compare(LC->next->account))
		{
			cout << "account has existed, please register again";
			return NULL;
		}
		LC = LC->next;
	}
	system("cls");
	cout << "\n Registration successful!!!!";
	return C;
}

void customer::addCustomer(customer* C)
{
	if(C->ID.empty())
		C->ID = this->increase_ID(this->lastCustomer->ID);
	customer* temp = new customer;
	*temp = *C;
	this->handle_create_customer(temp);
}

void writeFileCustomer(ListCustomer LC)
{
	ofstream File;
	File.open("customer.txt"); 
	LC = LC->next;
	while(LC != NULL)
	{
		File << LC->ID << ",";
		File << LC->name << ",";
		File << LC->address << ",";
		File << LC->phoneNumber << ",";
		File << LC->gender << ",";
		File << LC->account << ",";
		File << LC->password << "\n";
		LC = LC->next;
	}
	File << "end file";
	File.close();
}

void customer::readFileCustomer()
{
	ifstream File;
	File.open("customer.txt");
	string line;
	customer* temp = new customer;
	while(true)
	{		
		getline(File, line);
		if(!line.compare("end file"))
			break;
		int length_line = line.length();
		int start = 0;
		int end = 0;
		
		end = line.find(',',start);
		temp->ID = line.substr(start, end - start);
		start = end + 1;
		
		end = line.find(',',start);
		temp->name = line.substr(start, end - start);
		start = end + 1;
		
		end = line.find(',',start);
		temp->address = line.substr(start, end - start);
		start = end + 1;
		
		end = line.find(',',start);
		temp->phoneNumber = line.substr(start, end - start);
		start = end + 1;
		
		end = line.find(',',start);
		string gender;
		gender = line.substr(start, end - start);
		temp->gender = gender[0] - '0';
		start = end + 1;
		
		end = line.find(',',start);
		temp->account = line.substr(start, end - start);
		start = end + 1;
		
		temp->password = line.substr(start, length_line);
		
		this->addCustomer(temp);
	}
	File.close();
}



#endif
