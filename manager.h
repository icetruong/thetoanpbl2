#ifndef Manager_H
#define Manager_H

#include <iostream>
#include <string>
#include "Person.h"

using namespace std;

class manager : public person
{
	private:
		string account;
		string password;
		
		class manager *headManager;
		class manager *lastManager;
	public:	
		class manager *next;
		
		void handle_create_manager(manager *M)
		{
			this->lastManager->next = M;
			this->lastManager = M;
		}
		
		manager();
		manager(string, string, string, int, string, string);
		virtual ~manager() {}
		
		virtual void updateInformation();
		
		void addManager(manager* );
		
		manager* handle_check_name_manager(string name);
		
		friend ostream& operator << (ostream&, const manager&);
		friend istream& operator >> (istream&, manager&);

		typedef class manager *ListManager;
		friend ListManager create_list_manager();
		
		friend manager* Login(ListManager ,string , string );
		friend void writeFileManager(ListManager);
		void readFileManager();
};

manager::manager()
{
	next = NULL;
}

manager::manager(string name, string address, string phoneNumber, int gender, string account, string password)
:person(name, address, phoneNumber, gender), account(account), password(password)
{
	next = NULL;
}

void manager::updateInformation()
{
	person::updateInformation();
}

void manager::addManager(manager* M)
{
	if(M->ID.empty())
		M->ID = this->increase_ID(this->lastManager->ID);
	manager* temp = new manager;
	*temp = *M;
	this->handle_create_manager(temp);
}

manager* manager::handle_check_name_manager(string name)
{
	manager* M = this->next;
	while(M != NULL)
	{
		if(!name.compare(M->name))
			return M;
		M = M->next;
	}
	return NULL;
}

ostream& operator << (ostream& os, const manager& M)
{
	os << M.name << " phone number: "<< M.phoneNumber << endl;
	
	return os;
}

istream& operator >> (istream& is, manager& M)
{
	int i = 0;
	cout << "Enter information :\n 1. name: ";
	getline(is,M.name);
	cout << "2. address: ";
	getline(is,M.address);
	
	while(true)
	{
		if(i > 0)
			cout << "\nPlease retype the correct phoneNumber again.\n";
		cout << "3. phoneNumber: ";
		getline(is,M.phoneNumber);
		if(M.phoneNumber.length() == 10)
			break;
		i++;
	}
		
	cout << "4. gender: nam/ nu (1/0) ";
	is >> M.gender;
	
	i = 0;
	string new_account;
	do
	{
		if(i > 0)
			cout << "\nPlease retype the correct account again.\n";
		else
			is.ignore();
		cout << "5. Your account: ";
		getline(is,M.account);
		cout << "6. Retype your account: ";
		getline(is,new_account);
		i++;
	} while(new_account.compare(M.account));
	i = 0;
	string new_password;
	do
	{
		if(i > 0)
			cout << "Please retype the correct password again.\n";
		cout << "7. Your password: ";
		getline(is,M.password);
		cout << "8. Retype your password: ";
		getline(is,new_password);
		i++;
	} while(new_password.compare(M.password));
	
	return is;
}

typedef class manager *ListManager;
ListManager create_list_manager()
{
	ListManager LM = new manager;
	LM->ID = ID_default;
	LM->headManager = LM;
	LM->lastManager = LM;
	
	return LM;
}

manager* Login(ListManager LM, string account, string password)
{
	LM = LM->next;
	while(LM != NULL)
	{
		if(!account.compare(LM->account))
			break;
		LM = LM->next;
	}
	
	if(LM == NULL)
		return NULL;
	
	if(password.compare(LM->password))
	{
		cout << "There is an error with the account or password !!!";
		return NULL;	
	}
	else
		cout << "Login account manager successfull";
	return LM;
}

void writeFileManager(ListManager LM)
{
	ofstream File;
	File.open("manager.txt"); 
	LM = LM->next;
	while(LM != NULL)
	{
		File << LM->ID << ",";
		File << LM->name << ",";
		File << LM->address << ",";
		File << LM->phoneNumber << ",";
		File << LM->gender << ",";
		File << LM->account << ",";
		File << LM->password << "\n";
		LM = LM->next;
	}
	File << "end file";
	File.close();
}

void manager::readFileManager()
{
	ifstream File;
	File.open("manager.txt");
	string line;
	manager* temp = new manager;
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
		
		this->addManager(temp);
	}
	File.close();
}


#endif
