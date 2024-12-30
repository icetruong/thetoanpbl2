#include <iostream>
#include <string>
#include "item.h"
#include "location.h"
#include "manager.h"

using namespace std;

int main()
{
	ListManager LM = create_list_manager();
	LM->readFileManager();
	ListLocation LL = create_list_location();
	LL->readFileLocation(LM);
	ListItem LI = create_list_item();
	LI->readFileItem(LL);
	while(true)
	{
		string name_location;
		cout << "Nhap ten dia diem: ";
		getline(cin,name_location);
		location* L = LL->handle_check_name_location(name_location);
		cout << "nhap du lieu mat hang: \n";
		item I;
		cin >> I;
		I.add_location_in_item(LL->next);
		LI->addItem(&I);
		cout << "ban co muon nhap tiep:(1/0) ";
		bool is_continue;
		cin >> is_continue;
		cin.ignore();
		if(!is_continue)
			break;
	}
	writeFileItem(LI);
}
