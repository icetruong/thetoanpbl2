#ifndef ID_H
#define ID_H

#include <iostream>
#include <string>

#define ID_default "00000000"

using namespace std;

class ID
{
	protected:
		string ID;
		
		string increase_ID(string id)
		{
			int n = id.length();
			for(int i = n - 1; i>=0; i--)
				if(id[i] < '9')
				{
					id[i] += 1;
					break;
				}
				else
					id[i] = '0';
			return id;
		}
	public:
		string getID()
		{
			return this->ID;
		}
};

#endif
