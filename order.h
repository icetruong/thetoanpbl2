#ifndef Order_H
#define Order_H

#include <iostream>
#include <string>
#include "customer.h"
#include "Date.h"
#include "item.h"
#include "payment.h"

using namespace std;
typedef class item* ListItem;
class order: public ID
{
	private:
		Date time;
		int status; //0: waiting  1: delivering 2: complete    
		ListItem menu;
		customer* Customer;
		payment Payment;
		
		class order *headOrder;
		class order *lastOrder;
	public:
		class order *next;
		
		void handle_create_order(order *O)
		{
			this->lastOrder->next = O;
			this->lastOrder = O;
		}
		
		order();
		order(Date, int, ListItem, customer*);
		order(const order&);
		
		void add_item_into_order(item*);
		void delete_item_into_order();
		
		int get_status();
		void set_status(int);
		
		typedef class order *ListOrder;
		friend ListOrder create_list_order();
		
		int calc_sum_money();
		
		virtual void viewInformation();
		
		friend ostream& operator << (ostream& , const order&);
		
		const order& operator = (const order& );
		
		void add_order(order*);
		void delete_order(order*);
		
		void PlaceAnOrder(item* , customer*);
		
		order* getHistoryOrder(customer* );
		void viewListOrder();
		
		void viewReportOrderinDay();
		
		void viewOrderIsNotComplete();
		void viewOrderWaiting();
		
		friend void writeFileOrder(ListOrder);
		void readFileOrder(ListCustomer, ListItem);
};

order::order()
{
	next = NULL;
	menu = create_list_item();
	this->Customer = new customer;
}

order::order(Date time, int status, ListItem menu, customer* Customer)
:time(time),status(status),menu(menu),Customer(Customer)
{
	next = NULL;
}

order::order(const order& O)
{
	this->time = O.time;
	this->status = O.status;
	this->menu = O.menu;
	this->Customer = O.Customer;
	this->next = NULL;
}

void order::add_item_into_order(item* I)
{
	item* temp = new item;
	*temp = *I;
	this->menu->addItem(temp);
}

void order::delete_item_into_order()
{
	cout << "Enter the name you want to delete: ";
	string newNameItem;
	getline(cin,newNameItem);
	menu->deleteItem(newNameItem);
}

int order::get_status()
{
	return this->status;
}

void order::set_status(int status)
{
	this->status = status;
}

typedef class order *ListOrder;
ListOrder create_list_order()
{
	ListOrder LO = new order;
	LO->ID= ID_default;
	LO->headOrder = LO;
	LO->lastOrder = LO;
	
	return LO;
}

int order::calc_sum_money()
{
	item* temp = menu->next;
	int sum = 0;
	while(temp != NULL)
	{
		sum += temp->price;
		temp = temp->next;
	}
	Payment.money = sum;
	return sum;
}

ostream& operator << (ostream& os, const order& O)
{
	os << "Day: "<< O.time << "status: ";
	if(O.status == 0)
		os << "waiting!!\n";
	else
		if(O.status == 1)
			os << "delivering!\n";
		else
			os << "complete\n";
	item* temp = O.menu;
	while(temp->next != NULL)
	{
		temp->next->viewInformationItemForCustomer();
		temp = temp->next;
	}
	os <<"\nMoney: " << O.Payment << " \ncustomer: " << *O.Customer;
	
	return os;
}

void order::viewInformation()
{
	cout << "cipher: " << ID << " day: "<< time << "status: ";
	if(status == 0)
		cout << "waiting!!";
	else
		if(status == 1)
			cout << "delivering!\n";
		else
			cout << "complete";
	cout <<" money: " << Payment.money << " customer: ";
	Customer->viewDetailedInformation();
}

const order& order::operator = (const order& O)
{
	this->ID = O.ID;
	this->time = O.time;
	this->status = O.status;
	this->menu = O.menu;
	this->Customer = O.Customer;
	this->Payment = O.Payment;
	this->next = NULL;
	
	return *this;
}

void order::add_order(order* O)
{
	if(O->ID.empty())
		O->ID = this->increase_ID(this->lastOrder->ID);
	order* temp = new order;
	*temp = *O;
	this->handle_create_order(temp);
}

void order::delete_order(order* O)
{
	order *temp = this;
	while(temp->next != NULL)
	{
		if(!O->getID().compare(temp->next->getID()))
		{
			order* newOrder = temp->next;
			temp->next = temp->next->next;
			delete newOrder;
			cout << "delete successfully";
			return;
		}
		temp = temp->next;
	}	
	cout << "delete failed";
		
}

void order::PlaceAnOrder(item* LI, customer* C)
{
	order* newOrder = new order;	
	cin >> newOrder->time;
	newOrder->status = 0;
	newOrder->Customer = C;
	
	LI->viewListItemfromLocation();

	while(true)
	{
		LI->handleSearchItem();
		
		string item_name;
		cout << "\nEnter your choose by name: ";
		getline(cin,item_name);
		item* temp3 = LI->next;
		while(temp3 != NULL)	
		{
			if((item_name.compare(temp3->nameItem)) == 0)
			{
				cout << "Enter number: ";	
				int your_number;
				cin >> your_number;
				for(int j = 0;j<your_number;j++)
					newOrder->add_item_into_order(temp3);
				break;
			}	
			temp3 = temp3->next;			
		}
		if(temp3 == NULL)
			cout << "Don't have item you choose by name, add item failed!\n";
		cout << "Do you want to continue choose item by name?(1/0)";
		int is_continue;
		cin >> is_continue;
		if(!is_continue)
			break;	
			
	}
	newOrder->calc_sum_money();
	newOrder->Payment.handle_payment();
	
	this->add_order(newOrder);
}

order* order::getHistoryOrder(customer* C)
{
	ListOrder temp_LO = this->next;
	ListOrder historyOrder = create_list_order();
	while(temp_LO != NULL)
	{
		string nameCustomer = temp_LO->Customer->getName();
		if(!nameCustomer.compare(C->getName()))
		{
			order* newOrder = new order;
			*newOrder = *temp_LO;
			historyOrder->add_order(newOrder);
		}
		temp_LO = temp_LO->next;
	}
	return historyOrder;
}

void order::viewListOrder()
{
	ListOrder temp_HO = this->next;
	if(temp_HO == NULL)
		cout << "Chua dat hang lan nao!!!\n";
	while(temp_HO != NULL)
	{
		cout << *temp_HO;
		temp_HO = temp_HO->next;
	}
}

void order::viewReportOrderinDay()
{
	cout << "Enter Day: ";
	int day;
	cin >> day;
	cout << "Enter Month: ";
	int month;
	cin >> month;
	cout << "Enter Year: ";
	int year;
	cin >> year;
	int count = 0;
	order* temp = this->next;
	while(temp != NULL)
	{
		if(day == temp->time.getDay() && month == temp->time.getMonth() && year == temp->time.getYear())
		{
			count += temp->calc_sum_money();
			cout << *temp;
		}
		temp = temp->next;		
	}
	if(count == 0)
		cout << "this day don't have order!!";	
	else
		cout << "\n\nThe total money of the day: " << count << endl;	
}

void order::viewOrderIsNotComplete()
{
	order* temp = this->next;
	while(temp != NULL)
	{
		if(temp->status != 1)
			cout << *temp;
		temp = temp->next;		
	}
}

void order::viewOrderWaiting()
{
	order* temp = this->next;
	while(temp != NULL)
	{
		if(temp->status == 0)
			temp->viewInformation();
		temp = temp->next;		
	}
}

void writeFileOrder(ListOrder LO)
{
	ofstream File;
	File.open("order.txt"); 
	LO = LO->next;
	while(LO != NULL)
	{
		File << LO->ID << ",";
		File << LO->time.getDay() << ",";
		File << LO->time.getMonth() << ",";
		File << LO->time.getYear() << ",";
		File << LO->status << ",";
		File << "(";
		item* temp = LO->menu->next;
		while(temp != NULL)
		{
			File << temp->getID() << ",";
			temp = temp->next;
		}
		File << ")";
		File << LO->Customer->getID() << ",";
		File << LO->Payment.getPayment_type() << ",";
		File << LO->Payment.getMoney() << ",";
		File << LO->Payment.getStatusPayment() << "\n";
		LO = LO->next;
	}
	File << "end file";
	File.close();
}

void order::readFileOrder(ListCustomer LC, ListItem LI)
{
	ifstream File;
	File.open("order.txt");
	string line;
	while(true)
	{		
		order* temp = new order;
		getline(File, line);
		if(!line.compare("end file"))
			break;
		int length_line = line.length();
		int start = 0;
		int end = 0;
		
		end = line.find(',',start);
		temp->ID = line.substr(start, end - start);
		start = end + 1;
		
		// day
		end = line.find(',',start);
		string day;
		day = line.substr(start, end - start);
		int num = 0;
		for(int i = 0;i<(end-start);i++)
			num = num*10 + (day[i] - '0');
		temp->time.day = num;
		start = end + 1;
		
		// month
		end = line.find(',',start);
		string month;
		month = line.substr(start, end - start);
		num = 0;
		for(int i = 0;i<(end-start);i++)
			num = num*10 + (month[i] - '0');
		temp->time.month = num;
		start = end + 1;
		
		// year
		end = line.find(',',start);
		string year;
		year = line.substr(start, end - start);
		num = 0;
		for(int i = 0;i<(end-start);i++)
			num = num*10 + (year[i] - '0');
		temp->time.year = num;
		start = end + 1;
		
		end = line.find(',',start);
		string status;
		status = line.substr(start, end - start);
		temp->status = status[0] - '0';
		start = end + 2;
		
		while(true)
		{
			end = line.find(',',start);
			string id_item;
			id_item = line.substr(start, end - start);
			item* item_temp = LI;
			while(item_temp->next != NULL)
			{
				if(!id_item.compare(item_temp->next->getID()))
				{
					temp->add_item_into_order(item_temp->next);
					break;
				}
				item_temp = item_temp->next;
			}
			start = end + 1;
			if(line[start] == ')')
				break;
		}
		start++;
		
		end = line.find(',',start);
		customer* C = LC->next;
		string id_customer;
		id_customer = line.substr(start, end - start);
		while(C != NULL)
		{
			if(!id_customer.compare(C->getID()))
			{
				temp->Customer = C;
				break;
			}
			C = C->next;
		}
		start = end + 1;
		
		end = line.find(',',start);
		string type_pay;
		type_pay = line.substr(start, end - start);
		temp->Payment.payment_type = type_pay[0] - '0';
		start = end + 1;
		
		end = line.find(',',start);
		string money;
		money = line.substr(start, end - start);
		num = 0;
		for(int i = 0;i<(end-start);i++)
			num = num*10 + (money[i] - '0');
		temp->Payment.money = num;
		start = end + 1;
		
		string status_pay;
		status_pay = line.substr(start, length_line);
		temp->Payment.status_payment = status_pay[0] - '0';
		
		this->add_order(temp);
	}
	File.close();
}

#endif
