#include <iostream>
#include <string>
#include "customer.h"

using namespace std;

int main()
{
	ListCustomer LC = create_list_customer();
	LC->readFileCustomer();
	while(true)
	{
		cout << "nhap du lieu khach hang: \n";
		customer C;
		cin >> C;
		LC->addCustomer(&C);
		cout << "ban co muon nhap tiep:(1/0) ";
		bool is_continue;
		cin >> is_continue;
		cin.ignore();
		if(!is_continue)
			break;
	}
	writeFileCustomer(LC);
	
}
