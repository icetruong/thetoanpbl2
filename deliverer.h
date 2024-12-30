#ifndef Deliverer_H
#define Deliverer_H

#include <iostream>
#include <string>
#include "Person.h"
#include "order.h"

using namespace std;

typedef class order* ListOrder;
class deliverer : public person
{
	private:
		string account;
		string password;
		int state; //0: busy, 1: freetime, 2: delivering
		ListOrder ListOrderDelivering;

		class deliverer *headDeliverer;
		class deliverer *lastDeliverer;
	public:
		class deliverer *next;
		
		void handle_create_deliverer(deliverer *D)
		{
			this->lastDeliverer->next = D;
			this->lastDeliverer = D;
		}
		
		deliverer();
		deliverer(string, string, string, int, int,string,string,ListOrder);
		deliverer(const deliverer&);
		virtual ~deliverer() {}

		virtual void updateInformation();
		
		void viewState();
		void setState(int state);
		void viewListDeliverer();
		
		void addDeliverer(deliverer* );
		
		friend ostream& operator << (ostream&, deliverer&);
		friend istream& operator >> (istream& , deliverer&);
		
		typedef class deliverer *ListDeliverver;
		friend ListDeliverver create_list_deliverer();
		
		friend deliverer* Login(ListDeliverver ,string , string);
		
		void ReceiveOrder(ListOrder LO,deliverer* D);
		void viewListOrderDelivering();
		void MakeDeliverer(ListOrder LO,deliverer* D);
		
		friend void writeFileDeliverer(ListDeliverver LD);
		void readFileDeliverer(ListOrder LO);
};

deliverer::deliverer()
{
	next = NULL;
	ListOrderDelivering = create_list_order();
}

deliverer::deliverer(string name, string address, string phoneNumber, int gender, int state, string account, string password,ListOrder ListOrderDelivering)
:person(name, address, phoneNumber, gender), state(state), account(account), password(password),ListOrderDelivering(ListOrderDelivering)
{
	next = NULL;
}

deliverer::deliverer(const deliverer& D):person(D.name, D.address, D.phoneNumber, D.gender)
{
	this->state = D.state;
	this->account = D.account;
	this->password = D.password;
	*this->ListOrderDelivering = *D.ListOrderDelivering;
}

void deliverer::updateInformation()
{
	person::updateInformation();
}

void deliverer::viewState()
{
	cout << "\nState: ";
	if(state == 0)
		cout << "Busy";
	else
		if(state == 1)
			cout << "Free time";
		else
			cout << "Delivering";
}

void deliverer::setState(int state)
{
	this->state = state;
}

void deliverer::viewListDeliverer()
{
	deliverer* D = new deliverer;
	D = this->next;
	while(D!=NULL)
	{
		cout << *D;
		D = D->next;
	}
}

void deliverer::addDeliverer(deliverer* D)
{
	if(D->ID.empty())
		D->ID = this->increase_ID(this->lastDeliverer->ID);
	deliverer* temp = new deliverer;
	*temp = *D;
	this->handle_create_deliverer(temp);
}

ostream& operator << (ostream& os, deliverer& D)
{
	os << "\n<----- Deliverer information ----->";
	D.viewDetailedInformation();
	D.viewState();
	
	return os;
}

istream& operator >> (istream& is, deliverer& D)
{
	int i = 0;
	cout << "Enter information :\n 1. name: ";
	getline(is,D.name);
	cout << "2. address: ";
	getline(is,D.address);
	
	while(true)
	{
		if(i > 0)
			cout << "\nPlease retype the correct phoneNumber again.\n";
		cout << "3. phoneNumber: ";
		getline(is,D.phoneNumber);
		if(D.phoneNumber.length() == 10)
			break;
		i++;
	}
		
	cout << "4. gender: nam/ nu (1/0) ";
	is >> D.gender;
	
	cout << "5. state: busy, freetime, delivering: (0/1/2)";
	is >> D.state;
	
	is.ignore();
	i = 0;
	string new_account;
	do
	{
		if(i > 0)
			cout << "\nPlease retype the correct account again.\n";
		cout << "5. Your account: ";
		getline(is,D.account);
		cout << "6. Retype your account: ";
		getline(is,new_account);
		i++;
	} while(new_account.compare(D.account));
	i = 0;
	string new_password;
	do
	{
		if(i > 0)
			cout << "Please retype the correct password again.\n";
		cout << "7. Your password: ";
		getline(is,D.password);
		cout << "8. Retype your password: ";
		getline(is,new_password);
		i++;
	} while(new_password.compare(D.password));
	
	return is;
}

void deliverer::ReceiveOrder(ListOrder LO, deliverer* D)
{
	order *temp = LO->next;
	while(true)
	{	
		cout << "\nEnter ID order you want to deliver: ";
		string ID_order_deliver;
		
		cin.ignore();
		getline(cin,ID_order_deliver);
		while(temp != NULL )
		{
			if(!temp->getID().compare(ID_order_deliver) && temp->get_status() == 0)
			{
				temp->set_status(1);
				deliverer* DL_temp = this->next;
				cout << "hehe";
				while(DL_temp != NULL)
				{
					if(!DL_temp->getID().compare(D->getID()))	
					{
						DL_temp->ListOrderDelivering->add_order(temp);
						DL_temp->state = 2;
						break;
					}
					DL_temp = DL_temp->next;
				}
				break;
			}		
			temp = temp->next;
		}
		if(temp == NULL)
			cout << "\nInvalid ID\n";
		else
			cout << "\nGet Deliver successfull\n";
		cout << "\nDo you want to continue to get order to deliver ? (1/0)";
		bool is_continue;
		cin >> is_continue;
		if(!is_continue)
			break;	
	}
}

void deliverer::viewListOrderDelivering()
{
	this->ListOrderDelivering->viewListOrder();
}

void deliverer::MakeDeliverer(ListOrder LO, deliverer* D)
{
	order *temp = LO->next;
	cout << "\nEnter ID order you want to make deliver: ";
	string ID_order_deliver;
	
	cin.ignore();
	getline(cin,ID_order_deliver);
	while(temp != NULL )
	{
		if(!temp->getID().compare(ID_order_deliver) && temp->get_status() == 1)
		{
			temp->set_status(2);
			deliverer* DL_temp = this->next;
			while(DL_temp != NULL)
			{
				if(!DL_temp->getID().compare(D->getID()))	
					DL_temp->ListOrderDelivering->delete_order(temp);
				DL_temp = DL_temp->next;
			}
			break;
		}		
		temp = temp->next;
	}
	this->state = 1;
}

typedef class deliverer *ListDeliverver;
ListDeliverver create_list_deliverer()
{
	ListDeliverver LD = new deliverer;
	LD->ID = ID_default;
	LD->headDeliverer = LD;
	LD->lastDeliverer = LD;
	
	return LD;
}

deliverer* Login(ListDeliverver LD, string account, string password)
{
	LD = LD->next;
	while(LD != NULL)
	{
		if(!account.compare(LD->account))
			break;
		LD = LD->next;
	}
	
	if(LD == NULL)
		return NULL;

	if(password.compare(LD->password))
	{
		cout << "There is an error with the account or password !!!";
		return NULL;	
	}
	else
		cout << "Login account deliverer successfull";
	return LD;
}

void writeFileDeliverer(ListDeliverver LD)
{
	ofstream File;
	File.open("deliverer.txt"); 
	LD = LD->next;
	while(LD != NULL)
	{
		File << LD->ID << ",";
		File << LD->name << ",";
		File << LD->address << ",";
		File << LD->phoneNumber << ",";
		File << LD->gender << ",";
		File << LD->state << ",";
		File << "(";
		while(LD->ListOrderDelivering->next != NULL)
		{
			File << LD->ListOrderDelivering->next->getID() << ",";
			LD->ListOrderDelivering = LD->ListOrderDelivering->next;
		}
		File << ")";
		File << LD->account << ",";
		File << LD->password << "\n";
		
		LD = LD->next;
	}
	File << "end file";
	File.close();
}

void deliverer::readFileDeliverer(ListOrder LO)
{
	ifstream File;
	File.open("deliverer.txt");
	string line;
	while(true)
	{		
	
		deliverer* temp = new deliverer;
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
		string state;
		state = line.substr(start, end - start);
		temp->state = state[0] - '0';
		start = end + 2;
		
		while(true)
		{	
			if(line[start] == ')')
				break;
			end = line.find(',',start);
			string id_order;
			id_order = line.substr(start, end - start);
			order* order_temp = LO;
			while(order_temp->next != NULL)
			{
				if(!id_order.compare(order_temp->next->getID()))
				{
					temp->ListOrderDelivering->add_order(order_temp->next);
					break;
				}
				order_temp = order_temp->next;
			}
			start = end + 1;
		}
		start++;
		
		end = line.find(',',start);
		temp->account = line.substr(start, end - start);
		start = end + 1;
		
		temp->password = line.substr(start, length_line);
		
		this->addDeliverer(temp);
	}
	File.close();
}



#endif
