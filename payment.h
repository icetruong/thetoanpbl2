#ifndef Payment_H
#define Payment_H

#include <iostream>
#include <string>

using namespace std;

class payment
{
	private:
		int payment_type; // 1: CK 2: tien mat
		int money;
		int status_payment;	// 0: chua thanh toan 1: da thanh toan
	public:
		payment();
		payment(int, int, int);
		
		int getPayment_type();
		int getMoney();
		int getStatusPayment();
		
		void check_status_payment();
		void handle_payment();
		friend ostream& operator << (ostream&, const payment&);
		
		friend class order;
};

payment::payment()
{
	
}

payment::payment(int type, int money, int status)
:payment_type(type), money(money), status_payment(status)
{
	
}

int payment::getPayment_type()
{
	return this->payment_type;
}

int payment::getMoney()
{
	return this->money;
}

int payment::getStatusPayment()
{
	return this->status_payment;
}


void payment::check_status_payment()
{
	if(status_payment)
		cout << "Paid";
	else
		cout << "Not Paid";
}

void payment::handle_payment()
{
	status_payment = 0;
	while(!status_payment)
	{
		cout << "You want to tranfer or money at home: ";
		cout << "\n1. at home \n2. tranfer\n Your choose tranfer: ";
		cin >> payment_type;
		if(payment_type == 1)
			return;
		else
		{
			cout << "The amount you need to pay:" << money << "D" << "\nYour paid: ";
			int your_money;
			cin >> your_money;
			if(your_money == money)
			{
				cout << "Payment successfull";
				status_payment = 1;
			}	
			else
				cout << "Payment fail";
		}
			
	}
}

ostream& operator << (ostream& os, const payment& P)
{
	if(P.payment_type == 1)
		os << "You have't paid yet. You must pay at home. The money you have paid: " << P.money;	
	else
		os << "You have paid by tranfering!! with the money: " << P.money;		
	
	return os;
}

#endif
