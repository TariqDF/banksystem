#include "bsystem.h"






BankSystem::BankSystem() {
	load();




}


//insert

void BankSystem::insert(Personaccount* node) {
	Personaccount* pointer;
	if (search(node->accountnumber) != nullptr) { cout << "duplicate account number or root is nullptr\n"; return; }
	if (root == nullptr)
	{
		root = node;
		return;
	}

	pointer = root;





	do {

		if (pointer->accountnumber < node->accountnumber) {

			if (pointer->right == nullptr)
			{
				pointer->right = node;
				node->parent = pointer;
			}
			else
			{
				pointer = pointer->right;
			}


		}
		else if (pointer->accountnumber > node->accountnumber) {

			if (pointer->left == nullptr)
			{
				pointer->left = node;
				node->parent = pointer;
			}
			else
			{
				pointer = pointer->left;
			}
		}
	} while (node->parent == nullptr);
	
	colorcorrection(node);
	
	return;

}

//setpin

void BankSystem::setpin(Personaccount* node, int pin) {

	node->pin = pin;

}



void BankSystem::makeaccount(string name, int pin, int accountnum, double creditb, double balance) {

	Personaccount* newacc = new Personaccount;
	newacc->name = name;
	newacc->accountnumber = accountnum;
	newacc->CreditBalance = creditb;
	newacc->balance = balance;
	newacc->left = nullptr;
	newacc->right = nullptr;
	newacc->parent = nullptr;
	setpin(newacc, pin);
	insert(newacc);




}

//search account

Personaccount* BankSystem::search(int accountnumb) {
	Personaccount* Findin;
	Findin = root;

	if (root == nullptr)
	{
		return nullptr;
	}

	do
	{

		if (accountnumb > Findin->accountnumber) { Findin = Findin->right; }
		else if (accountnumb < Findin->accountnumber)
		{
			Findin = Findin->left;
		}
		
		if (Findin!= nullptr)
		{
			if (Findin->accountnumber== accountnumb)
			{
				return Findin;
			}
		}
	} while (Findin != nullptr);

	



	return nullptr;


}



//removing node from parent

void BankSystem::parentremove(Personaccount* node)
{
	if (node->parent->right == node)
	{
		node->parent->right = nullptr;
	}
	else if (node->parent->left == node)
	{
		node->parent->left = nullptr;
	}

}

//delete node

void BankSystem::deleter(Personaccount* node)
{

	delete node;

}



//removing the account

void BankSystem::remove(int accountnum) {
	Personaccount* removing, * temp;
	removing = search(accountnum);
	if (removing == nullptr) {

		cout << "account not found\n";
		return;


	}

	// if the account being removed has no children
	if (removing->right == nullptr && removing->left == nullptr) {
		if (removing != root)
		{

			parentremove(removing);
			deleter(removing);
			return;
		}
		else
		{
			deleter(root);
			root = nullptr;
			return;
		}

	}


	//if the account has at least one child
	temp = (removing->left != nullptr) ? removing->left : removing->right;



	while (temp->left != nullptr || temp->right != nullptr) {
		if ((removing->right && temp == removing->right->right) || (removing->left && temp == removing->left->left))
		{
			break;
		}
		else if (temp->right != nullptr)
		{
			temp = temp->right;
		}
		else if (temp->left != nullptr)
		{
			temp = temp->left;

		}


	}

	if (removing->right && removing->right->right && temp == removing->right->right)
	{

		temp = temp->parent;
		parentremove(temp);
		temp->left = removing->left;
		temp->parent = removing->parent;
		
		//dealing with the sibling parent connection
		if (removing->left)
		{
			removing->left->parent = temp;
		}
		if (removing->right)
		{
			removing->right->parent = temp;
		}
		
		//dealing with the parent child connection

		if (removing!=root && removing->parent->right == removing)
		{
			removing->parent->right = temp;
		}
		else if (removing != root && removing->parent->left == removing)
		{
			removing->parent->left = temp;
		}
		if (removing == root)
		{
			root = temp;
		}
		deleter(removing);
		deletionfix(temp);
		return;
	}
	else if (removing->left && removing->left->left && temp == removing->left->left)
	{	
		temp = temp->parent;
		
		parentremove(temp);
		temp->right = removing->right;
		temp->parent = removing->parent;
		//dealing with the sibling parent connection
		if (removing->left)
		{
			removing->left->parent = temp;
		}
		if (removing->right)
		{
			removing->right->parent = temp;
		}

		//dealing with the parent child connection
		if (removing != root && removing->parent->right == removing)
		{
			removing->parent->right = temp;
		}
		else if (removing != root && removing->parent->left == removing)
		{
			removing->parent->left = temp;
		}
		if (removing == root)
		{
			root = temp;
		}
		deleter(removing);
		deletionfix(temp);
		return;

	}
	else
	{	parentremove(temp);
		//dealing with the sibling parent connection
		temp->parent = removing->parent;
		temp->left = removing->left;
		temp->right = removing->right;
		if (removing->left)
		{
			removing->left->parent = temp;
		}
		if (removing->right)
		{
			removing->right->parent = temp;
		}
		
		//dealing with the parent child connection
		if (removing != root && removing->parent->right == removing)
		{
			removing->parent->right = temp;
		}
		else if (removing != root && removing->parent->left == removing)
		{
			removing->parent->left = temp;
		}

		if (removing == root)
		{
			root = temp;
		}
		deleter(removing);
		deletionfix(temp);
		return;


	}
}
	

		




void BankSystem::addmoney(int accountnumb, double money) {

	Personaccount* pointer1 = search(accountnumb);

	if (pointer1->accountnumber == accountnumb)
	{
		pointer1->balance += money;
		cout << "money has been added.\n";
	}

	return;

}



void BankSystem::withdraw(int accountnumb, double money) {
	Personaccount* pointer1 = search(accountnumb);

	if (pointer1->accountnumber == accountnumb)
	{
		pointer1->balance -= money;
		cout << "money has been taken.\n";
	}

	return;


}


void BankSystem::chargecredit(int accountnumb, double money) {

	Personaccount* pointer1 = search(accountnumb);

	if (pointer1->accountnumber == accountnumb)
	{
		pointer1->CreditBalance += money;
		cout << "money has been charged to your credit.\n";
	}

	return;

}


void BankSystem::paycredit(int accountnumb, double money) {
	Personaccount* pointer1 = search(accountnumb);

	if (pointer1->accountnumber == accountnumb)
	{
		pointer1->CreditBalance -= money;
		cout << "money has been paid to your credit.\n";
	}

	return;
}



void BankSystem::transfer(int accountnumb, int accountnumb2, double money) {

	Personaccount* pointer1 = search(accountnumb);
	Personaccount* pointer2 = search(accountnumb2);


	if (pointer1->accountnumber == accountnumb)
	{
		if (pointer2->accountnumber == accountnumb2)
		{
			pointer1->balance -= money;
			pointer2->balance += money;

			cout << "money has been transfered to " << accountnumb2 << endl;
		}

	}
	else
	{
		cout << "one of the accounts not found\n";
	}
	return;




}




void BankSystem::printcredit(int accountnumb) {
	Personaccount* pointer1 = search(accountnumb);
	if (pointer1->accountnumber == accountnumb) {
		cout << "account number " << accountnumb << " credit balance:" << pointer1->CreditBalance << endl;

	}
	else
	{
		cout << "account not found\n";
	}

	return;
}




void BankSystem::printbalance(int accountnumb) {

	Personaccount* pointer1 = search(accountnumb);
	if (pointer1->accountnumber == accountnumb) {
		cout << "account number " << accountnumb << " balance:" << pointer1->balance << endl;

	}
	else
	{
		cout << "account not found\n";
	}
	return;
}



//corrects the color

void BankSystem::colorcorrection(Personaccount* node) {
	Personaccount* changer = node;
	node->color = 'r';
	if (!node->parent || !node->parent->parent)
	{
		
		return;
	}


	if (node->parent && node->parent->parent)
	{
		changer = node->parent->parent;
	}


	if (changer == root && changer->color != 'b')
	{
		node->color = 'b';
	}


	if (node->parent->parent->left == node->parent)
	{
		if (node->parent->parent->right){
			if (node->parent->parent->right->color == 'r') {
				changer->color = 'r';
				node->parent->parent->right->color = 'b';
				node->parent->color = 'b';
				
			}
			else if (node->parent->parent->right->color == 'b')
			{
				if (node->parent->left == node)
				{
					
					node->parent->color = 'b';
					changer->color = 'r';
					rrotation(changer);

				}
				else
				{
					
					node->parent->color = 'b';
					changer->color = 'r';
					lrotation(node->parent);
					rrotation(changer);
				}
			}
		}
		else
		{
			if (node->parent->left == node)
			{
				
				node->parent->color = 'b';
				changer->color = 'r';
				rrotation(changer);

			}
			else
			{
				
				node->parent->color = 'b';
				changer->color = 'r';
				lrotation(node->parent);
				rrotation(changer);
			}
		}
	}
	else if (node->parent->parent->right == node->parent)
	{
		if (node->parent->parent->left)
		{
			if (node->parent->parent->left->color == 'r') {
			changer->color = 'r';
			node->parent->parent->left->color = 'b';
			node->parent->color = 'b';
			
			}

		
			else if (node->parent->parent->left->color == 'b')
			{
				if (node->parent->left == node)
				{
					
					node->parent->color = 'b';
					changer->color = 'r';
					rrotation(node->parent);
					lrotation(changer);

				}
				else
				{
					
					node->parent->color = 'b';
					changer->color = 'r';
					lrotation(changer);

				}
			}
		}
		else
		{
			if (node->parent->left == node)
			{
				
				node->parent->color = 'b';
				changer->color = 'r';
				rrotation(node->parent);
				lrotation(changer);

			}
			else
			{
				
				node->parent->color = 'b';
				changer->color = 'r';
				lrotation(changer);

			}

		}
	}

	colorcorrection(changer);
	if (root->color != 'b')
	{
		root->color = 'b';
	}
	return;
}



void BankSystem::deletionfix(Personaccount* node) {
	if (node==root)
	{
		if (node->color!='b')
		{
			node->color = 'b';
		}
		
		return;
	}
	if (node->parent->right == node)
	{
			
		
		if (node->parent->left!=nullptr)
		{
			//case 1
			if (node->parent->left->color=='r')
			{
				node->parent->color = 'r';
				node->parent->left->color = 'b';
				rrotation(node->parent);

			}
			else if (node->parent->left->color == 'b') {
				
				if (node->parent->left->right!=nullptr || node->parent->left->left!=nullptr)
				{
					if (node->parent->left->right && !node->parent->left->left) {
						//case 3
						if (node->parent->left->right->color=='r') {
							node->parent->left->color = 'r';
							node->parent->left->right->color = 'b';
							lrotation(node->parent->left);
						}
						else if(node->parent->left->right->color == 'b') {
							//case 2
							node->parent->left->color = 'r';
							deletionfix(node->parent);
						
						
						}
					
					
					
					}
					else if(!node->parent->left->right && node->parent->left->left) {
						//case 4
						if (node->parent->left->left->color=='r')
						{
							node->parent->color = 'b';
							node->parent->left->left->color = 'b';
							rrotation(node->parent);
						}
						else if (node->parent->left->left->color == 'b')
						{
							//case 2
							node->parent->left->color = 'r';
							deletionfix(node->parent);
						}
					
					}

					
				}
				else if (node->parent->left->right && node->parent->left->left)
				{
					if (node->parent->left->right && node->parent->left->left->color=='b') {
						//case 3
						if (node->parent->left->right->color == 'r') {
							node->parent->left->color = 'r';
							lrotation(node->parent->left);
						}
						else if (node->parent->left->right->color == 'b')
						{
							node->parent->left->color = 'r';
							deletionfix(node->parent);
						}


					}
					else if (node->parent->left->right->color=='b' && node->parent->left->left) {
						//case 4
						if (node->parent->left->left->color == 'r')
						{
							node->parent->left->color = 'b';
							node->parent->left->left->color = 'b';
							rrotation(node->parent);
						}
						else if(node->parent->left->left->color == 'b')
						{
							node->parent->left->color = 'r';
							deletionfix(node->parent);
						}


					}
					else if (node->parent->left->right->color == 'r' && node->parent->left->left->color=='r')
					{
						node->parent->left->color = 'b';
						node->parent->left->left->color = 'b';
						rrotation(node->parent);
					}

				}
				else if (node->parent->left->right == nullptr && node->parent->left->left== nullptr)
				{
					//case 2
					node->parent->left->color = 'r';
					deletionfix(node->parent);


				}
			
		
			}

		}
		else
		{
			deletionfix(node->parent);
		}

	}
	else
	{
		if (node->parent->right != nullptr) {
			//case 1
			if (node->parent->right->color == 'r')
			{
				node->parent->color = 'r';
				node->parent->right->color = 'b';
				lrotation(node->parent);

			}
			else if (node->parent->right->color == 'b') {

				if (node->parent->right->right != nullptr || node->parent->right->left != nullptr)
				{
					if (node->parent->right->right && !node->parent->right->left) {
						//case 4
						if (node->parent->right->right->color == 'r') {
							
							node->parent->color = 'b';
							node->parent->right->right->color = 'b';
							lrotation(node->parent);


						}
						else if (node->parent->right->right->color == 'b') {
							//case 2
							node->parent->right->color = 'r';
							deletionfix(node->parent);


						}



					}
					else if (!node->parent->right->right && node->parent->right->left) {
						//case 3
						if (node->parent->right->left->color == 'r')
						{
							node->parent->right->color = 'r';
							node->parent->right->left->color = 'b';
							rrotation(node->parent->right);
						}
						else if (node->parent->right->left->color == 'b')
						{
							//case 2
							node->parent->right->color = 'r';
							deletionfix(node->parent);
						}

					}


				}
				else if (node->parent->right->right && node->parent->right->left)
				{
					if (node->parent->right->right && node->parent->right->left->color == 'b') {
						//case 4
						if (node->parent->right->right->color == 'r') {
							node->parent->color = 'b';
							node->parent->right->right->color = 'b';
							lrotation(node->parent);
						}
						else if (node->parent->right->right->color == 'b')
						{
							node->parent->left->color = 'r';
							deletionfix(node->parent);
						}


					}
					else if (node->parent->right->right->color == 'b' && node->parent->right->left) {
						//case 3
						if (node->parent->right->left->color == 'r')
						{
							node->parent->right->color = 'r';
							node->parent->right->left->color = 'b';
							rrotation(node->parent->right);
						}
						else if (node->parent->right->left->color == 'b')
						{
							node->parent->right->color = 'r';
							deletionfix(node->parent);
						}


					}
					else if (node->parent->right->right->color == 'r' && node->parent->right->left->color == 'r')
					{
						node->parent->right->color = 'b';
						node->parent->right->right->color = 'b';
						rrotation(node->parent);
					}

				}
				else if (node->parent->right->right == nullptr && node->parent->right->left == nullptr)
				{
					//case 2
					node->parent->right->color = 'r';
					deletionfix(node->parent);


				}


			}

		}
		else
		{
			deletionfix(node->parent);
		}
		
		
	}
}



void BankSystem::colorcheck() {
	Personaccount* node;
	int n = 1, z = 0;
	queue<Personaccount*> dis;
	paths();
	int steps = 0;
	dis.push(root);


	while (steps<=bottomfloor) {



		for (int i = 0; i < n; i++)
		{
			if (dis.empty())
			{
				break;
			}
			node = dis.front();
			if (node)
			{
				cout << node->color << " ";
				if (node->left) { dis.push(node->left); }
				else { dis.push(nullptr); }
				if (node->right) { dis.push(node->right); }
				else { dis.push(nullptr); }
				
			}
			else
			{
				cout << "n ";
				dis.push(nullptr);
				dis.push(nullptr);
			}
			dis.pop();




		}
		cout << endl;
		n *= 2;
		steps++;

	}

	return;




}







int BankSystem::height(Personaccount* node) {
	int steps=0;
	while (node->parent)
	{
		if (node->parent)
		{
			node = node->parent;
		}
		
		steps++;
	}



	return steps;

}




void BankSystem::paths() {
	queue<Personaccount*> del;
	int steps;
	Personaccount* node;
	bottomfloor = 0;
	del.push(root);
	while (!del.empty())
	{
		node = del.front();
		del.pop();
		if (node->left)
		{
			del.push(node->left);
		}
		if (node->right)
		{
			del.push(node->right);
		}
		
		if (node)
		{
			steps=height(node);
		}
		
		if (steps>bottomfloor)
		{
			bottomfloor = steps;
		}



	}

	return;

}

//checks and rotates

void BankSystem::lrotation(Personaccount* root1) {
	Personaccount* newroot;

	newroot = root1->right;
	root1->right = newroot->left;
	if (newroot->left)
	{
		newroot->left->parent = root1;
	}

	newroot->left = root1;
	newroot->parent = root1->parent;
	root1->parent = newroot;
	if (newroot->parent)
	{
		if (newroot->parent->left == root1)
		{
			newroot->parent->left = newroot;
		}
		else
		{
			newroot->parent->right = newroot;
		}
	}
	else
	{
		this->root = newroot;
	}



}





void BankSystem::rrotation(Personaccount* root1) {
	Personaccount* newroot;

	newroot = root1->left;
	root1->left = newroot->right;
	if (newroot->right)
	{
		newroot->right->parent = root1;
	}

	newroot->right = root1;
	newroot->parent = root1->parent;
	root1->parent = newroot;
	if (newroot->parent)
	{
		if (newroot->parent->left == root1)
		{
			newroot->parent->left = newroot;
		}
		else
		{
			newroot->parent->right = newroot;
		}
	}
	else
	{
		this->root = newroot;
	}



}




//delete whole tree

void BankSystem::Qdelete() {
	queue<Personaccount*> del;
	Personaccount* node;
	del.push(root);

	while (!del.empty())
	{
		node = del.front();
		if (node->left)
		{
			del.push(node->left);
		}
		if (node->right)
		{
			del.push(node->right);
		}
		del.pop();
		deleter(node);




	}

	return;
}



void BankSystem::displaytree() {

	Personaccount* node;
	int n = 1, z = 0;
	queue<Personaccount*> dis;
	paths();
	int steps = 0;
	dis.push(root);


	while (steps <= bottomfloor) {



		for (int i = 0; i < n; i++)
		{
			if (dis.empty())
			{
				break;
			}
			node = dis.front();
			if (node)
			{
				cout << node->accountnumber << " ";
				if (node->left) { dis.push(node->left); }
				else { dis.push(nullptr); }
				if (node->right) { dis.push(node->right); }
				else { dis.push(nullptr); }
				z++;
			}
			else
			{
				cout << "0000000000 ";
				dis.push(nullptr);
				dis.push(nullptr);
			}
			dis.pop();




		}
		cout << endl;
		n *= 2;
		steps++;

	}
	cout << z << " accounts\n";
	return;
}





BankSystem::~BankSystem() {
	save();
	Qdelete();
	root = nullptr;
}



//write to file

void BankSystem::save() {
	Personaccount* node;
	queue<Personaccount*> accounts;
	accounts.push(root);
	ofstream outFile("BankAccounts.txt");


	if (outFile.is_open())
	{


		while (!accounts.empty()) {
			node = accounts.front();
			accounts.pop();

			if (node->left)
			{
				accounts.push(node->left);
			}

			if (node->right)
			{
				accounts.push(node->right);
			}



			outFile << node->name << " " << node->pin << " " << node->accountnumber << " " << node->balance << " " << node->CreditBalance << endl;


		}

		outFile.close();
	}
	else
	{
		cerr << "could not create file.\n";
	}

}




int BankSystem::load() {
	ifstream inFile("BankAccounts.txt");
	if (!inFile.is_open())
	{
		cerr << "file not found, making new one\n";
		return 1;
	}
	string line, name;
	int accountnumber, pin;
	double balance, cbalance;
	while (getline(inFile, line))
	{
		istringstream iss(line);
		iss >> name >> pin >> accountnumber >> balance >> cbalance;
		makeaccount(name, pin, accountnumber, cbalance, balance);

	}
	inFile.close();
	return 0;
}

bool BankSystem::isempty() {

	if (root==nullptr)
	{
		return true;
	}
	else 
	{
		return false;

	}
}