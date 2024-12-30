#ifndef Location_H
#define Location_H

#include <iostream>
#include <string>
#include "manager.h"

using namespace std;

class location: public ID
{
	private:
		string name;
		string address;
		string phoneNumber;
		
		class manager* Manager;
		
		class location *headLocation;
		class location *lastLocation;
	public:
		class location *next;
		
		void handle_create_location(location *L)
		{
			this->lastLocation->next = L;
			this->lastLocation = L;
		}
		
		location();
		location(string, string, string);
		location(const location&);
		
		typedef class location *ListLocation;
		friend ListLocation create_list_location();
		
		location* handle_check_name_location(string name);

		virtual void updateInformation();
		
		friend ostream& operator << (ostream&, const location&);
		friend istream& operator >> (istream&, location&);
		
		const location& operator = (const location&);
		
		void add_manager_in_location(manager* );
		
		void addLocation(location *);
		ListLocation getLocationformManager(manager* );
		void viewListLocation();
		
		friend void writeFileLocation(ListLocation);
		void readFileLocation(ListManager);
};

location::location()
{
	next = NULL;
	this->Manager = new manager;
}

location::location(string name, string address, string phoneNumber)
:name(name), address(address), phoneNumber(phoneNumber)
{
	next = NULL;
}

location::location(const location& L)
{
	this->ID = L.ID;
	this->name = L.name;
	this->address = L.address;
	this->phoneNumber = L.phoneNumber;
	this->Manager = L.Manager;
	this->next = NULL;
}

ostream& operator << (ostream& os, const location& L)
{
	os << "Name: " << L.name << " Address: " << L.address  << L.phoneNumber << " Manager: ";
	os << *L.Manager;

	return os;
}

istream& operator >> (istream& is, location& L)
{
	int i = 0;
	cout << "Enter information :\n 1. name: ";
	getline(is,L.name);
	cout << "2. address: ";
	getline(is,L.address);
	
	return is;
}

const location& location::operator = (const location& L)
{
	this->ID = L.ID;
	this->name = L.name;
	this->address = L.address;
	this->phoneNumber = L.phoneNumber;
	this->Manager = L.Manager;
	this->next = NULL;
	
	return *this;
}

void location::updateInformation()
{
	cout << "What location information do you want to change?\n";
	cout << "1. Name\n2. Address\n";
	while(true)
	{
		cout << "Your choose is: ";
		int yourChoose;
		cin >> yourChoose;
		switch(yourChoose)
		{
			case 1:
				cout << "New Name: ";
				cin.ignore();
				getline(cin, name);
				break;
			case 2:
				cout << "New Address: ";
				cin.ignore();
				getline(cin, address);
				break;
			default:
				cout <<"You enter incorrect";
		}
		cout << "Do you want to continue ?(1/0)";
		bool is_continue;
		cin >> is_continue;
		if(!is_continue)
			break;
	}
}

typedef class location *ListLocation;
ListLocation create_list_location()
{
	ListLocation LL = new location;
	LL->ID = ID_default;
	LL->headLocation = LL;
	LL->lastLocation = LL;
	return LL;
}

location* location::handle_check_name_location(string name)
{
	location* L = this->next;
	while(L != NULL)
	{
		if(!name.compare(L->name))
			return L;
		L = L->next;
	}
	return NULL;
}

void location::add_manager_in_location(manager* M)
{
	this->Manager = M;
}

void location::addLocation(location *L)
{
	if(L->ID.empty())
		L->ID = this->increase_ID(this->lastLocation->ID);
	location* temp = new location;
	*temp = *L;
	this->handle_create_location(temp);
}

ListLocation location::getLocationformManager(manager* M)
{
	location* temp_LL = this->next;
	ListLocation LLFL  = create_list_location();
	while(temp_LL != NULL)
	{
		if(!M->getID().compare(temp_LL->Manager->getID()))
			LLFL->addLocation(temp_LL);
		temp_LL = temp_LL->next;
	}
	return LLFL;
}

void location::viewListLocation()
{
	ListLocation temp_LL = this->next;
	if(temp_LL == NULL)
		cout << "Don't have location!!\n";
	while(temp_LL != NULL)
	{
		cout << *temp_LL;
		temp_LL = temp_LL->next;
	}
}

void writeFileLocation(ListLocation LL)
{
	ofstream File;
	File.open("location.txt"); 
	LL = LL->next;
	while(LL != NULL)
	{
		File << LL->ID << ",";
		File << LL->name << ",";
		File << LL->address << ",";
		File << LL->Manager->getID() << "\n";
		LL = LL->next;
	}
	File << "end file";
	File.close();
}

void location::readFileLocation(ListManager LM)
{
	ifstream File;
	File.open("location.txt");
	string line;
	location* temp = new location;
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
		
		manager* L = new manager;
		L = LM->next;
		string id_manager;
		id_manager = line.substr(start, length_line);
		while(L != NULL)
		{
			if(!id_manager.compare(L->getID()))
			{
				temp->Manager = L;
				break;
			}
			L = L->next;
		}
		
		this->addLocation(temp);	
	}
	File.close();
}

#endif
