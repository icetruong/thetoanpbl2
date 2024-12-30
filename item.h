#ifndef Item_H
#define Item_H

#include <iostream>
#include <string>
#include <iomanip>
#include "location.h"


using namespace std;

class item: public ID
{
	private:
		string nameItem;
		string describe;
		int price;
		int availability; // 1: in stock, 0: out of stock
		class location* Location;
	
		class item *headItem;
		class item *lastItem;
	public:
		class item *next;
		
		void handle_create_item(item *I)
		{
			this->lastItem->next = I;
			this->lastItem = I;
		}
		
		item();
		item(string, string, int, int, location*);
		item(const item&);
		
		typedef class item *ListItem;
		friend ListItem create_list_item();
		
		virtual void updateInformation();
		void viewInformationItemForCustomer();
		friend ostream& operator << (ostream&, const item&);
		
		friend istream& operator >> (istream&, item&);
		
		const item& operator = (const item&);
		
		void bubble_sort_list_item();
		
		void add_location_in_item(location* );
		
		void addItem(item *);
		void handleSearchItem();
		void deleteItem(string);
		
		ListItem getItemformLocation(location* );
		void viewListItemfromLocation();
		
		friend void writeFileItem(ListItem);
		void readFileItem(ListLocation);
		
		
		
		friend class order;
};

item::item()
{
	next = NULL;
	this->Location = new location;
}

item::item(string name, string describe, int price, int availability, location* L)
:nameItem(name), describe(describe), price(price), availability(availability), Location(L)
{
	next = NULL;
}

item::item(const item& I)
{
	this->next = NULL;
	this->ID = I.ID;
	this->nameItem = I.nameItem;
	this->describe = I.describe;
	this->price = I.price;
	this->availability = I.availability;
	this->Location = I.Location;
}

typedef class item *ListItem;
ListItem create_list_item()
{
	ListItem LI = new item;
	LI->ID = ID_default;
	LI->headItem = LI;
	LI->lastItem = LI;
	return LI;
}

void item::viewInformationItemForCustomer()
{
	cout << "Name: " << this->nameItem << " Describe: " << this->describe << " Price " << this->price;
	cout << "D\nLocation:"  << *this->Location;
}

ostream& operator << (ostream& os, const item& I)
{
	os << "Name: " << I.nameItem << " Describe: " << I.describe << " Price " << I.price << "D" ;
	if(I.availability == 0)
		os << " Out of stock";
	else
		os << " In stock ";
	os << "\nLocation: ";
	cout << *I.Location;
	
	return os;
}

istream& operator >> (istream& is, item& I)
{
	cout << "Enter information :\n 1. name: ";
	getline(is,I.nameItem);
	cout << "2. describe: ";
	getline(is,I.describe);
	cout << "3. price: ";
	is >> I.price;
	cout << "4. availability:  ";
	is >> I.availability;
	is.ignore();
	
	return is;
}

void item::add_location_in_item(location* L)
{
	this->Location = L;
}

void item::updateInformation()
{
	cout << "Enter the name you want to update: ";
	string newNameItem;
	getline(cin,newNameItem);
	item* I = this;
	while(I->next != NULL)
	{
		if(!newNameItem.compare(I->next->nameItem))
		{
			cout << "What item information do you want to change?\n";
			cout << "1. Name: " << I->next->nameItem;
			cout << "\n2. describe " << I->next->describe;
			cout << "\n3. price " << I->next->price;
			cout << "\n4. availability\n" << I->next->availability;
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
						getline(cin,I->next->nameItem);
						break;
					case 2:
						cout << "New describe: ";
						cin.ignore();
						getline(cin,I->next->describe);
						break;
					case 3:
						cout << "New price: ";
						cin >> I->next->price;
						break;
					case 4:
						cout << "New availability: stock/not stock (1/0)  ";
						cin >> I->next->availability;
						break;
				}
				cout << "Do you want to continue ?(1/0)";
				bool is_continue;
				cin >> is_continue;
				if(!is_continue)
					break;
			}
		}
		I = I->next;
	}	
	if(I == NULL)
		cout << "update failed";
	else
		cout << "update successfully";
}

const item& item::operator = (const item& I)
{
	this->ID = I.ID;
	this->nameItem = I.nameItem;
	this->describe = I.describe;
	this->price = I.price;
	this->availability = I.availability;
	this->Location = I.Location;
	
	return *this;
}

void swap_string(string& a ,string& b)
{
	string temp = a;
	a = b;
	b = temp;
}

void swap_int(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void item::bubble_sort_list_item()
{
	item* i = this->next;
	for(;i->next != NULL;i = i->next)
		for(item* j = i->next;j != NULL;j = j->next)
			if(i->nameItem.compare(j->nameItem) == 1)
			{
				swap_string(i->ID,j->ID);
				swap_string(i->nameItem,j->nameItem);
				swap_string(i->describe,j->describe);
				swap_int(i->price,j->price);
				swap_int(i->availability,j->availability);
				
				location* L = i->Location;
				i->Location = j->Location;
				j->Location = L;
			}
}

void item::addItem(item *I)
{
	if(I->ID.empty())
		I->ID = this->increase_ID(this->lastItem->ID);
		
	item* temp = new item;
	*temp = *I;
	this->handle_create_item(temp);
}

void item::handleSearchItem()
{
	cout << "\n\nPress 0 to search item!!";
	int your_search;
	cin >> your_search;
	cin.ignore();
	while(!your_search)
	{
		cout << "Enter the item you want to search for(can be the first few letter)";
		string your_enter;
		getline(cin,your_enter);
		int i = 1;
		item* temp2 = this->next;
		while(temp2 != NULL)
		{
			if(temp2->nameItem.find(your_enter) != string::npos)
				if(temp2->nameItem.find(your_enter) == 0)
				{
					cout << "\n" << i << ". " << *temp2;
					i++;
				}	
			temp2 = temp2->next;
		}
		if(i == 1)
			cout << "Don't have item you search!!, you can enter repeat: \n" ;
		else
			break;
	}
}

void item::deleteItem(string newNameItem)
{
	
	item* I = this;
	while(I->next != NULL)
	{
		if(!newNameItem.compare(I->next->nameItem))
		{
			item* newItem = I->next;
			I->next = I->next->next;
			delete newItem;
			break;
		}
		I = I->next;
	}	
	if(I->next == NULL)
		cout << "delete failed";
	else
		cout << "delete successfully";
}

ListItem item::getItemformLocation(location* L)
{
	item* temp_LI = this->next;
	ListItem LIFL  = create_list_item();
	while(temp_LI != NULL)
	{
		if(!L->getID().compare(temp_LI->Location->getID()))
			LIFL->addItem(temp_LI);
		temp_LI = temp_LI->next;
	}
	return LIFL;
}

void item::viewListItemfromLocation()
{
	ListItem temp_LI = this->next;
	cout << "\nLOCATION: ";
	cout << *temp_LI->Location;
	cout << "\n \n";
	cout << "List item: \n";
	int i = 1;
	cout << left << setw(8) << "" << setw(35) <<	"Name " << setw(32) << "Describe " << setw(15) << right << "Price " << setw(15) << "Availability" << endl;
	cout << left << setw(115) << setfill('-') << "" << endl;
	cout << setfill(' ');
	while(temp_LI != NULL)
	{
		cout << left;
		cout << "\n" << setw(8) << i << setw(35);
		cout << temp_LI->nameItem << "| " << setw(30);
		cout << temp_LI->describe << "| "<< setw(11) ;
		cout << right << temp_LI->price  << "D | " << setw(14) ;
		if(temp_LI->availability == 0)
			cout << " Out of stock";
		else
			cout << " In stock "; 
		temp_LI = temp_LI->next;
		i++;
	}
}

void writeFileItem(ListItem LI)
{
	ofstream File;
	File.open("item.txt"); 
	LI = LI->next;
	while(LI != NULL)
	{
		File << LI->ID << ",";
		File << LI->nameItem << ",";
		File << LI->describe << ",";
		File << LI->price << ",";
		File << LI->availability << ",";
		File << LI->Location->getID() << "\n";
		LI = LI->next;
	}
	File << "end file";
	File.close();
}

void item::readFileItem(ListLocation LL)
{
	ifstream File;
	File.open("item.txt");
	string line;
	item* temp = new item;
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
		temp->nameItem = line.substr(start, end - start);
		start = end + 1;
		
		end = line.find(',',start);
		temp->describe = line.substr(start, end - start);
		start = end + 1;
		
		end = line.find(',',start);
		string price;
		price = line.substr(start, end - start);
		int num = 0;
		for(int i = 0;i<(end-start);i++)
			num = num*10 + (price[i] - '0');
		temp->price = num;
		start = end + 1;
		
		end = line.find(',',start);
		string abailability;
		abailability = line.substr(start, end - start);
		num = 0;
		for(int i = 0;i<(end-start);i++)
			num = num*10 + (abailability[i] - '0');
		temp->availability = num;
		start = end + 1;
		
		location* L = new location;
		L= LL->next;
		string id_location;
		id_location = line.substr(start, length_line);
		while(L!= NULL)
		{
			if(!id_location.compare(L->getID()))
			{
				temp->Location = L;
				break;
			}
			L = L->next;
		}
		
		this->addItem(temp);
	}
	File.close();
}


#endif
