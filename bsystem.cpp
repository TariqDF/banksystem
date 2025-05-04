#include "bsystem.h"
#include <random>

void bankmenu();
string randomname(mt19937& gen);
int whataccount();
double howmuch();

int main() {
	BankSystem mybank;
	bool term = false;
	string name,amount;
	int pin, accountnum,accountnum2, nodeamount=-1, choice;
	double creditb, balance;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> pinnum(1000, 9999), balancenum(000000,999999),acountnum1(1000000000,9999999999);

	if(mybank.isempty()){
		while (nodeamount==-1)
	{

		
			try
			{
				cout << "how many accounts do you want(only numbers)?: \n";
				cin >> amount;
				for (int i = 0; i < amount.length(); i++) {
					if (!isdigit(amount[i]))
					{
						throw runtime_error("not just numbers");
					}
				}
				nodeamount = stoi(amount);

			}
			catch (const exception& e)
			{
			cout << "caught exception: " << e.what() << endl;
	
			}
	
		}
	}
	
	for (int i = 0; i < nodeamount; i++)
	{
		name = randomname(gen);
		pin = pinnum(gen);
		creditb = balancenum(gen);
		balance= balancenum(gen);
		accountnum = acountnum1(gen);
	
		mybank.makeaccount(name, pin, accountnum, creditb, balance);
	
	
	
	}
	
	
	while (!term)
	{
		bankmenu();
		cin >> choice;

		switch (choice)
		{
		case 1:
			accountnum = whataccount();
			mybank.printbalance(accountnum);

			break;
		case 2:
			accountnum = whataccount();
			balance = howmuch();
			mybank.addmoney(accountnum, balance);
			break;
		case 3:
			accountnum = whataccount();
			balance = howmuch();
			mybank.withdraw(accountnum, balance);

			break;
		case 4:
			accountnum = whataccount();
			cout << "now for the account you want to give the money to\n";
			accountnum2 = whataccount();
			balance = howmuch();
			mybank.transfer(accountnum, accountnum2, balance);
			break;
		case 5:
			accountnum = whataccount();
			balance = howmuch();
			mybank.chargecredit(accountnum, balance);

			break;
		case 6:
			accountnum = whataccount();
			balance = howmuch();
			mybank.paycredit(accountnum, balance);
			break;
		case 7:
			accountnum = whataccount();
			mybank.printcredit(accountnum);
			break;
		case 8:
			accountnum = whataccount();
			mybank.remove(accountnum);
			break;
		case 9:

			mybank.displaytree();

			break;
		
		
		case 10:
			mybank.colorcheck();
		
			break;
		case 11:

			term = true;

			break;

		default:

			cout << "not an option\n";
			cin.clear();
			cin.ignore(10000, '\n');
			break;
		}

	}

	return 0;

}






void bankmenu() {

	cout <<"1. print balance\n" << "2. deposit\n" << "3. withdrawl\n" << "4. transfer\n" << "5.charge credit\n" << "6. pay credit\n";
	cout << "7.show credit balance\n" <<"8. remove an account\n" << "9. display tree\n" <<"10. color check\n" << "11. exit\n";



	return;

}




string randomname(mt19937& gen) {
	string name;
	uniform_int_distribution<> names(0, 29);
	string namebank[] = { "Alice", "Bob", "Charlie", "Diana", "Ethan", "Fiona", "George", "Hannah", "Isaac", "Julia",
		"Kevin", "Laura", "Michael", "Natalie", "Oliver", "Paige", "Quentin", "Rachel", "Samuel", "Tina",
		"Umar", "Vanessa", "William", "Xander", "Yasmine", "Zachary", "Amber", "Brian", "Chloe", "Derek" };



	name = namebank[names(gen)];
	return name;

}




int whataccount() {
	string accountstringnum;
	int accountnum;
	bool through = false;

	while (!through)
	{

	
		try
		{
			cout << "Enter a 10-digit account number:\n";
			cin >> accountstringnum;


			if (accountstringnum.length() == 10)
			{
				if (accountstringnum[0] == '0') {
					throw runtime_error("account number cannot start with 0");
				}

				for (int i = 0; i < accountstringnum.length(); i++) {
					if (!isdigit(accountstringnum[i]))
					{
					throw runtime_error("not just numbers");
					}
				}


			}
			else
			{
				throw runtime_error("too long or short try again");
			}

			accountnum = stoi(accountstringnum);
			through = true;
		}
		catch (const std::exception& E)
		{
			cout << "caught exception: " << E.what() << endl;
		}
	}

	return accountnum;

}




double howmuch() {
	string cashstring;
	double cash;
	bool through = false;
	bool decimal_seen=false;
	
	while (!through)
	{


		try
		{
			cout << "Enter amount (numbers only, optionally with decimal):\n";
			cin >> cashstring;


			
		

				for (int i = 0; i < cashstring.length(); i++) {
					if (!isdigit(cashstring[i]))
					{	if (cashstring[i]=='.'&& decimal_seen== false)
						{
							decimal_seen = true;
						}
						else
						{
							throw runtime_error("not just numbers");

						}
						
					}
					

				}


			

			cash= stod(cashstring);
			through = true;
		}
		catch (const std::exception& E)
		{
			cout << "caught exception: " << E.what() << endl;
		}
	}

	return cash;

}