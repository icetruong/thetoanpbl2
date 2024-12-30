#include <iostream>
#include <string>
#include "manager.h"
#include "customer.h"
#include "deliverer.h"
#include "location.h"
#include "item.h"
#include "order.h"

using namespace std;

int main()
{
	ListManager LM = create_list_manager();
	LM->readFileManager();
	ListCustomer LC = create_list_customer();
	LC->readFileCustomer();
	ListLocation LL = create_list_location();
	LL->readFileLocation(LM);
	ListItem LI = create_list_item();
	LI->readFileItem(LL);
	ListOrder LO = create_list_order();
//	writeFileOrder(LO);
	LO->readFileOrder(LC,LI);
	
	ListDeliverver LD = create_list_deliverer();
	LD->readFileDeliverer(LO);
	
	cout << "\n<--------------------> PBL2: Du an co so lap trinh <-------------------->\n\n";
	cout << "<----------- Giao vien huong dan: Le Thi My Hanh ------------------>\n\n");
	while(true)
	{	
	
		system("color 70");
		cout << "<--------------------> Ung dung quan li don hang goi mon <-------------------->\n\n\n\n");
		int your_choose;
		cout << "\n1. Login\n2. Register\nRemain: exit";
		cout << "\n Your choose is: ";
		cin >> your_choose;
		int check_login;
		
		customer* CS = new customer;
		deliverer* D = new deliverer;
		manager* M = new manager;
		while(true)
		{
			cin.ignore();
			if(your_choose == 1)
			{
				cout << "Enter your account: ";
				string your_account;
				getline(cin,your_account);
				cout << "Enter your password: ";
				string your_password;
				getline(cin,your_password);
				check_login = 1; // 1 is customer, 2 is deliverer, 3 is manager
				CS = Login(LC,your_account,your_password);
				if(CS == NULL)
				{
					check_login = 2;
					D = Login(LD,your_account,your_password);
					if(D == NULL)
					{
						check_login = 3;
						M = Login(LM,your_account,your_password);
						if(M == NULL)
						{
							cout << "khong co tai khoan ban vua nhap!! vui lòng chon lai phuong thuc dang nhap: ";
							check_login = 0;
							break;
						}		
						else
							break;
					}
					else
						break;
				}
				else
					break;
			}
			else
				if(your_choose == 2)
				{
					check_login = 1;
					CS = Register(LC);
					if(CS != NULL)
						break;
				}
				else
					break;
		}
		if(your_choose != 1 && your_choose != 2)
			break;
		
		
		if(check_login == 1)
			while(true)
			{
				cout << "\nWhat do you want to choose?";
				cout << "\n1. view information";
				cout << "\n2. update information";
				cout << "\n3. order";
				cout << "\n4. view history order";
				cout << "\n5. view order being not complete ";
				cout << "\n6. log out";
				cout << "\nyour choose is : ";
				cin >> your_choose;
				
				string name_location;
				switch(your_choose)
				{
					case 1: 
						cout << *CS;
						break;
					case 2:
						CS->updateInformation();
						break;
					case 3:
						location *L;
						L = new location;
						cout << "List Location you can choose: \n";
						LL->viewListLocation();
						cout << "\nEnter name location you want to order:";
						cin.ignore();
						getline(cin,name_location);
						L = LL->handle_check_name_location(name_location);
						ListItem LIFL;
						LIFL = LI->getItemformLocation(L);
						LIFL->bubble_sort_list_item();
						LO->PlaceAnOrder(LIFL,CS);
						
						break;
					case 4:
						ListOrder ListhistoryOrder;
						ListhistoryOrder = LO->getHistoryOrder(CS);
						ListhistoryOrder->viewListOrder();
						break;
					case 5:
						LO->viewOrderIsNotComplete();
						break;
				}
				if(your_choose == 6)
					break;
					
						
				cout << "\nDo you want to continue to stay in the application ? (1/0)";
				bool is_continue;
				cin >> is_continue;
				if(!is_continue)
					break;
			}	
		else
			if(check_login == 2)
			{
				while(true)
				{
					cout << "\nWhat do you want to choose?";
					cout << "\n1. view information";
					cout << "\n2. update information";
					cout << "\n3. set state";
					cout << "\n4. Get order to deliver";
					cout << "\n5. Make deliver";
					cout << "\n6. log out";
					cout << "\nyour choose is : ";
					cin >> your_choose;
					string name_order;
					switch(your_choose)
					{
						case 1: 
							cout << *D;
							break;
						case 2:
							D->updateInformation();
							break;
						case 3:
							D->viewState();
							cout << "you want to set state into:\n0. busy   1. freetime   2. delivering  \nyour choose: ";
							int your_state;
							cin >> your_state;
							D->setState(your_state);
							break;
						case 4:
							cout << "List Order need delivering: \n \n";
							LO->viewOrderWaiting();
							LD->ReceiveOrder(LO,D);
							break;
						case 5: 
							cout << "List Order you need to deliver:";
							D->viewListOrderDelivering();
							LD->MakeDeliverer(LO,D);
					}
					if(your_choose == 6)
						break;
						
							
					cout << "\nDo you want to continue to stay in the application ? (1/0)";
					bool is_continue;
					cin >> is_continue;
					if(!is_continue)
						break;
				}
			}	
			else
				if(check_login == 3)
				{
					while(true)
					{
						cout << "\nWhat do you want to choose?";
						cout << "\n1. view information";
						cout << "\n2. update information";
						cout << "\n3. change item in location";
						cout << "\n4. view information report order in day";
						cout << "\n5. view deliverer ";
						cout << "\n6. log out";
						cout << "\nyour choose is : ";
						cin >> your_choose;
						string name_location;
						switch(your_choose)
						{
							case 1: 
								cout << *M;
								break;
							case 2:
								M->updateInformation();
								break;
							case 3:
								location *L;
								L = new location;
								ListLocation LLFL;
								LLFL = LL->getLocationformManager(M);
								cout << "List Location you can choose: \n";
								LLFL->viewListLocation();
								cout << "\nEnter name location you want to change:";
								cin.ignore();
								
								getline(cin,name_location);
								L = LL->handle_check_name_location(name_location);
								ListItem LIFL;
								LIFL = LI->getItemformLocation(L);
								LIFL->bubble_sort_list_item();
								LIFL->viewListItemfromLocation();
								int your_change;
								cout << "\nWhat do you want to choose to change information item in location?";
								cout << "\n1. add item";
								cout << "\n2. delete item";
								cout << "\n3. update item";
								cout << "\nyour choose: ";
								cin >> your_change;	
								cin.ignore();
								if(your_change == 1)
								{
									item* I = new item;
									cout << "enter data item: ";
									cin >> *I;	
									I->add_location_in_item(L);
									LI->addItem(I);
									cout << "add successfully";
								}
								else
									if(your_change == 2)
									{
										LIFL->handleSearchItem();
										cout << "Enter the name you want to delete: ";
										string newNameItem;
										getline(cin,newNameItem);
										LIFL->deleteItem(newNameItem);
										LI->deleteItem(newNameItem);	
									}
									else
									{
										LIFL->handleSearchItem();
										LIFL->updateInformation();
									}
								
								break;
							case 4:
								LO->viewReportOrderinDay();
								break;
							case 5:
								LD->viewListDeliverer();
								break;
							
								
						}
						if(your_choose == 6)
							break;
							
								
						cout << "\nDo you want to continue to stay in the application ? (1/0)";
						bool is_continue;
						cin >> is_continue;
						if(!is_continue)
							break;
					}	
				}
				
	}
		
	writeFileManager(LM);
	writeFileCustomer(LC);
	writeFileDeliverer(LD);
	writeFileItem(LI);
	writeFileLocation(LL);
	writeFileOrder(LO);
}

// sua thanh nguoi giao hang co the giao hang
