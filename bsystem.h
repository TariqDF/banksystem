#pragma once
#include <iostream>
#include <queue>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;
#ifndef bsystem



#define bsystem

struct Personaccount {

	double balance;
	double CreditBalance;
	int accountnumber;
	int pin;
	string name;
	char color;
	



	Personaccount* left;
	Personaccount* right;
	Personaccount* parent;

};




class BankSystem {
private:
	Personaccount* root;	
	void rrotation(Personaccount* root1);
	void lrotation(Personaccount* root1);
	Personaccount* search(int accountnumb);
	int bottomfloor;
public:
	BankSystem();
	void makeaccount(string name, int pin, int accountnum, double creditb = 0, double balance = 0);
	void setpin(Personaccount* node, int pin);
	void remove(int accountnumb);
	void insert(Personaccount* node);
	void addmoney(int accountnumb, double money);
	void withdraw(int accountnumb, double money);
	void transfer(int accountnumb, int accountnumb2, double money);
	void deleter(Personaccount* node);
	void Qdelete();
	void parentremove(Personaccount* node);
	void printbalance(int accountnumb);
	void chargecredit(int accountnumb, double money);
	void paycredit(int accountnumb, double money);
	void printcredit(int accountnumb);
	void deletionfix(Personaccount* node);
	void colorcorrection(Personaccount* node);
	void paths();
	void save();
	int load();
	int height(Personaccount* node);
	void displaytree();
	bool isempty();
	void colorcheck();
	~BankSystem();
};

#endif // !bankingclass







