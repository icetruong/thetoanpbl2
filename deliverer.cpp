#include <iostream>
#include <string>
#include "deliverer.h"

using namespace std;

int main()
{
	ListDeliverver LD = create_list_deliverer();
	LD->readFileDeliverer();
	while(true)
	{
		cout << "nhap du lieu nguoi giao hang: \n";
		deliverer D;
		cin >> D;
		LD->addDeliverer(&D);
		cout << "ban co muon nhap tiep:(1/0) ";
		bool is_continue;
		cin >> is_continue;
		cin.ignore();
		if(!is_continue)
			break;
	}
	writeFileDeliverer(LD);
}
