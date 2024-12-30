#include <iostream>
#include <string>
#include "manager.h"

int main()
{
	ListManager LM = create_list_manager();
	LM->readFileManager();
	while(true)
	{
		cout << "nhap du lieu quan li: \n";
		manager M;
		cin >> M;
		LM->addManager(&M);
		cout << "ban co muon nhap tiep:(1/0) ";
		bool is_continue;
		cin >> is_continue;
		cin.ignore();
		if(!is_continue)
			break;
	}
	writeFileManager(LM);
}
