#include <iostream>
#include <string>
#include "location.h"

using namespace std;

int main()
{
	ListManager LM = create_list_manager();
	LM->readFileManager();
	ListLocation LL = create_list_location(); 
	LL->readFileLocation(LM);
	while(true)
	{
		string name_manager;
		cout << "Nhap ten quan li: ";
		getline(cin,name_manager);
		manager* M = LM->handle_check_name_manager(name_manager);
		cout << "nhap du lieu dia diem: \n";	
		location L;
		cin >> L;
		L.add_manager_in_location(M);
		LL->addLocation(&L);
		cout << "ban co muon nhap tiep:(1/0) ";
		bool is_continue;
		cin >> is_continue;
		cin.ignore();
		if(!is_continue)
			break;
	}
	writeFileLocation(LL);
}
